/*
 * Screen.cpp
 *
 *  Created on: Oct 20, 2015
 *      Author: joxmox
 */

#include "Screen.hpp"
#include "Position.hpp"
#include "ops.hpp"
#include <string>
#include "Debug.hpp"

using namespace std;

void Screen::initScreen() {
	if (mode == full) {
	  siz = tty->getScreenSize();
	  statusPos = tty->getStatPos();
	  DBG << "Screen initialized: " << siz << endl;
	}
}

Screen::Screen(Tty* tty,Buffer* buf, scrMode mode) : tty(tty), buf(buf), mode(mode) {
	initScreen();
}

Screen::Screen(Tty* tty, scrMode mode) : tty(tty), buf(nullptr), mode(mode) {
	initScreen();
}

bool Screen::inView(Position& bPos) {
	return false;
}

void Screen::setBuffer(Buffer* b) {
	buf = b;
}

Position& Screen::getPos() {
	return pos;
}

void Screen::setSize(Size& s) {
	siz = s;
}

void Screen::displayBuffer() {
	DBG << "starting" << endl;
    int f = buf->getRow();
    for (Position p=siz.getStart(); p < siz; p.moveDown()) {
        tty->move(p);
        tty->print(buf->getLine(f++));
        tty->clearToEol();
    }
    printStatus();
    DBG << "leaving" << endl;;
}

void Screen::printStatus() {
	int spaces = siz.getWidth() - 9 - buf->getFileName().length() - 27;
	tty->move(statusPos);
	wattron(stdscr, A_REVERSE);
	tty->print(" Buffer: " + buf->getFileName() + string(spaces, ' ') + "| Write | Insert | Forward ");
	wattroff(stdscr, A_REVERSE);
}

void Screen::insertChar(int key) {
	buf->adjustRow(pos);
	buf->insertChar(key);
	tty->putChar(key);
	if (pos < siz) pos++;
}

void Screen::position() {
	tty->move(pos);
}

void Screen::moveLeft() {
	buf->moveLeft();
	if (pos.getCol() > siz.getStart().getCol()) {
		pos--;
	}
	int bs = buf->getSelect();
	switch (bs) {
	    case -1: tty->reverseCur(); break;
	    case  1: tty->normalCur(); break;
	}
}

void Screen::moveRight() {
	buf->moveRight();
	if (pos.getCol() < siz.getEnd().getCol()) {
		pos++;
	}
}

void Screen::moveUp() {
	if (buf->getRow() > 0) {
		buf->moveUp();
		if (pos.getRow() > 0) {
			pos.moveUp();
		} else {
			tty->move(siz.getStart());
			tty->insertLine();
			tty->move(siz.getStart());
			tty->print(buf->getCurLine());
		}
	}
}

void Screen::moveDown() {
	buf->moveDown();
	if (pos.getRow() < siz.getEnd().getRow()) {
		pos.moveDown();
	} else {
		tty->move(0, 0);
		tty->delLine();
		tty->move(siz.getLowLeft());
		tty->print(buf->getCurLine());
	}
}





