#include "Game.h"
#include <iostream>
#include <string>
using namespace std;

// Clear the terminal screen
void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

// Show help instructions
void showHelp() {
    clearScreen();
    cout << "\n  +----------------------------------+\n";
    cout << "  |          HOW TO PLAY             |\n";
    cout << "  +----------------------------------+\n\n";
    cout << "  Enter moves in this format:  e2 e4\n\n";
    cout << "  File (column) : a - h  (left to right)\n";
    cout << "  Rank (row)    : 1 - 8  (bottom to top)\n\n";
    cout << "  Pieces:  P = Pawn    R = Rook\n";
    cout << "           N = Knight  B = Bishop\n";
    cout << "           Q = Queen   K = King\n\n";
    cout << "  White pieces = UPPERCASE\n";
    cout << "  Black pieces = lowercase\n\n";
    cout << "  Press Enter to go back...\n";
    cin.get();
}

int main() {
    while (true) {
        clearScreen();
        cout << "\n  +----------------------------------+\n";
        cout << "  |          CHESS GAME              |\n";
        cout << "  +----------------------------------+\n\n";
        cout << "  1.  Start Game\n";
        cout << "  2.  Help\n";
        cout << "  3.  Exit\n\n";
        cout << "  Choose an option: ";

        string choice;
        getline(cin, choice);

        if (choice == "1") {
            Game game;
            game.run();
        } else if (choice == "2") {
            showHelp();
        } else if (choice == "3") {
            clearScreen();
            cout << "\n  Goodbye!\n\n";
            break;
        } else {
            cout << "\n  Invalid option. Press Enter to try again...\n";
            cin.get();
        }
    }
    return 0;
}
