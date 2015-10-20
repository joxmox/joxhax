/*
 * BufferPosition.cpp
 *
 *  Created on: Oct 20, 2015
 *      Author: joxmox
 */

#include "BufferPosition.hpp"

BufferPosition::BufferPosition() {
	this->row = 0;
	this->col = 0;
}

BufferPosition::BufferPosition(int row, int col) {
	this->row = row;
	this->col = col;
}

int BufferPosition::getCol() {
	return this->col;
}

int BufferPosition::getRow() {
	return this->row;
}

bool BufferPosition::onScreen() {
	return true;
}

void BufferPosition::operator ++() {
	this->row++;
}



