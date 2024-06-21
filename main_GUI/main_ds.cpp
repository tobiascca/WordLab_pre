#include <iostream>
#include <raylib.h>
using namespace std;

// Enum for game events
typedef enum GameEvent {
    MENU,
    START,
    OPTIONS,
    CREDITS
} GameEvent;

// Function to draw the return button and handle clicks
bool DrawReturnButton(Texture2D backIcon, float scale) {
    DrawTextureEx(backIcon, (Vector2){ 10, 10 }, 0.0f, scale, WHITE);
    Rectangle backRect = { 10, 10, backIcon.width * scale, backIcon.height * scale };
    return CheckCollisionPointRec(GetMousePosition(), backRect) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON);
}

// Function to draw a custom slider
float DrawSlider(float x, float y, float width, float height, float value) {
    Rectangle sliderBar = { x, y, width, height };
    Rectangle sliderKnob = { x + value * width - height / 2, y - height / 4, height / 2, height * 1.5f };

    // Draw the slider bar
    DrawRectangleRec(sliderBar, GRAY);

    // Check if the mouse is over the slider knob
    if (CheckCollisionPointRec(GetMousePosition(), sliderKnob) && IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
        // Update the slider value based on mouse position
        value = (GetMouseX() - x) / width;
        if (value < 0.0f) value = 0.0f;
        if (value > 1.0f) value = 1.0f;
    }

    // Draw the slider knob
    DrawRectangleRec(sliderKnob, WHITE);

    return value;
}

int main() {
    // Initialize raylib with desired window size
    float screenWidth = 500;
    float screenHeight = 700;
    InitWindow(screenWidth, screenHeight, "WordLab");

    // Images
    Texture2D backIcon = LoadTexture("previous.png");
    if (backIcon.id == 0) {
        cout << "Failed." << endl;
        return -1;
    }
    float scale = 0.25f;     // To scale image

    // Define colors for text and button
    Color titleColor = WHITE;
    Color buttonBackgroundColor = BLUE;
    Color buttonTextColor = WHITE;

    // Set target FPS for smooth animation
    SetTargetFPS(60);

    // Current game state
    GameEvent currentEvent = MENU;

    // Variables for options settings
    bool showTutorial = true;
    const char* languages[] = {"English", "Spanish"};
    int currentLanguage = 0;
    float musicVolume = 0.5f;
    float sfxVolume = 0.5f;


    // Game loop
    while (!WindowShouldClose()) {
        // Update and draw based on current game state
        switch (currentEvent) {
            case MENU: {
                // Start drawing on frame
                BeginDrawing();

                // Clear the screen with black background
                ClearBackground(BLACK);

                // Font size for the title text
                int fontSize = 50;
                const char* titleText = "WORDLAB";

                // Calculate the width of the title text
                int titleTextWidth = MeasureText(titleText, fontSize);

                // Calculate the center position for the title text
                int titleX = (screenWidth / 2) - (titleTextWidth / 2);
                int titleY = screenHeight / 6;

                // Draw the title text
                DrawText(titleText, titleX, titleY, fontSize, titleColor);

                // Define button dimensions and position
                float buttonWidth = 200;
                float buttonHeight = 50;
                float buttonX = screenWidth / 2 - buttonWidth / 2;

                // Button labels and positions
                const char* buttonTexts[] = {"START", "OPTIONS", "CREDITS", "EXIT"};
                float buttonYPositions[] = {(screenHeight / 2) - 100, (screenHeight / 2) - 40, (screenHeight / 2) + 20, (screenHeight / 2) + 80};

                // Draw buttons
                for (int i = 0; i < 4; i++) {
                    float buttonY = buttonYPositions[i];

                    // Check if mouse is hovering over the button
                    bool isHoveringButton = CheckCollisionPointRec(GetMousePosition(), Rectangle{buttonX, buttonY, buttonWidth, buttonHeight});

                    // Change button background color based on hover state
                    if (isHoveringButton) {
                        buttonBackgroundColor = SKYBLUE;
                    } else {
                        buttonBackgroundColor = BLUE;
                    }

                    // Draw the button rectangle
                    DrawRectangle(buttonX, buttonY, buttonWidth, buttonHeight, buttonBackgroundColor);

                    // Calculate the width of the button text
                    int buttonTextWidth = MeasureText(buttonTexts[i], 20);

                    // Calculate the center position for the button text
                    int buttonTextX = (int)(buttonX + (buttonWidth / 2)) - (buttonTextWidth / 2);
                    int buttonTextY = buttonY + (buttonHeight - 20) / 2;

                    // Draw the button text
                    DrawText(buttonTexts[i], buttonTextX, buttonTextY, 20, buttonTextColor);

                    // Handle button clicks
                    if (isHoveringButton && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                        if (i == 0) currentEvent = START; // Start button
                        else if (i == 1) currentEvent = OPTIONS; // Options button
                        else if (i == 2) currentEvent = CREDITS; // Credits button
                        else if (i == 3) CloseWindow(); // Exit button
                    }
                }

                // End drawing on frame
                EndDrawing();
            } break;

            case START: {
                // Start drawing on frame
                BeginDrawing();
                ClearBackground(DARKGRAY);
                
                // Draw the return button and check for click
                if (DrawReturnButton(backIcon, 0.1f)) {
                    currentEvent = MENU;
                }

                // Display gameplay screen content
                DrawText("WordLab", screenWidth / 2 - MeasureText("WordLab", 15), 55, 30, WHITE);

                // End drawing on frame
                EndDrawing();

            } break;

            case OPTIONS: {
                // Start drawing on frame
                BeginDrawing();
                ClearBackground(DARKBLUE);

                // Draw the return button and check for click
                if (DrawReturnButton(backIcon, scale)) {
                    currentEvent = MENU;
                }

                // Display options screen content
                float optionsY = 150;
                DrawText("OPTIONS", screenWidth / 2 - MeasureText("OPTIONS", 40) / 2, 50, 40, WHITE);
                
                // Toggle tutorial
                DrawText(TextFormat("Show Tutorial: %s", showTutorial ? "ON" : "OFF"), 50, optionsY, 20, WHITE);
                if (CheckCollisionPointRec(GetMousePosition(), Rectangle{50, optionsY, 200, 20}) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                    showTutorial = !showTutorial;
                }
                optionsY += 40;

                // Language selection
                DrawText(TextFormat("Language: %s", languages[currentLanguage]), 50, optionsY, 20, WHITE);
                if (CheckCollisionPointRec(GetMousePosition(), Rectangle{50, optionsY, 200, 20}) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                    currentLanguage = (currentLanguage + 1) % 3;
                }
                optionsY += 40;

                // Music volume
                DrawText(TextFormat("Music Volume: %.2f", musicVolume), 50, optionsY, 20, WHITE);
                musicVolume = DrawSlider(250, optionsY, 200, 20, musicVolume);
                optionsY += 40;

                // SFX volume
                DrawText(TextFormat("SFX Volume: %.2f", sfxVolume), 50, optionsY, 20, WHITE);
                sfxVolume = DrawSlider(250, optionsY, 200, 20, sfxVolume);
                optionsY += 40;

                // Reset progress button
                DrawText("Reset Progress", 50, optionsY, 20, RED);
                if (CheckCollisionPointRec(GetMousePosition(), Rectangle{50, optionsY, 200, 20}) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                    // Reset progress logic here
                }

                // End drawing on frame
                EndDrawing();
            } break;

            case CREDITS: {
                // Start drawing on frame
                BeginDrawing();

                // Draw the return button and check for click
                if (DrawReturnButton(backIcon, scale)) {
                    currentEvent = MENU;
                }

                // Clear the screen with a different background color
                ClearBackground(DARKGREEN);
                DrawTexture(backIcon, screenHeight / 2, screenWidth / 2, DARKGRAY);

                // Display credits screen content
                DrawText("Credits", screenWidth / 2 - MeasureText("Credits", 60) / 2, 50, 60, WHITE);
                DrawText("Tobias Anuf", screenWidth / 2 - MeasureText("Tobias Anuf", 20) / 2, 220, 20, WHITE);
                DrawText("Angie Barreto", screenWidth / 2 - MeasureText("Angie Barreto", 20) / 2, 260, 20, WHITE);
                DrawText("Bryan ...", screenWidth / 2 - MeasureText("Bryan ...", 20) / 2, 300, 20, WHITE);
                DrawText("Lujan Martinez", screenWidth / 2 - MeasureText("Lujan Martinez", 20) / 2, 340, 20, WHITE);

                // End drawing on frame
                EndDrawing();

            } break;

            default: break;
        }
    }

    // Unload the back icon texture
    UnloadTexture(backIcon);

    // Close the raylib window
    CloseWindow();

    return 0;
}