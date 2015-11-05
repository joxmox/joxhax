/*
 * BufferPosition.cpp
 *
 *  Created on: Oct 20, 2015
 *      Author: joxmox
 */

#include "Position.hpp"

Position::Position(int row, int col): row(row), col(col) {};

int Position::getCol() {
	return this->col;
}

int Position::getRow() {
	return this->row;
}

bool Position::onScreen() {
	return true;
}

void Position::setPos(int r, int c) {
	row = r;
	col = c;
}

void Position::operator ++() {
	this->row++;
}



