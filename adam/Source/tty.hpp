#pragma once

#include <ncurses.h>
#include <string>
#include <map>
#include <fstream>
#include "Size.hpp"
#include "Screen.hpp"
#include "Position.hpp"

class Screen;

class Tty {
  static int winCnt;
  int height;
  int width;
  int row;
  int col;
  int stsRow;
  int msgRow;
  int cmdRow;
  int maxRow;
  Size ttySize;
  Size screenSize;
  Position msgPos;
  Position cmdPos;
  Screen* scr;
  std::map<int, WINDOW*> winMap;
public:
  Tty();
  ~Tty();
  int getHeight();
  int getWidth();
  void putChar(int x);
  void delChar();
  void delLine();
  std::string getLine(int l);
  void print(std::string s, int n=-1);
  void print(int, std::string, int = -1);
  void mvPrint(int r, int c, std::string s);
  void move(int r, int c);
  void move(Position p);
  void move(int, Position);
  void refresh();
  int getKey();
  int mvGetKey(int r, int c);
  void putMessage(std::string s);
  void putStatus(std::string s);
  void clearToEol();
  void clearToEol(int);
  void insertLine();
  void clearAll();
  void printRev();
  void reverseOn();
  void reverseOff();
  void reverseCur();
  void reverseEOL();
  void reverseN(int n);
  void normalCur();
  void normalEOL();
  void normalN(int n);
  std::string readCmd();
  Size getTtySize();
  Size getScreenSize();
  void handleResize();
  void setScreen(Screen*);
  Screen* getScreen();
  Position getStatPos();
  int createWin(Size);
};
