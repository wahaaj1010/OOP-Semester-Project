#include "Piece.h"
#include <cmath>

Piece::Piece(char color, int row, int col, char symbol) : color(color), row(row), col(col), symbol(symbol) {}

char Piece::getColor() const { return color; }
int  Piece::getRow()   const { return row; }
int  Piece::getCol()   const { return col; }

void Piece::setPosition(int r, int c) { row = r; col = c; }

//pawn
Pawn::Pawn(char color, int row, int col) : Piece(color, row, col, 'P') {}

bool Pawn::isValidMove(int toRow, int toCol) const {
    int dc = abs(toCol - col);
    int dr = toRow - row;

    if (color == 'W') {
        if (dc == 0 && dr == -1) return true;           // 1 step forward
        if (dc == 0 && dr == -2 && row == 6) return true; // 2 steps from start row
        if (dc == 1 && dr == -1) return true;           // diagonal 
    }
    else {
        if (dc == 0 && dr == 1) return true;
        if (dc == 0 && dr == 2 && row == 1) return true;
        if (dc == 1 && dr == 1) return true;
    }
    return false;
}

//rook
Rook::Rook(char color, int row, int col) : Piece(color, row, col, 'R') {}

bool Rook::isValidMove(int toRow, int toCol) const {
    if (toRow == row && toCol == col) return false;
    return (toRow == row || toCol == col);
}

//knight
Knight::Knight(char color, int row, int col) : Piece(color, row, col, 'N') {}

bool Knight::isValidMove(int toRow, int toCol) const {
    int dr = abs(toRow - row);
    int dc = abs(toCol - col);
    return (dr == 2 && dc == 1) || (dr == 1 && dc == 2);
}

//bishop
Bishop::Bishop(char color, int row, int col) : Piece(color, row, col, 'B') {}

bool Bishop::isValidMove(int toRow, int toCol) const {
    if (toRow == row && toCol == col) return false;
    return abs(toRow - row) == abs(toCol - col);
}

//queen
Queen::Queen(char color, int row, int col) : Piece(color, row, col, 'Q') {}

bool Queen::isValidMove(int toRow, int toCol) const {
    if (toRow == row && toCol == col) return false;
    int dr = abs(toRow - row);
    int dc = abs(toCol - col);
    return (toRow == row || toCol == col || dr == dc);
}

//king
King::King(char color, int row, int col) : Piece(color, row, col, 'K') {}

bool King::isValidMove(int toRow, int toCol) const {
    int dr = abs(toRow - row);
    int dc = abs(toCol - col);
    return (dr <= 1 && dc <= 1 && !(dr == 0 && dc == 0));
}
