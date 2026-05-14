#include "Game.h"
#include <iostream>
#include <sstream>
#include <cmath>
#include <stdexcept>
using namespace std;


// ── clearScreen ─────────────────────────────────────────────
// Clears the terminal. Uses "cls" on Windows, "clear" elsewhere.

void Game::clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}


// ── Constructor ──────────────────────────────────────────────

Game::Game() : currentTurn('W'), gameOver(false) {
    board.setup();
}


// ── parseInput ───────────────────────────────────────────────
// Converts "e2 e4" -> fromRow=6, fromCol=4, toRow=4, toCol=4
// Files: a=0  b=1  c=2  d=3  e=4  f=5  g=6  h=7
// Ranks: 1=7  2=6  3=5  4=4  5=3  6=2  7=1  8=0

bool Game::parseInput(const string& input,
                      int& fromRow, int& fromCol,
                      int& toRow,   int& toCol) {

    if (input.size() < 5)
        throw invalid_argument("Input too short. Use format: e2 e4");

    char fc = input[0];
    char fr = input[1];
    char tc = input[3];
    char tr = input[4];

    if (fc < 'a' || fc > 'h' || tc < 'a' || tc > 'h')
        throw invalid_argument("File must be between a and h.");
    if (fr < '1' || fr > '8' || tr < '1' || tr > '8')
        throw invalid_argument("Rank must be between 1 and 8.");

    fromCol = fc - 'a';
    fromRow = 8 - (fr - '0');
    toCol   = tc - 'a';
    toRow   = 8 - (tr - '0');

    return true;
}


// ── isPathClear ──────────────────────────────────────────────
// Checks every square between from and to (exclusive).
// Used for R, B, Q — Knight skips this.

bool Game::isPathClear(int fromRow, int fromCol, int toRow, int toCol) {
    int dr = 0, dc = 0;

    if (toRow > fromRow) dr = 1;
    else if (toRow < fromRow) dr = -1;

    if (toCol > fromCol) dc = 1;
    else if (toCol < fromCol) dc = -1;

    int r = fromRow + dr;
    int c = fromCol + dc;

    while (r != toRow || c != toCol) {
        if (r < 0 || r > 7 || c < 0 || c > 7)
            throw invalid_argument("Path check went out of board bounds.");
        if (board.grid[r][c] != nullptr) return false;
        r += dr;
        c += dc;
    }
    return true;
}


