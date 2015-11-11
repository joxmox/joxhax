/*
 * ops.hpp
 *
 *  Created on: Nov 8, 2015
 *      Author: joxmox
 */

#pragma once

#include "Size.hpp"
#include "Position.hpp"


bool operator <(Position p, Size s);
bool operator >(Position p, Size s);


/*
 *
bool const operator ==(Position& p1, Position& p2);
bool const operator !=(Position& p1, Position& p2);
*/

bool const operator <(Position& p1, Position& p2);
bool const operator <=(Position& p1, Position& p2);
bool const operator >(Position& p1, Position& p2);
bool const operator >=(Position& p1, Position& p2);
