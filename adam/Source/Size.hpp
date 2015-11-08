/*
 * Size.hpp
 *
 *  Created on: Nov 2, 2015
 *      Author: joxmox
 */

#pragma once

#include "Position.hpp"

class Size {
	Position start;
	Position end;
public:
	Size();
	Size(const Position&, const Position&);
	Size(int, int, int, int);
	Size(int, int);
	Size(int, int, const Position&);
	Size(const Position&, int, int);
	Position getStart();
	Position getEnd();
	int const getHeight();
	int const getWidth();
	int const getStartRow();
	int const getEndRow();
	int const getStartCol();
	int const getEndCol();
	void setSize(Size s);
	Size const splitU();
	Size const splitL();
	Size& operator -(Position& p);

};

