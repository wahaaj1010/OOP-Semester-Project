#include "Board.h"
#include <iostream>
using namespace std;
//Added ANSI COLORS to board display for visuals
#define RESET      "\033[0m"
#define BOLD       "\033[1m"

#define BG_LIGHT   "\033[48;5;250m"   // silver squares
#define BG_DARK    "\033[48;5;18m"    // dark blue squares

#define FG_WHITE   "\033[30m"         // white pieces
#define FG_BLACK   "\033[30m"         // black pieces

#define FG_LABEL   "\033[38;5;111m"   // light blue labels
