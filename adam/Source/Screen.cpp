/*
 * Screen.cpp
 *
 *  Created on: Oct 20, 2015
 *      Author: joxmox
 */

#include "Screen.hpp"
#include "BufferPosition.hpp"

Screen::Screen(Tty tty, int top, int bot) {
  this->tty = tty;
  this->top = top;
  this->bot = bot;
  this->row = 0;
  this->col = 0;
}

int Screen::getRow() {
	return this->row;
}

int Screen::getCol() {
	return this->col;
}

void Screen::move() {

}

bool Screen::inView(BufferPosition bPos) {
	return false;
}


