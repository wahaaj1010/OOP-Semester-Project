#pragma once
#include "Piece.h"


//  Board class
//  Composition (8 * 8 grid)

class Board {
public:
    Piece* grid[8][8];   // grid[row][col], row 0 = rank 8 (Black back rank)

    Board();
    ~Board();

    void setup();     // setting all pieces at starting positions
    void display();   // print the board 
};
