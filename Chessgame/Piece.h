#pragma once
#include <iostream>
#include <string>
using namespace std;

class Piece {
protected:
    char   color;    // 'W' = White,  'B' = Black
    int    row;      // 0-7  (0 = rank 8, 7 = rank 1)
    int    col;      // 0-7  (0 = file a, 7 = file h)
    char   symbol;   // P R N B Q K

public:
    Piece(char color, int row, int col, char symbol);
    virtual ~Piece() {}

    virtual bool isValidMove(int toRow, int toCol) const = 0;

    virtual string getName()   const = 0;
    virtual char   getSymbol() const { return symbol; }

    char getColor() const;
    int  getRow()   const;
    int  getCol()   const;

    void setPosition(int r, int c);
};

class Pawn : public Piece {
public:
    Pawn(char color, int row, int col);
    bool   isValidMove(int toRow, int toCol) const override;
    string getName() const override { return "Pawn"; }
};

class Rook : public Piece {
public:
    Rook(char color, int row, int col);
    bool   isValidMove(int toRow, int toCol) const override;
    string getName() const override { return "Rook"; }
};

class Knight : public Piece {
public:
    Knight(char color, int row, int col);
    bool   isValidMove(int toRow, int toCol) const override;
    string getName() const override { return "Knight"; }
};

class Bishop : public Piece {
public:
    Bishop(char color, int row, int col);
    bool   isValidMove(int toRow, int toCol) const override;
    string getName() const override { return "Bishop"; }
};

class Queen : public Piece {
public:
    Queen(char color, int row, int col);
    bool   isValidMove(int toRow, int toCol) const override;
    string getName() const override { return "Queen"; }
};

class King : public Piece {
public:
    King(char color, int row, int col);
    bool   isValidMove(int toRow, int toCol) const override;
    string getName() const override { return "King"; }
};
