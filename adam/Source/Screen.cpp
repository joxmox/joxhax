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
#include "parse.hpp"

using namespace std;

int Screen::idCnt = 0;


void Screen::initScreen() {
	id = ++idCnt;
	if (mode == full) {
	  Size ttySiz = tty->getScreenSize();
	  siz = {ttySiz.getStart(), {ttySiz.getEndRow() - 3, ttySiz.getEndCol()}};
	  win = tty->createWin(siz);
	  Size stsSiz = {{ttySiz.getEndRow() - 2, ttySiz.getEndCol()}, {ttySiz.getEndRow() - 2, ttySiz.getEndCol()}};
	  stsWin = tty->createWin(stsSiz);
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
	stsBuf = b->getName();
}

Position& Screen::getPos() {
	return pos;
}

void Screen::setSize(Size& s) {
	siz = s;
}

string Screen::toString() const{
	ostringstream os;
	os << "Scr[" << id << "] " << "size:" << siz << ", ";
	os << "pos:" << pos << ", ";
	if (buf != nullptr) {
	  os << "buf:" << buf->getName();
	} else {
		os << "buf:(none)";
	}
	os << ", win:" << win;
	return os.str();
}

void Screen::displayBuffer() {
	DBG << "starting " << win << endl;
    int f = buf->getRow();
    for (Position p=siz.getStart(); p < siz; p.moveDown()) {
        tty->move(win, p);
        tty->print(win, buf->getLine(f++), siz.getEndCol());
        tty->clearToEol(win);
    }
    printStatus();
    tty->refresh();
    DBG << "leaving" << endl;
}

void Screen::printStatus() {
	int spaces = siz.getWidth() - 9 - buf->getFileName().length() - 27;
	tty->move(statusPos);
	wattron(stdscr, A_REVERSE);
	tty->print(" Buffer: " + buf->getFileName() + string(spaces, ' ') + "| Write | Insert | Forward ");
	wattroff(stdscr, A_REVERSE);
}

void Screen::insertChar(int key) {
	adjust();
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
			tty->print(buf->getCurLine(), siz.getEndCol());
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
		tty->print(buf->getCurLine(),siz.getEndCol());
	}
}

void Screen::pageUp() {
}

void Screen::pageDown() {
}

void Screen::breakLine() {
	adjust();
	buf->recalcMarks(1);
	buf->breakLine();
	pos.setCol(0);
	tty->move(pos);
	tty->print(buf->getCurLine(-1));
	tty->clearToEol();
	pos.moveDown();
	tty->move(pos);
	tty->insertLine();
	tty->print(buf->getCurLine());
}


void Screen::deleteChar() {
	DBG << "enter" << endl;
	adjust();
	if (pos.getCol() > 0) {
		tty->move(--pos);
		tty->delChar();
		buf->delChar();
	} else {
		int br = buf->getRow();
		DBG << "Buffer row: " << br << endl;
		if (br > 0) {
			int nc = buf->joinLines();
			DBG << "new column: " << nc << endl;
			tty->delLine();
			pos.moveUp();
			tty->move(pos);
			DBG << "new pos (after move up): " << pos << endl;
			tty->print(buf->getCurLine());
			tty->move(siz.getLowLeft());
			tty->print(buf->getLine(siz.getEndRow() + br - pos.getRow() - 1));
			pos.setCol(nc);
			buf->recalcMarks(-1);
		}
	}
}

void Screen::adjust() {
	int obs = buf->getDataSize();
	buf->adjustRow(pos);
	int nbs = buf->getDataSize();
	DBG << "obs:" << obs << ", nbs:" << nbs << endl;
	if (nbs > obs) {
		for (int i=nbs-obs; i>=0 && pos.getRow() - i + 1 < siz; i--) {
			DBG << "moving to row " << pos.getRow() - i + 1 << endl;
			tty->move(pos.getRow() - i + 1, 0);
			DBG << "printing buffer line #" << nbs - i << ": " << buf->getLine(nbs - i) << endl;
			tty->print(buf->getLine(nbs - i));
			tty->clearToEol();
			tty->move(pos);
		}
	}
}

void Screen::gotoPos(Position p) {
	DBG << "enter" << endl;
	int markRow = p.getRow();
	markRow = min(markRow, buf->getEndLine());
	markRow = max(markRow, 0);
	int markCol = p.getCol();
	markCol = min(markCol, static_cast<int>(buf->getLine(markRow).length()));
	int bufRow = buf->getRow();
	int topRow = bufRow - pos.getRow();
	int botRow = topRow + siz.getEndRow();
	int scrRow = pos.getRow();
	DBG << "markRow:" << markRow << ", markCol:" << markCol << ", topRow:" << topRow << ", botRow:" << botRow << endl;
	if (markRow < topRow || markRow > botRow) {
		DBG << "outside current view" << endl;
		if (markRow < topRow) {
			scrRow = 0;
		} else {
			scrRow = siz.getEndRow();
		}
		buf->setPos({markRow, markCol});
		displayBuffer();
	} else {
		DBG << "inside current view" << endl;
		scrRow += markRow - buf->getRow();
		buf->setPos({markRow, markCol});
	}
	pos = {scrRow, markCol};
}


void Screen::cmdMark(string mark) {
	buf->setMark(mark);
	tty->putMessage("Mark " + mark + " set.");
	DBG << "mark " << mark << " set at " << buf->getPos() << endl;
}

void Screen::cmdLine(string line) {
	int ln = stoi(line);
	gotoPos(Position{ln - 1, 0});
}

void Screen::cmdGoto(string mark) {
	Position p = buf->getMark(mark);
	if (p == NOPOS) {
		tty->putMessage("Marker " + mark + " not set.");
	} else {
		gotoPos(p);
		tty->putMessage("Going to mark: " + mark + "");
	}
}

void Screen::readCommand() {
	static vector<pair<int, string>> ptab {
		{1, "mark *"},
		{2, "line *"},
		{3, "goto *"},
		{4, "select"},
		{5, "delete"},
		{6, "insert"},
    };
	static Parse parse {ptab};
	string cmd = tty->readCmd();
	DBG << "parsing command: " << cmd << endl;
	int res = parse.decode(cmd);
	switch(res) {
	case -2 : tty->putMessage("No command given."); break;
	case -1 : tty->putMessage("Ambiguous command."); break;
	case  0 : tty->putMessage("Unrecognized command."); break;
	case  1: cmdMark(parse.getParam()); break;
	case  2: cmdLine(parse.getParam()); break;
	case  3: cmdGoto(parse.getParam()); break;
	default : tty->putMessage("Command #" + to_string(res) + " OK.");

	/*
	 *
	case  1 : cmdShowDefault(); break;
	case  2 : cmdShowScreen(); break;
	case  3 : cmdMark(parse.getParam()); break;
	case  4 : cmdLine(parse.getParam()); break;
	case  5 : cmdGoto(parse.getParam()); break;
	case  6 : cmdGoto(parse.getParam()); break;
	case  7 : cmdGoto(parse.getParam()); break;
	case  8 : cmdGoto(parse.getParam()); break;
	*/
	}
}


/*
void Eve::deleteChar() {
  adjustLength();
  if (col > 0) {
    tty.move(row, --col);
    tty.delChar();
    fData[firstLine].erase(col, 1);
    tty.move(row, 0);
  } else {
    if (firstLine > 0) {
      col = fData[firstLine-1].length();
      string str = fData[firstLine];
      tty.delLine();
      tty.move(--row, col);
      printStr(str);
      fData[firstLine-1] += fData[firstLine];
      fData.erase(fData.begin() + firstLine--);
      --flines;
    }
  }
}

*/

ostream& operator <<(ostream& os, const Screen scr) {
	os << scr.toString();
	return os;
}
