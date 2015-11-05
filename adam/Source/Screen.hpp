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
public:
	enum scrMode {full, upper, lower};
private:
	Tty* tty;
	Buffer* buf;
	scrMode mode;
	Size siz;
public:
	Screen(Tty* tty, scrMode mode = full);
	Screen(Tty* tty, Buffer* buf, scrMode mode = full);
	bool inView(Position& bPos);
	void setBuffer(Buffer*);
	void displayBuffer();
	Size& getSize();
	void setSize(Size& s);
	void initScreen();
};


#endif /* SCREEN_HPP_ */
