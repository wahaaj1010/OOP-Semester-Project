#include "Piece.h"
#include <cmath>

// ══════════════════════════════════════════════════════════════
//  Piece  (base)
// ══════════════════════════════════════════════════════════════
Piece::Piece(char color, int row, int col, char symbol)
    : color(color), row(row), col(col), symbol(symbol) {}

char Piece::getColor() const { return color; }
int  Piece::getRow()   const { return row;   }
int  Piece::getCol()   const { return col;   }

void Piece::setPosition(int r, int c) { row = r; col = c; }


// ══════════════════════════════════════════════════════════════
//  Pawn
// ══════════════════════════════════════════════════════════════
Pawn::Pawn(char color, int row, int col)
    : Piece(color, row, col, 'P') {}

bool Pawn::isValidMove(int toRow, int toCol) const {
    int dc = abs(toCol - col);
    int dr = toRow - row;

    if (color == 'W') {
        // White moves toward lower row numbers (up the board)
        if (dc == 0 && dr == -1) return true;           // 1 step forward
        if (dc == 0 && dr == -2 && row == 6) return true; // 2 steps from start row
        if (dc == 1 && dr == -1) return true;           // diagonal capture
    } else {
        // Black moves toward higher row numbers (down the board)
        if (dc == 0 && dr == 1) return true;
        if (dc == 0 && dr == 2 && row == 1) return true;
        if (dc == 1 && dr == 1) return true;
    }
    return false;
}


// ══════════════════════════════════════════════════════════════
//  Rook
// ══════════════════════════════════════════════════════════════
Rook::Rook(char color, int row, int col)
    : Piece(color, row, col, 'R') {}

bool Rook::isValidMove(int toRow, int toCol) const {
    if (toRow == row && toCol == col) return false;
    return (toRow == row || toCol == col);
}


// ══════════════════════════════════════════════════════════════
//  Knight
// ══════════════════════════════════════════════════════════════
Knight::Knight(char color, int row, int col)
    : Piece(color, row, col, 'N') {}

bool Knight::isValidMove(int toRow, int toCol) const {
    int dr = abs(toRow - row);
    int dc = abs(toCol - col);
    return (dr == 2 && dc == 1) || (dr == 1 && dc == 2);
}


// ══════════════════════════════════════════════════════════════
//  Bishop
// ══════════════════════════════════════════════════════════════
Bishop::Bishop(char color, int row, int col)
    : Piece(color, row, col, 'B') {}

bool Bishop::isValidMove(int toRow, int toCol) const {
    if (toRow == row && toCol == col) return false;
    return abs(toRow - row) == abs(toCol - col);
}


// ══════════════════════════════════════════════════════════════
//  Queen
// ══════════════════════════════════════════════════════════════
Queen::Queen(char color, int row, int col)
    : Piece(color, row, col, 'Q') {}

bool Queen::isValidMove(int toRow, int toCol) const {
    if (toRow == row && toCol == col) return false;
    int dr = abs(toRow - row);
    int dc = abs(toCol - col);
    return (toRow == row || toCol == col || dr == dc);
}


// ══════════════════════════════════════════════════════════════
//  King
// ══════════════════════════════════════════════════════════════
King::King(char color, int row, int col)
    : Piece(color, row, col, 'K') {}

bool King::isValidMove(int toRow, int toCol) const {
    int dr = abs(toRow - row);
    int dc = abs(toCol - col);
    return (dr <= 1 && dc <= 1 && !(dr == 0 && dc == 0));
}
