#include "Game.h"
#include <iostream>
#include <string>
using namespace std;
int main() {
    while (true) {
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
            cout << "\n  Goodbye!\n\n";
            break;
        } else {
            cout << "\n  Invalid option. Press Enter to try again...\n";
            cin.get();
        }
    }
    return 0;
}
