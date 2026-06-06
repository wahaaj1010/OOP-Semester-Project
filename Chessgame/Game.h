#pragma once
#include "Board.h"
#include <string>
using namespace std;

// ══════════════════════════════════════════════════════════════
//  Game class
//  Handles: input, turns, validation, capture, check, checkmate
// ══════════════════════════════════════════════════════════════

class Game {
private:
    Board  board;
    char   currentTurn;   // 'W' or 'B'
    bool   gameOver;

    // Screen
    void clearScreen();

    // Input
    bool parseInput(const string& input, int& fromRow, int& fromCol,
                                         int& toRow,   int& toCol);

    // Path checking (for Rook, Bishop, Queen)
    bool isPathClear(int fromRow, int fromCol, int toRow, int toCol);

    // Check / Checkmate
    bool isInCheck(char color);
    bool hasAnyLegalMove(char color);

public:
    Game();
    void run();   // main game loop
};
