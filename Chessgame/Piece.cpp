#include "Piece.h"
#include <cmath>
#include <stdexcept>
#include <string>

using namespace std;

static void validateColor(char color)
{
    if (color != 'W' && color != 'B')
        throw invalid_argument (string("Invalid piece color '") + color + "'. Must be white or black.");
}

static void validateSquare(int row, int col, const string& context)
{
    if (row < 0 || row > 7 || col < 0 || col > 7)
        throw out_of_range (context + ": square (" + to_string(row) + ", " + to_string(col) + ") is outside the 8x8 board [0-7].");
}

//Piece base class

Piece::Piece(char color, int row, int col, char symbol) : color(color), row(row), col(col), symbol(symbol)
{
    validateColor(color);
    validateSquare(row, col, "Piece constructor");
}

char Piece::getColor() const
{
    return color;
}

int Piece::getRow() const
{
    return row;
}

int Piece::getCol() const
{
    return col;
}

void Piece::setPosition(int r, int c)
{
    validateSquare(r, c, "setPosition");

    row = r;
    col = c;
}

// Pawn
Pawn::Pawn(char color, int row, int col) : Piece(color, row, col, 'P') {}

bool Pawn::isValidMove(int toRow, int toCol) const
{
    validateSquare(toRow, toCol, "Pawn::isValidMove");

    if (toRow == row && toCol == col)
        throw invalid_argument ("Pawn::isValidMove: Same destination square");

    int dr = toRow - row;
    int dc = abs(toCol - col);

    if (color == 'W')
    {
        if (dc == 0 && dr == -1) return true;

        if (dc == 0 && dr == -2 && row == 6)
            return true;

        if (dc == 1 && dr == -1)
            return true;
    }
    else
    {
        if (dc == 0 && dr == 1) return true;

        if (dc == 0 && dr == 2 && row == 1)
            return true;

        if (dc == 1 && dr == 1)
            return true;
    }

    return false;
}

// rook

Rook::Rook(char color, int row, int col) : Piece(color, row, col, 'R') {}

bool Rook::isValidMove(int toRow, int toCol) const
{
    validateSquare(toRow, toCol, "Rook::isValidMove");

    if (toRow == row && toCol == col)
        throw invalid_argument ("Rook::isValidMove: Same destination square");

    return (toRow == row || toCol == col);
}

//Knight

Knight::Knight(char color, int row, int col) : Piece(color, row, col, 'N') {}

bool Knight::isValidMove(int toRow, int toCol) const
{
    validateSquare(toRow, toCol, "Knight::isValidMove");

    if (toRow == row && toCol == col)
        throw invalid_argument ("Knight::isValidMove: Same destination square");

    int dr = abs(toRow - row);
    int dc = abs(toCol - col);

    return (dr == 2 && dc == 1) || (dr == 1 && dc == 2);
}

// bishop

Bishop::Bishop(char color, int row, int col) : Piece(color, row, col, 'B') {}

bool Bishop::isValidMove(int toRow, int toCol) const
{
    validateSquare(toRow, toCol, "Bishop::isValidMove");

    if (toRow == row && toCol == col)
        throw invalid_argument ("Bishop::isValidMove: Same destination square");

    return abs(toRow - row) == abs(toCol - col);
}

//queen

Queen::Queen(char color, int row, int col)
    : Piece(color, row, col, 'Q') {
}

bool Queen::isValidMove(int toRow, int toCol) const
{
    validateSquare(toRow, toCol, "Queen::isValidMove");

    if (toRow == row && toCol == col)
        throw invalid_argument ("Queen::isValidMove: Same destination square");

    int dr = abs(toRow - row);
    int dc = abs(toCol - col);

    return (toRow == row || toCol == col || dr == dc);
}

//king

King::King(char color, int row, int col) : Piece(color, row, col, 'K') {}

bool King::isValidMove(int toRow, int toCol) const
{
    validateSquare(toRow, toCol, "King::isValidMove");

    if (toRow == row && toCol == col)
        throw invalid_argument ("King::isValidMove: Same destination square");

    int dr = abs(toRow - row);
    int dc = abs(toCol - col);

    return (dr <= 1 && dc <= 1);
}
