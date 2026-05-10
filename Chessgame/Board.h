#pragma once
#include "Piece.h"

// ══════════════════════════════════════════════════════════════
//  Board class
//  Demonstrates: Composition (Board "has" Piece objects)
// // ══════════════════════════════════════════════════════════════
class Board {
public:
    Piece* grid[8][8];   // grid[row][col], row 0 = rank 8 (Black back rank)

    Board();
    ~Board();

    void setup();     // place all pieces in starting positions
    void display();   // print the board to console
};
