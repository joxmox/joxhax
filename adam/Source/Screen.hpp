/*
 * Screen.hpp
 *
 *  Created on: Oct 20, 2015
 *      Author: joxmox
 */

#ifndef SCREEN_HPP_
#define SCREEN_HPP_

#include "Position.hpp"
#include "tty.hpp"

class Screen {
	int row;
	int col;
	int top;
	int bot;
	Tty *tty;
public:
	Screen(Tty* tty, int top, int bot);
	int getRow();
	int getCol();
	void move();
	bool inView(Position bPos);
};


#endif /* SCREEN_HPP_ */
