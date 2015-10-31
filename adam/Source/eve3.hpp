/*
 * eve3.hpp
 *
 *  Created on: Oct 30, 2015
 *      Author: joxmox
 */

#ifndef EVE3_HPP_
#define EVE3_HPP_

#include <iostream>
#include <fstream>
#include "tty.hpp"
#include "parse.hpp"
#include <unistd.h>
#include <list>
#include <vector>
#include <sstream>
#include <unordered_map>

using namespace std;

struct Buff {
  string txt;
};

#ifdef DBG
#define deb(x) dbg << __FUNCTION__ << ": " << x << endl;
#else
#define deb(x) //
#endif



class Eve {
  int row;
  int col;
  int key;
  int maxRow;
  int maxCol;
  string fileName;
  int firstLine;
  int curLine;
  int maxLines;
  int flines;
}
  bool dispatchLoop;
  bool escapeActive = false;
  bool selectActive = false;
  int selectLine;
  int selectCol;
  Tty tty;
  vector<string> fData;
  int firstLine;
  unordered_map<string, int> markMap;
  bool readFile(string fileName);
  void displayFile();
  bool dispatch();
  void insertChar();
  void processCtrl();
  void processFunc();
  void breakLine();
  void gotoSol();
  void gotoEol();
  void moveDown();
  void moveUp();
  void moveLeft();
  void moveRight();
  void displayStatus();
  int adjustLength();
  void clearScreen();
  void refreshScreen();
  void debugDump();
  void deleteChar();
  void saveExit();
  void processEscape();
  void readCommand();
  void gotoLine(int lnr);
  void cmdShowDefault();
  void cmdShowScreen();
  void cmdMark(string mrk);
  void cmdGoto(string mrk);
  void cmdLine(string lnr);
  void cmdSelect();
  void cmdDelete();
  void cmdInsert();
  int cmpPos(int r1, int c1, int r2, int c2);
  void printStr(string s);
  void movePgDown();
  void movePgUp();
#ifdef DBG
  ofstream dbg{"eve.log"};
#endif
public:
  Eve(string fileName);
};



#endif /* EVE3_HPP_ */
