/*
 * FilePosition.hpp
 *
 *  Created on: Oct 20, 2015
 *      Author: joxmox
 */

#pragma once

#include <iostream>
#include <string>

#define NULLPOS Position {0, 0}
#define NOPOS Position {-1, -1}

class Position {
	int row;
	int col;
public:
	Position(int row = 0, int col = 0);
	int getCol() const;
	int getRow() const;
	int setCol(int);
	int setRow(int);
	void moveUp();
	void moveDown();
	void moveLeft();
	void moveRight();
	bool onScreen() const;
	void setPos(int row, int col);
	bool operator ==(Position);
	bool operator !=(Position);
	Position operator ++();
	Position operator ++(int);
	Position operator --();
	Position operator --(int);
	Position operator -(Position);
	Position operator +(Position);
	Position operator +=(Position);
	Position operator -=(Position);
	std::string toString() const;
};

std::ostream& operator <<(std::ostream& os, const Position& p);
