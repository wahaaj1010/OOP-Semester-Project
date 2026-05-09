#include "Game.h"
#include <iostream>
#include <sstream>
#include <cmath>
using namespace std;

// ══════════════════════════════════════════════════════════════
//  Constructor
// ══════════════════════════════════════════════════════════════
Game::Game() : currentTurn('W'), gameOver(false) {
    board.setup();   // NOTE: update if Momna names this differently
}


// ══════════════════════════════════════════════════════════════
//  parseInput
//  Converts "e2 e4" → fromRow=6, fromCol=4, toRow=4, toCol=4
//  Files: a=0  b=1  c=2  d=3  e=4  f=5  g=6  h=7
//  Ranks: 1=7  2=6  3=5  4=4  5=3  6=2  7=1  8=0
// ══════════════════════════════════════════════════════════════
bool Game::parseInput(const string& input,
                      int& fromRow, int& fromCol,
                      int& toRow,   int& toCol) {
    // Expected format: "e2 e4"  (5 characters including space)
    if (input.size() < 5) return false;

    char fc = input[0];   // from file  (a-h)
    char fr = input[1];   // from rank  (1-8)
    char tc = input[3];   // to file
    char tr = input[4];   // to rank

    if (fc < 'a' || fc > 'h') return false;
    if (tc < 'a' || tc > 'h') return false;
    if (fr < '1' || fr > '8') return false;
    if (tr < '1' || tr > '8') return false;

    fromCol = fc - 'a';
    fromRow = 8 - (fr - '0');
    toCol   = tc - 'a';
    toRow   = 8 - (tr - '0');

    return true;
}


// ══════════════════════════════════════════════════════════════
//  isPathClear
//  Checks every square between from and to (exclusive).
//  Used for Rook, Bishop, Queen — Knight skips this.
// ══════════════════════════════════════════════════════════════
bool Game::isPathClear(int fromRow, int fromCol, int toRow, int toCol) {
    int dr = 0, dc = 0;

    if (toRow > fromRow) dr = 1;
    else if (toRow < fromRow) dr = -1;

    if (toCol > fromCol) dc = 1;
    else if (toCol < fromCol) dc = -1;

    int r = fromRow + dr;
    int c = fromCol + dc;

    while (r != toRow || c != toCol) {
        if (board.grid[r][c] != nullptr) return false;  // something is blocking
        r += dr;
        c += dc;
    }
    return true;
}


// ══════════════════════════════════════════════════════════════
//  isInCheck
//  Scans all opponent pieces and checks if any can reach
//  the current player's King.
// ══════════════════════════════════════════════════════════════
bool Game::isInCheck(char color) {
    // Find the King's position
    int kingRow = -1, kingCol = -1;
    for (int r = 0; r < 8; r++) {
        for (int c = 0; c < 8; c++) {
            Piece* p = board.grid[r][c];
            if (p && p->getColor() == color && p->getSymbol() == 'K') {
                kingRow = r;
                kingCol = c;
            }
        }
    }
    if (kingRow == -1) return false;  // King not found (shouldn't happen)

    // Check if any opponent piece can move to the King's square
    char opponent = (color == 'W') ? 'B' : 'W';
    for (int r = 0; r < 8; r++) {
        for (int c = 0; c < 8; c++) {
            Piece* p = board.grid[r][c];
            if (!p || p->getColor() != opponent) continue;

            if (p->isValidMove(kingRow, kingCol)) {
                // Knights jump — no path check needed
                char sym = p->getSymbol();
                if (sym == 'N') return true;
                if (isPathClear(r, c, kingRow, kingCol)) return true;
            }
        }
    }
    return false;
}


// ══════════════════════════════════════════════════════════════
//  hasAnyLegalMove
//  Tries every possible move for every piece of the given color.
//  If at least one move exists that doesn't leave King in check
//  → not checkmate.
// ══════════════════════════════════════════════════════════════
bool Game::hasAnyLegalMove(char color) {
    for (int fr = 0; fr < 8; fr++) {
        for (int fc = 0; fc < 8; fc++) {
            Piece* p = board.grid[fr][fc];
            if (!p || p->getColor() != color) continue;

            for (int tr = 0; tr < 8; tr++) {
                for (int tc = 0; tc < 8; tc++) {
                    if (!p->isValidMove(tr, tc)) continue;

                    // Skip if path is blocked (except Knight)
                    if (p->getSymbol() != 'N' && !isPathClear(fr, fc, tr, tc))
                        continue;

                    // Skip if destination has a friendly piece
                    Piece* dest = board.grid[tr][tc];
                    if (dest && dest->getColor() == color) continue;

                    // Try the move temporarily
                    board.grid[tr][tc] = p;
                    board.grid[fr][fc] = nullptr;
                    p->setPosition(tr, tc);

                    bool stillInCheck = isInCheck(color);

                    // Undo the move
                    board.grid[fr][fc] = p;
                    board.grid[tr][tc] = dest;
                    p->setPosition(fr, fc);

                    if (!stillInCheck) return true;  // found a legal move
                }
            }
        }
    }
    return false;  // no legal moves found → checkmate
}


// ══════════════════════════════════════════════════════════════
//  run  —  Main game loop
// ══════════════════════════════════════════════════════════════
void Game::run() {
    cout << "\n  ♟  Welcome to Chess  ♟\n";
    cout << "  Enter moves like:  e2 e4\n\n";

    while (!gameOver) {
        // Display the board
        board.display();   // NOTE: update if Momna names this differently

        // Print whose turn it is
        string playerName = (currentTurn == 'W') ? "White" : "Black";
        cout << "\n  " << playerName << "'s turn: ";

        // Get input
        string input;
        getline(cin, input);

        // Parse input
        int fromRow, fromCol, toRow, toCol;
        if (!parseInput(input, fromRow, fromCol, toRow, toCol)) {
            cout << "  Invalid format. Use:  e2 e4\n";
            continue;
        }

        // Check there is a piece at the from-square
        Piece* piece = board.grid[fromRow][fromCol];
        if (!piece) {
            cout << "  No piece at that square.\n";
            continue;
        }

        // Check the piece belongs to the current player
        if (piece->getColor() != currentTurn) {
            cout << "  That is not your piece.\n";
            continue;
        }

        // Check the piece can move there (shape of move)
        if (!piece->isValidMove(toRow, toCol)) {
            cout << "  Invalid move for " << piece->getName() << ".\n";
            continue;
        }

        // Check path is clear (skip for Knight)
        if (piece->getSymbol() != 'N' && !isPathClear(fromRow, fromCol, toRow, toCol)) {
            cout << "  Path is blocked.\n";
            continue;
        }

        // Check destination is not occupied by a friendly piece
        Piece* dest = board.grid[toRow][toCol];
        if (dest && dest->getColor() == currentTurn) {
            cout << "  You cannot capture your own piece.\n";
            continue;
        }

        // Extra pawn rule: pawns can only move diagonally if capturing
        if (piece->getSymbol() == 'P') {
            bool isDiagonal = (abs(toCol - fromCol) == 1);
            if (isDiagonal && !dest) {
                cout << "  Pawns can only move diagonally to capture.\n";
                continue;
            }
            if (!isDiagonal && dest) {
                cout << "  Pawns cannot capture straight ahead.\n";
                continue;
            }
        }

        // Apply the move
        delete dest;                          // capture (nullptr-safe)
        board.grid[toRow][toCol]     = piece;
        board.grid[fromRow][fromCol] = nullptr;
        piece->setPosition(toRow, toCol);

        // Check if the move left our own King in check (illegal)
        if (isInCheck(currentTurn)) {
            // Undo
            board.grid[fromRow][fromCol] = piece;
            board.grid[toRow][toCol]     = dest;
            piece->setPosition(fromRow, fromCol);
            cout << "  You cannot move into check.\n";
            continue;
        }

        // Switch turn
        currentTurn = (currentTurn == 'W') ? 'B' : 'W';

        // Check if the opponent is now in check or checkmate
        if (isInCheck(currentTurn)) {
            if (!hasAnyLegalMove(currentTurn)) {
                board.display();
                string winner = (currentTurn == 'W') ? "Black" : "White";
                cout << "\n  Checkmate!  " << winner << " wins!\n\n";
                gameOver = true;
            } else {
                cout << "  Check!\n";
            }
        }
    }
}
