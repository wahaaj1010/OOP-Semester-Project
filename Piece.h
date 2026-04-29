#pragma once
#ifndef PIECE_H
#define PIECE_H

#include <string>
using namespace std;

// ══════════════════════════════════════════════════════════════
//  Abstract base class — Piece
//  Demonstrates: Encapsulation, Abstraction, Polymorphism base
// ══════════════════════════════════════════════════════════════
class Piece {
protected:
    char   color;    // 'W' = White,  'B' = Black
    int    row;      // 0-7  (0 = rank 8, 7 = rank 1)
    int    col;      // 0-7  (0 = file a, 7 = file h)
    char   symbol;   // P R N B Q K

public:
    Piece(char color, int row, int col, char symbol);
    virtual ~Piece() {}

    // Pure virtual: every derived class MUST override
    virtual bool isValidMove(int toRow, int toCol) const = 0;

    // Virtual: derived classes may override for display
    virtual string getName()   const = 0;
    virtual char   getSymbol() const { return symbol; }

    // Getters (Encapsulation)
    char getColor() const;
    int  getRow()   const;
    int  getCol()   const;

    // Setter
    void setPosition(int r, int c);
};


// ══════════════════════════════════════════════════════════════
//  Pawn   — 1 step forward (2 from start), diagonal capture
// ══════════════════════════════════════════════════════════════
class Pawn : public Piece {
public:
    Pawn(char color, int row, int col);
    bool   isValidMove(int toRow, int toCol) const override;
    string getName() const override { return "Pawn"; }
};


// ══════════════════════════════════════════════════════════════
//  Rook   — any number of squares horizontally or vertically
// ══════════════════════════════════════════════════════════════
class Rook : public Piece {
public:
    Rook(char color, int row, int col);
    bool   isValidMove(int toRow, int toCol) const override;
    string getName() const override { return "Rook"; }
};


// ══════════════════════════════════════════════════════════════
//  Knight — L-shape: (+-2,+-1) or (+-1,+-2); jumps over pieces
// ══════════════════════════════════════════════════════════════
class Knight : public Piece {
public:
    Knight(char color, int row, int col);
    bool   isValidMove(int toRow, int toCol) const override;
    string getName() const override { return "Knight"; }
};


// ══════════════════════════════════════════════════════════════
//  Bishop — any number of squares diagonally
// ══════════════════════════════════════════════════════════════
class Bishop : public Piece {
public:
    Bishop(char color, int row, int col);
    bool   isValidMove(int toRow, int toCol) const override;
    string getName() const override { return "Bishop"; }
};


// ══════════════════════════════════════════════════════════════
//  Queen  — combines Rook + Bishop movement
// ══════════════════════════════════════════════════════════════
class Queen : public Piece {
public:
    Queen(char color, int row, int col);
    bool   isValidMove(int toRow, int toCol) const override;
    string getName() const override { return "Queen"; }
};


// ══════════════════════════════════════════════════════════════
//  King   — exactly 1 square in any direction
// ══════════════════════════════════════════════════════════════
class King : public Piece {
public:
    King(char color, int row, int col);
    bool   isValidMove(int toRow, int toCol) const override;
    string getName() const override { return "King"; }
};

#endif // PIECE_H
