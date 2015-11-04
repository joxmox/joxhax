#ifndef TTY_HPP_
#define TTY_HPP_


#include <ncurses.h>
#include <string>
#include <fstream>
#include "Size.hpp"
#include "Screen.hpp"

class Screen;

class Tty {
  int height;
  int width;
  int row;
  int col;
  int stsRow;
  int msgRow;
  int cmdRow;
  int maxRow;
  Screen* scr;
public:
  Tty();
  ~Tty();
  int getHeight();
  int getWidth();
  void putChar(int x);
  void delChar();
  void delLine();
  std::string getLine(int l);
  void print(std::string s, int n);
  void mvPrint(int r, int c, std::string s);
  void move(int r, int c);
  void refresh();
  int getKey();
  int mvGetKey(int r, int c);
  void putMessage(std::string s);
  void putStatus(std::string s);
  void clearToEol();
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
  Size getSize();
  void handleResize();
  void setScreen(Screen*);
  Screen* getScreen();
};

#endif
