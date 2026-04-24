Overview
A fully functional two-player chess game built in C++ using core Object-Oriented Programming principles. The game runs in the console and allows two players to take turns making valid moves according to standard chess rules.

🎯 Features

✅ 8×8 console-rendered chessboard with piece symbols
✅ All 6 chess pieces with correct movement rules
✅ Turn-based system (White moves first)
✅ Full move validation — illegal moves are rejected
✅ Piece capture
✅ Check detection
✅ Checkmate detection with winner announcement
⭕ Stalemate / draw detection (optional)
🌟 Graphical UI (bonus)

🗂️ Class Structure
Piece  (abstract base class)
├── Pawn
├── Rook
├── Knight
├── Bishop
├── Queen
└── King

Board  (contains Piece objects — composition)
Game   (manages turns, input, win conditions)


📁 Project Structure
chess-game-oop/
│
├── main.cpp           # Entry point
├── Piece.h / .cpp     # Abstract base class
├── Pawn.h / .cpp
├── Rook.h / .cpp
├── Knight.h / .cpp
├── Bishop.h / .cpp
├── Queen.h / .cpp
├── King.h / .cpp
├── Board.h / .cpp     # Board management
├── Game.h / .cpp      # Game loop and rules
└── README.md

👥 Group Members
25F-0100 Muhammad Wahaaj Humayun, 25F-0033 Uswa Abdullah, 25F-0081 Momna Amir
