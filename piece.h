#pragma once
#include <iostream>

using namespace std;

class piece
{
protected:
	string colour, symbol;
	int pos1, pos2; //positions
	
public:
	piece(string c, string s, int p1, int p2);

	virtual bool isValidMove(int newP1, int newP2);
	void setPosition(int newP1, int newP2);
	void display();
	virtual ~piece();
};
