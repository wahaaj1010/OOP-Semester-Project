# ♟️ Chess Game in C++
### OOP Semester Project — National University of Computer & Emerging Sciences, Faisalabad

---

## 📖 Description

A fully functional two-player chess game built in **C++** using core Object-Oriented Programming principles. The game runs in the console and allows two players to take turns making valid moves according to standard chess rules. It demonstrates encapsulation, inheritance, polymorphism, and composition through a structured class hierarchy of chess pieces managed by a central Board class.

---

## 👥 Group Members

### 25F-0033 — Uswa Abdullah
- Create base `Piece` class with common attributes (color, position, symbol)
- Add pure virtual function `isValidMove()` to `Piece` for polymorphism
- Create `Pawn` class — move validation 
- Create `Rook` class — move validation
- Create `Knight` class — move validation
- Create `Bishop` class — move validation
- Create `Queen` class — move validation
- Create `King` class — move validation 

### 25F-0081 — Momna Amir
- Create `Board` class (8×8 grid) storing and managing `Piece` objects
- Place all pieces in correct starting positions at game start
- Display the board in the console using text symbols

### 25F-0100 — Muhammad Wahaaj Humayun
- Implement input system for players to enter moves (e.g. `e2 e4`)
- Implement turn system — White moves first, then alternate
- Validate that a move is legal before applying it to the board
- Handle piece capture — remove captured piece from the board
- Detect when the King is in check
- Detect checkmate and end the game with a winner message
- *(Stalemate / draw detection missing)*

---

## 📁 Project Structure

```
chess-game-oop/
│
├── Piece.h / Piece.cpp      # Abstract base class + all 6 piece classes
├── Board.h / Board.cpp      # Board management and display
├── Game.h / Game.cpp        # Game loop, input, turns, and win conditions
├── main.cpp                 # Entry point
└── README.md
```
