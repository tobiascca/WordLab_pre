    // Used libraries
#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <random>
#include <algorithm>
#include <fstream>
#include <unordered_set>
using namespace std;

    // Color escape assigned to string
const string reset = "\033[0m";
const string red = "\033[31m";
const string green = "\033[32m";
const string yellow = "\033[33m";

    // Global variables
string word;
string aGuess;
string correctAns;
string targetWord;
char letter = ' ';
vector<string> guesses = {};
vector<string> words = {};
int i = 0;

    // Displays presentation message
void welcome() {
    cout << "\tWelcome to wording!" << endl;
    cout << "You are given a 5 letter word and you have to guess this word ";
    cout << "in six tries. When you give me a word, if the letter is in its ";
    cout << "correct place, the letter will turn green, if it is not in the place, ";
    cout << "the letter will turn yellow. Let's start! " << endl;
}

    // Colors just a letter
void colorLetter(const char& l, const string& color) {
    cout << color << l << reset << " ";
}

    // Prints colored text
void colorText(const string& word, const string& color) {
    cout << color << word << reset << endl;
}

    // Prints the word in formatted form
void printWord(const string& word) {
    for (int i = 0; i < word.length(); i++) {
        cout << " ";
        cout << word[i] << " ";
    }
    cout << endl;
}

    // Function that checks if word matches
bool checkForMatch(const string& targetWord, const string& aGuess) {
    if (targetWord == aGuess) return true;
    else return false;
}

    // Prints again the word with in-color feedback
void printFeedback(const string& targetWord, const string& aGuess) {

    unordered_set<char> targetLetters(targetWord.begin(), targetWord.end());

    for (size_t i = 0; i < targetWord.length(); i++) {
            // If letter match in correct position
        if (targetWord[i] == aGuess[i]) colorLetter(aGuess[i], green);

            // If letter match but at incorrect place
        else if (targetLetters.find(aGuess[i]) != targetLetters.end()) colorLetter(aGuess[i], yellow);
        
            // If not a letter match
        else colorLetter(aGuess[i], reset);
    }

    cout << endl;
}

    // Main function to call game
void generateProblem() {

        // Seeding random number generator
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution dis(1, 40);
    int random = dis(gen);

        // Reading list of words
    ifstream inputFile("chair.txt");

        // Inserting all words in a list
    if (inputFile.is_open()) {
        string word;
        while (getline(inputFile, word)) {
            words.push_back(word);
        }
        inputFile.close();
    } else {
        cerr << "Error opening file." << endl;
    }

    string targetWord = words[random];
    cout << targetWord << endl;

    for (int i = 0; i < 6; i++) {
    
    comienzo:
        cout << "Enter a 5 letter word in lowercase: " << " ";
        cin >> aGuess;

        if (aGuess.length() != 5) {
            do {
                cout << "\tError! Not a 5 letter word." << endl; 
                cin >> aGuess;
            } while (aGuess.length() != 5);
        }

        printFeedback(targetWord, aGuess);

        if (checkForMatch(targetWord, aGuess) == true) {
            cout << "Word Match! Congratulations." << endl;
            guesses.empty();
            goto comienzo;
        } else if (guesses.size() == 6) {
            cout << "\nAll six tries were made, you loose! The word was: " << endl;
            colorText("  ", green);
            printWord(targetWord);
            colorText("  ", reset);
            guesses.clear();
            break;
        } else {
            guesses.push_back(aGuess);                  // stores the wrong guess
        }
    }
}

void counter() {}