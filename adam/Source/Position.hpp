/*
 * FilePosition.hpp
 *
 *  Created on: Oct 20, 2015
 *      Author: joxmox
 */

#ifndef POSITION_HPP_
#define POSITION_HPP_

class Position {
	int row;
	int col;
public:
	Position();
	Position(int row, int col);
	int getCol();
	int getRow();
	bool onScreen();
	void setPos(int row, int col);
	void operator ++();
	void operator ++(int) {++(*this);}
	void operator --();
	void operator --(int) {--(*this);}
};



#endif /* POSITION_HPP_ */