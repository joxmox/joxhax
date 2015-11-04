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
#include "Buffer.hpp"
#include "Size.hpp"

class Tty;

class Screen {
	Size siz;
	Tty* tty;
	Buffer* buf;
public:
	Screen(Tty* tty, Size& s);
	Screen(Tty* tty, Size& s, Buffer* buf);
	bool inView(Position bPos);
	void setBuffer(Buffer*);
	void displayBuffer();
	void setSize(Size& s);
};


#endif /* SCREEN_HPP_ */
