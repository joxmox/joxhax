/*
 * BufferPosition.cpp
 *
 *  Created on: Oct 20, 2015
 *      Author: joxmox
 */

#include "Position.hpp"

Position::Position() {
	this->row = 0;
	this->col = 0;
}

Position::Position(int row, int col) {
	this->row = row;
	this->col = col;
}

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



