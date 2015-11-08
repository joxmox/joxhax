/*
 * BufferPosition.cpp
 *
 *  Created on: Oct 20, 2015
 *      Author: joxmox
 */

#include "Position.hpp"
#include <string>
#include <iostream>

using namespace std;

Position::Position(int row, int col): row(row), col(col) {};

int Position::getCol() const {
	return this->col;
}

int Position::getRow() const {
	return this->row;
}

bool Position::onScreen() const {
	return true;
}

void Position::setPos(int r, int c) {
	row = r;
	col = c;
}

void Position::operator ++() {
	this->col++;
}

void Position::operator --() {
	this->col--;
}

string Position::toString() const {
	return ("(" + to_string(row) + "," + to_string(col) + ")");
}

ostream& operator <<(ostream& os, const Position& p) {
	return os << p.toString();
}
