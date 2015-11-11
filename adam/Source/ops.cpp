/*
 * ops.cpp
 *
 *  Created on: Nov 8, 2015
 *      Author: joxmox
 */

#include "ops.hpp"

bool operator <(Position p, Size s) {
	int pr = p.getRow();
	int pc = p.getCol();
	Position ss = s.getStart();
	Position se = s.getEnd();
	if (pr >= ss.getRow() && pr <=se.getRow() && pc >= ss.getCol() && pc <= se.getCol()) {
		return true;
	} else {
		return false;
	}
}

bool operator >(Position p, Size s) {
	return !(p < s);
}

/*
bool const operator ==(Position& p1, Position& p2) {
	if (p1.getRow() == p2.getRow() && p1.getCol() == p2.getCol()) {
		return true;
	} else {
		return false;
	}
}

bool const operator !=(Position& p1, Position& p2) {
	return !(p1 == p2);
}

*/

bool const operator <(Position& p1, Position& p2) {
	if (p1.getRow() < p2.getRow()) return true;
	if (p1.getRow() > p2.getRow()) return false;
	if (p1.getCol() < p2.getCol()) return true;
	return false;
}

bool const operator <=(Position& p1, Position& p2) {
	return (p1 < p2 || p1 == p2);
}

bool const operator >(Position& p1, Position& p2) {
	return !(p1 <= p2);
}

bool const operator >=(Position& p1, Position& p2) {
	return !(p1 < p2);
}
