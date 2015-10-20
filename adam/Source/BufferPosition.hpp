/*
 * FilePosition.hpp
 *
 *  Created on: Oct 20, 2015
 *      Author: joxmox
 */

#ifndef BUFFERPOSITION_HPP_
#define BUFFERPOSITION_HPP_

class BufferPosition {
	int row;
	int col;
public:
	BufferPosition();
	BufferPosition(int row, int col);
	int getCol();
	int getRow();
	bool onScreen();
	void operator ++();
	void operator ++(int) {++(*this);}
	void operator --();
	void operator --(int) {--(*this);}
};



#endif /* BUFFERPOSITION_HPP_ */
