/*
 * Size.hpp
 *
 *  Created on: Nov 2, 2015
 *      Author: joxmox
 */

#ifndef SIZE_HPP_
#define SIZE_HPP_

#include "Position.hpp"

class Size {
	Position start;
	Position end;
public:
	Size(const Position&, const Position&);
	Size(int, int, int, int);
	Size(int, int);
	Size(int, int, const Position&);
	Size(const Position&, int, int);
	int const getHeight();
	int const getWidth();
	int const getStartRow();
	int const getEndRow();
	int const getStartCol();
	int const getEndCol();
	Size const splitU();
	Size const splitL();
};

#endif /* SIZE_HPP_ */
