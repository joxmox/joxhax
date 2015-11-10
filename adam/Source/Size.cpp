/*
 * Size.cpp
 *
 *  Created on: Nov 2, 2015
 *      Author: joxmox
 */

#include "Size.hpp"
#include "Position.hpp"
#include <string>
#include <ostream>

using namespace std;

Size::Size(): start({0,0}), end({0,0}) {}

Size::Size(const Position& a, const Position& b): start(a), end(b) {}

Size::Size(int r1, int c1, int r2, int c2) {
	start = Position {r1, c1};
	end = Position {r2, c2};
}

Size::Size(int r2, int c2) {
	start = Position(0, 0);
	end = Position(r2, c2);
}

Size::Size(const Position& s, int r2, int c2) {
	start = s;
	end = Position {r2, c2};
}

Size::Size(int r1, int c1, const Position& e) {
	start = Position {r1, c1};
	end = e;
}

int const Size::getWidth() {
	return end.getCol() - start.getCol() + 1;
}

int const Size::getHeight()  {
	return end.getRow() - start.getRow() + 1;
}

Size const Size::splitU() {
	int r1 = start.getRow();
	int r2 = end.getRow();
	int c2 = end.getCol();
	return Size(start, (r2-r1-1)/2, c2);
}

Size const Size::splitL() {
	int r1 = start.getRow();
	int c1 = start.getCol();
	int r2 = end.getRow();
	return Size((r2-r1+1)/2, c1, end);
}

Position Size::getStart() {
	return start;
}

Position Size::getEnd() {
	return end;
}

Position Size::getLowLeft() {
	return {end.getRow(), start.getCol()};
}

Position Size::getUpRight() {
	return {start.getRow(), end.getCol()};
}

int const Size::getStartRow() {
	return start.getRow();
}

int const Size::getStartCol() {
	return start.getCol();
}

int const Size::getEndRow() {
	return end.getRow();
}

int const Size::getEndCol() {
	return end.getCol();
}

//Size& Size::operator -(Position& p) {
//	if (p.getRow() == this->getStartRow()) {
//		this->start++;
//	}
//}

void Size::setSize(Size s) {
	start = s.getStart();
	end = s.getEnd();
}


string Size::toString() const {
	return start.toString() + ":" + end.toString();
}

ostream& operator <<(ostream& os, const Size& s) {
	return os << s.toString();
}


