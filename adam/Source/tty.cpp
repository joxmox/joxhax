#include <ncurses.h>
#include <string>
#include "tty.hpp"
#include "Position.hpp"
#include "Size.hpp"
#include <map>
#include <csignal>
#include <sys/ioctl.h>
#include <cstdlib>
#include <cstring>
#include "Debug.hpp"

using namespace std;


Tty::Tty() {
	  DBG << "Creating tty..." << endl;
	  initscr();

	  scr = nullptr;

	  getmaxyx(stdscr, this->height, this->width);

	  raw();
	  meta(NULL, true);
	  nonl();
	  keypad(stdscr, true);
	  noecho();

	  msgRow = height - 1;
	  cmdRow = height - 2;
	  stsRow = height - 3;
	  maxRow = height - 4;
	  //The stuff above is old. Further stsROw should be in Screen

	  ttySize = {height - 1, width - 1};

	  msgPos = {height - 1};
	  cmdPos = {height - 2};

	  screenSize = {height - 4, width - 1};
	  DBG << screenSize << endl;

	  this->row = 0;
	  this->col = 0;

}

Tty::~Tty() {
  endwin();
}

void Tty::handleResize() {
	DBG << "resize detected!" << endl;
	endwin();
	clear();

	getmaxyx(stdscr, this->height, this->width);

	msgRow = height - 1;
	cmdRow = height - 2;
	stsRow = height - 3;
	maxRow = height - 4;

	//The stuff above is old. Further stsROw should be in Screen

	ttySize = {height - 1, width - 1};

	msgPos = {height - 1};
	cmdPos = {height - 2};

	screenSize = {height - 4, width - 1};
	scr->initScreen();

	scr->displayBuffer();
}

void Tty::setScreen(Screen* s) {
	scr = s;
}

Screen* Tty::getScreen() {
	return scr;
}

int Tty::getHeight() {
  return this->height;
}

int Tty::getWidth() {
  return this->width;
}

void Tty::mvPrint(int r, int c, string s) {
  wmove(stdscr, r, c);
  waddstr(stdscr, s.c_str());
}

void Tty::print(string s,int n) {
  int sts = waddnstr(stdscr, s.c_str(), n);
  if (sts == ERR) DBG << "error printing" << endl;
}

void Tty::reverseOn() {
	wattron(stdscr, A_REVERSE);
}

void Tty::reverseOff() {
	wattroff(stdscr, A_REVERSE);
}

void Tty::reverseCur() {
	wchgat(stdscr, 1, A_REVERSE, 0, nullptr);
}

void Tty::reverseEOL() {
	wchgat(stdscr, -1, A_REVERSE, 0, nullptr);
}

void Tty::reverseN(int n) {
	wchgat(stdscr, n, A_REVERSE, 0, nullptr);
}

void Tty::normalCur() {
	wchgat(stdscr, 1, 0, 0, nullptr);
}

void Tty::normalEOL() {
	wchgat(stdscr, -1, 0, 0, nullptr);
}

void Tty::normalN(int n) {
	wchgat(stdscr, n, 0, 0, nullptr);
}

void Tty::move(int r, int c) {
  int sts = wmove(stdscr, r, c);
  if (sts == ERR) DBG << "error moving" << endl;
}

void Tty::move(Position p) {
	wmove(stdscr, p.getRow(), p.getCol());
}

void Tty::refresh() {
  DBG << "refreshing" << endl;
  wrefresh(stdscr);
}

int Tty::getKey() {
  return getch();
}

int Tty::mvGetKey(int r, int c) {
  int x;
  x = mvgetch(r, c);
  return x;
}

void Tty::putChar(int x) {
  winsch(stdscr, x);
}

string Tty::getLine(int l) {
  char line[2048];
  winnstr(stdscr, line, l);
  return line;
}

void Tty::putMessage(string s) {
  move(msgRow, 0);
  print(s.c_str(), 80);
  wclrtoeol(stdscr);
}

void Tty::putStatus(string s) {
  move(stsRow, 0);
  wattron(stdscr, A_REVERSE);
  print(s.c_str(), 80);
  wattroff(stdscr, A_REVERSE);
}

void Tty::insertLine() {
  int y, x;
  getyx(stdscr, y, x);
  wmove(stdscr, maxRow, 0);
  wdeleteln(stdscr);
  wmove(stdscr, y, x);
  winsertln(stdscr);
}

void Tty::clearToEol() {
  wclrtoeol(stdscr);
}

void Tty::clearAll() {
  wclear(stdscr);
}

void Tty::delChar() {
  wdelch(stdscr);
}

void Tty::delLine() {
  int y, x;
  getyx(stdscr, y, x);
  wdeleteln(stdscr);
  wmove(stdscr, maxRow, 0);
  winsertln(stdscr);
  wmove(stdscr, y, x);
}

string Tty::readCmd() {
	char buff[2048];
	mvwprintw(stdscr, cmdRow, 0, "Command: ");
	wclrtoeol(stdscr);
	noraw();
	echo();
	wgetnstr(stdscr, buff, 2047);
	raw();
	noecho();
	wmove(stdscr, cmdRow, 0);
	wclrtoeol(stdscr);
	putMessage("");
	return buff;
}

Size Tty::getTtySize() {
	return ttySize;
}

Size Tty::getScreenSize() {
	return {height - 4, width - 1};
}

Position Tty::getStatPos() {
	return {height - 3, 0};
}

