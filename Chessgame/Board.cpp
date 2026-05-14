#include "Board.h"
#include <iostream>
using namespace std;
//Added ANSI COLORS to board display for visuals
#define RESET      "\033[0m"
#define BOLD       "\033[1m"

#define BG_LIGHT   "\033[48;5;250m"   // silver squares
#define BG_DARK    "\033[48;5;18m"    // dark blue squares

#define FG_WHITE   "\033[30m"         // white pieces
#define FG_BLACK   "\033[30m"         // black pieces

#define FG_LABEL   "\033[38;5;111m"   // light blue labels

//Constructor
Board::Board() {
    for (int r = 0; r < 8; r++)
        for (int c = 0; c < 8; c++)
            grid[r][c] = nullptr;
}



//  Destructor

Board::~Board() {
    for (int r = 0; r < 8; r++)
        for (int c = 0; c < 8; c++) {
            delete grid[r][c];
            grid[r][c] = nullptr;
        }
}
//Implemented  setup() to place all pieces in starting positions

void Board::setup() {
    //Added console display function with rank and file labels
        // Black back rank
    grid[0][0] = new Rook('B', 0, 0);
    grid[0][1] = new Knight('B', 0, 1);
    grid[0][2] = new Bishop('B', 0, 2);
    grid[0][3] = new Queen('B', 0, 3);
    grid[0][4] = new King('B', 0, 4);
    grid[0][5] = new Bishop('B', 0, 5);
    grid[0][6] = new Knight('B', 0, 6);
    grid[0][7] = new Rook('B', 0, 7);

    // Black pawns
    for (int c = 0; c < 8; c++)
        grid[1][c] = new Pawn('B', 1, c);

    // White pawns
    for (int c = 0; c < 8; c++)
        grid[6][c] = new Pawn('W', 6, c);

    // White back rank
    grid[7][0] = new Rook('W', 7, 0);
    grid[7][1] = new Knight('W', 7, 1);
    grid[7][2] = new Bishop('W', 7, 2);
    grid[7][3] = new Queen('W', 7, 3);
    grid[7][4] = new King('W', 7, 4);
    grid[7][5] = new Bishop('W', 7, 5);
    grid[7][6] = new Knight('W', 7, 6);
    grid[7][7] = new Rook('W', 7, 7);
}
//  display
// Added Console display function with ranks and file labels
void Board::display() {

    cout << "\n";
    cout << FG_LABEL << "      a    b    c    d    e    f    g    h\n" << RESET;

    for (int r = 0; r < 8; r++) {

        int rank = 8 - r;

        cout << FG_LABEL << BOLD << "  " << rank << " " << RESET;

        for (int c = 0; c < 8; c++) {

            bool isLightSquare = (r + c) % 2 == 0;
            const char* bg = isLightSquare ? BG_LIGHT : BG_DARK;

            Piece* p = grid[r][c];

            if (!p) {

                cout << bg << "     " << RESET;
            }
            else {

                char sym = p->getSymbol();

                // Black pieces → lowercase
                if (p->getColor() == 'B')
                    sym = (char)(sym + 32);

                const char* fg =
                    (p->getColor() == 'W') ? FG_WHITE : FG_BLACK;

                cout << bg << fg << BOLD
                    << "  " << sym << "  "
                    << RESET;
            }
        }

        cout << FG_LABEL << BOLD << " " << rank << RESET << "\n";
    }

    cout << FG_LABEL << "      a    b    c    d    e    f    g    h\n"
        << RESET << "\n";
}

