/*
 * Screen.cpp
 *
 *  Created on: Oct 20, 2015
 *      Author: joxmox
 */

#include "Screen.hpp"
#include "debug.hpp"
#include "Position.hpp"
#include <string>

using namespace std;

Screen::Screen(Tty* tty, Size& siz, Buffer* buf) : siz(siz), tty(tty), buf(buf) {}
Screen::Screen(Tty* tty, Size& siz) : siz(siz), tty(tty), buf(nullptr) {}

bool Screen::inView(Position bPos) {
	return false;
}

void Screen::setBuffer(Buffer* b) {
	buf = b;
}

void Screen::setSize(Size& s) {
	siz = s;
}

void Screen::displayBuffer() {
	deb("starting");
    int r = siz.getStartRow();
    int f = buf->getTopLine();
    deb("maxLine: " + to_string(buf->getMaxLine()));
    deb("endRow: " + to_string(siz.getEndRow()));
    for (f=buf->getTopLine(); f<buf->getMaxLine() && r<=siz.getEndRow(); r++, f++) {
        tty->move(r, 0);
        tty->print(buf->getLine(f), -1);
        tty->clearToEol();
    }
    deb("rows done");
    if (r <= siz.getEndRow()) {
    	deb("printing EOF marker at line ");
    	tty->move(r++, 0);
    	tty->print("[End of file]", -1);
    }
    while (r <= siz.getEndRow()) {
    	tty->move(r++, 0);
    	tty->clearToEol();
    }
    deb("leaving");
}
