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


// ── isInCheck ────────────────────────────────────────────────
// Finds the King, then checks if any opponent piece can reach it.

bool Game::isInCheck(char color) {
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

    if (kingRow == -1)
        throw invalid_argument("King not found. Game state is corrupted.");

    char opponent = (color == 'W') ? 'B' : 'W';
    for (int r = 0; r < 8; r++) {
        for (int c = 0; c < 8; c++) {
            Piece* p = board.grid[r][c];
            if (!p || p->getColor() != opponent) continue;

            if (p->isValidMove(kingRow, kingCol)) {
                char sym = p->getSymbol();
                if (sym == 'N') return true;
                // Pawns attack diagonally — isValidMove already checks that,
                // so if it returned true it must be a diagonal move to the king.
                if (sym == 'P') return true;
                if (isPathClear(r, c, kingRow, kingCol)) return true;
            }
        }
    }
    return false;
}


// ── hasAnyLegalMove ──────────────────────────────────────────
// Tries every move for every piece of the given color.
// Returns true if at least one move doesn't leave the King in check.
// IMPORTANT: pawn capture/push rules are enforced here too, exactly
// mirroring the checks done in run(), so we don't count illegal
// pawn moves as "escapes" and miss checkmate.

bool Game::hasAnyLegalMove(char color) {
    for (int fr = 0; fr < 8; fr++) {
        for (int fc = 0; fc < 8; fc++) {
            Piece* p = board.grid[fr][fc];
            if (!p || p->getColor() != color) continue;

            for (int tr = 0; tr < 8; tr++) {
                for (int tc = 0; tc < 8; tc++) {

                    // 1. Piece-level move geometry
                    try { if (!p->isValidMove(tr, tc)) continue; }
                    catch (...) { continue; }

                    // 2. Path must be clear (except Knights)
                    try {
                        if (p->getSymbol() != 'N' && !isPathClear(fr, fc, tr, tc))
                            continue;
                    } catch (...) { continue; }

                    Piece* dest = board.grid[tr][tc];

                    // 3. Cannot capture own piece
                    if (dest && dest->getColor() == color) continue;

                    // 4. Pawn-specific capture / push rules
                    //    (same logic as in run() — MUST match or checkmate is missed)
                    if (p->getSymbol() == 'P') {
                        bool isDiagonal = (abs(tc - fc) == 1);
                        if (isDiagonal && !dest) continue;   // diagonal needs a victim
                        if (!isDiagonal && dest) continue;   // straight push blocked
                    }

                    // 5. Try the move on the board
                    board.grid[tr][tc] = p;
                    board.grid[fr][fc] = nullptr;
                    p->setPosition(tr, tc);

                    bool stillInCheck = false;
                    try { stillInCheck = isInCheck(color); } catch (...) {}

                    // Undo
                    board.grid[fr][fc] = p;
                    board.grid[tr][tc] = dest;
                    p->setPosition(fr, fc);

                    if (!stillInCheck) return true;   // found at least one legal move
                }
            }
        }
    }
    return false;   // no legal move exists → checkmate (or stalemate)
}


// ── run ──────────────────────────────────────────────────────
// Main game loop.

void Game::run() {
    while (!gameOver) {
        clearScreen();
        board.display();

        string playerName = (currentTurn == 'W') ? "White" : "Black";
        cout << "\n  " << playerName << "'s turn: ";

        string input;
        getline(cin, input);

        try {
            int fromRow, fromCol, toRow, toCol;
            parseInput(input, fromRow, fromCol, toRow, toCol);

            Piece* piece = board.grid[fromRow][fromCol];

            if (!piece)
                throw invalid_argument("No piece at that square.");

            if (piece->getColor() != currentTurn)
                throw invalid_argument("That is not your piece.");

            if (!piece->isValidMove(toRow, toCol))
                throw invalid_argument("Invalid move for " + piece->getName() + ".");

            if (piece->getSymbol() != 'N' && !isPathClear(fromRow, fromCol, toRow, toCol))
                throw invalid_argument("Path is blocked.");

            Piece* dest = board.grid[toRow][toCol];

            if (dest && dest->getColor() == currentTurn)
                throw invalid_argument("You cannot capture your own piece.");

            // Pawn diagonal/straight capture rules
            if (piece->getSymbol() == 'P') {
                bool isDiagonal = (abs(toCol - fromCol) == 1);
                if (isDiagonal && !dest)
                    throw invalid_argument("Pawns can only move diagonally to capture.");
                if (!isDiagonal && dest)
                    throw invalid_argument("Pawns cannot capture straight ahead.");
            }

            // Apply the move
            board.grid[toRow][toCol]     = piece;
            board.grid[fromRow][fromCol] = nullptr;
            piece->setPosition(toRow, toCol);

            // Undo if move leaves own King in check
            if (isInCheck(currentTurn)) {
                board.grid[fromRow][fromCol] = piece;
                board.grid[toRow][toCol]     = dest;
                piece->setPosition(fromRow, fromCol);
                throw invalid_argument("That move puts your King in check.");
            }

            // Move is legal — delete captured piece
            delete dest;

            // Switch turn
            currentTurn = (currentTurn == 'W') ? 'B' : 'W';

            // Check opponent status
            if (isInCheck(currentTurn)) {
                if (!hasAnyLegalMove(currentTurn)) {
                    // ── CHECKMATE ──────────────────────────────────────────
                    clearScreen();
                    board.display();
                    string winner = (currentTurn == 'W') ? "Black" : "White";
                    cout << "\n  Checkmate!  " << winner << " wins!\n\n";
                    cout << "  Press Enter to return to menu...";
                    cin.get();          // wait for one Enter
                    gameOver = true;    // exits run() → returns to main menu
                } else {
                    cout << "  Check!\n";
                    cout << "  Press Enter to continue...";
                    cin.get();
                }
            } else if (!hasAnyLegalMove(currentTurn)) {
                // ── STALEMATE ──────────────────────────────────────────────
                clearScreen();
                board.display();
                cout << "\n  Stalemate!  It's a draw.\n\n";
                cout << "  Press Enter to return to menu...";
                cin.get();
                gameOver = true;
            }

        } catch (const invalid_argument& e) {
            cout << "  Error: " << e.what() << "\n";
            cout << "  Press Enter to try again...";
            cin.get();
        } catch (const exception& e) {
            cout << "  Fatal error: " << e.what() << "\n";
            cin.get();
            gameOver = true;
        }
    }
}
