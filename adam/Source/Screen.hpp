/*
 * Screen.hpp
 *
 *  Created on: Oct 20, 2015
 *      Author: joxmox
 */

#pragma once

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
	Position pos;
	Position statusPos;
public:
	Screen(Tty* tty, scrMode mode = full);
	Screen(Tty* tty, Buffer* buf, scrMode mode = full);
	bool inView(Position& bPos);
	void setBuffer(Buffer*);
	void displayBuffer();
	Size& getSize();
	void setSize(Size& s);
	void initScreen();
	void printStatus();
	void insertChar(int key);
	void position();
	void moveRight();
	void moveLeft();
	void moveUp();
	void moveDown();
};

