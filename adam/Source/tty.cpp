#include <ncurses.h>
#include <string>
#include "tty.hpp"
#include <map>

using namespace std;

Tty::Tty() {
  int sts;
  WINDOW *iscr = NULL;

  iscr = initscr();
  if (iscr == NULL) {
    deb << "initscr: failed" << endl;
  } else {
    deb << "initscr: success" << endl;
  }

  sts = start_color();
  deb << "start_color: " << sts << endl;

  sts = getmaxyx(stdscr, this->height, this->width);

  sts = raw();
  sts = meta(NULL, true);
  sts = nonl();
  sts = keypad(stdscr, true);
  sts = noecho();

  msgRow = height - 1;
  cmdRow = height - 2;
  stsRow = height - 3;
  maxRow = height - 4;

  this->row = 0;
  this->col = 0;
}

Tty::~Tty() {
  endwin();
}

int Tty::getHeight() {
  return this->height;
}

int Tty::getWidth() {
  return this->width;
}

void Tty::mvPrint(int r, int c, string s) {
  int sts;
  sts = mvprintw(r, c, s.c_str());
  deb << "mvwprint sts: " << sts << endl;
}

void Tty::print(string s) {
  printw(s.c_str());
}

void Tty::move(int r, int c) {
  int sts;
  wmove(stdscr, r, c);
}

void Tty::refresh() {
  deb << "refreshed" << endl;
  wrefresh(stdscr);
}

int Tty::getKey() {
  return getch();
}

int Tty::mvGetKey(int r, int c) {
  int x;
  x = mvgetch(r, c);
  deb << "mwgetch c: " << x << endl;
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
  print(s.c_str());
  wclrtoeol(stdscr);
}

void Tty::putStatus(string s) {
  move(stsRow, 0);
  wattron(stdscr, A_REVERSE);
  print(s.c_str());
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
