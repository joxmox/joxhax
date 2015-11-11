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

int Position::setCol(int c) {
	col = c;
	return c;
}

int Position::setRow(int r) {
	row = r;
	return r;
}

void Position::moveUp() {
	row--;
}

void Position::moveDown() {
	row++;
}

void Position::moveLeft() {
	col--;
}

void Position::moveRight() {
	col++;
}

bool Position::onScreen() const {
	return true;
}

void Position::setPos(int r, int c) {
	row = r;
	col = c;
}

bool Position::operator ==(Position p) {
	return (this->row == p.row && this->col == p.row);
}

bool Position::operator !=(Position p) {
	return !(*this == p);
}

Position Position::operator ++() {
	this->col++;
	return *this;
}

Position Position::operator ++(int) {
	Position tmp = *this;
	this->col++;
	return tmp;
}

Position Position::operator --() {
	this->col--;
	return *this;
}

Position Position::operator --(int) {
	Position tmp = *this;
	this->col--;
	return tmp;
}

Position Position::operator +(Position p) {
	return {this->row + p.row, this->col + p.col};
}

Position Position::operator -(Position p) {
	return {this->row - p.row, this->col + p.col};
}

Position Position::operator +=(Position p) {
	*this = *this + p;
	return *this;
}

Position Position::operator -=(Position p) {
	*this = *this - p;
	return *this;
}

string Position::toString() const {
	return ("(" + to_string(row) + "," + to_string(col) + ")");
}

ostream& operator <<(ostream& os, const Position& p) {
	return os << p.toString();
}
