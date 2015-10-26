#ifndef TTY_HPP_
#define TTY_HPP_


#include <ncurses.h>
#include <string>
#include <fstream>

class Tty {
  int height;
  int width;
  int row;
  int col;
  int stsRow;
  int msgRow;
  int cmdRow;
  int maxRow;
  std::ofstream deb {"tty.log"};
public:
  Tty();
  ~Tty();
  void init();
  int getHeight();
  int getWidth();
  void putChar(int x);
  void delChar();
  void delLine();
  std::string getLine(int l);
  void print(std::string s);
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
  std::string readCmd();
};

#endif
