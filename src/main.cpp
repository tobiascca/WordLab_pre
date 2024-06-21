#include <iostream>
#include "wordingLibrary.cpp"

using namespace std;

int main() {

    /*

        implementar en español?
        implementar para celular?
        
        ** implementar warning de tries
        **   "   "     para solo palabra diaria
        **   "   "     resultado con significado desde base de datos 
    
    */

    welcome();

    // Keeps game running
    do {

    generateProblem();
    cout << endl;

    } while (true);
    

    colorText(" ", reset);

    return 0;
}