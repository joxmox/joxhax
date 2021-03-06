#include <iostream>
#include <fstream>
#include "tty.hpp"
#include "parse.hpp"
#include <unistd.h>
#include <list>
#include <vector>
#include <sstream>
#include <unordered_map>

//#define DBG 0

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
  int flines;
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

bool Eve::readFile(string fileName) {
	this->fileName = fileName;
  flines = 0;
  string line;
  ifstream inf{fileName};
  if (!inf) return false;
  while (getline(inf, line)) {
    fData.push_back(line);
    flines++;
  }
  firstLine = 0;
  stringstream ss;
  ss << flines << " lines read from " << fileName;
  tty.putMessage(ss.str());
  return true;
}

void Eve::printStr(string s) {
	string tmp = s;
	int right = col + tmp.length();
	deb("Right=" << right)
	if (right > maxCol) {
		deb("pos=" << maxCol-col);
		deb("tmp before:" << tmp);
		tmp.erase(maxCol-col);
		deb("tmp after:"<< tmp);
		tmp += string(1, 274);
	}
	tty.print(tmp, -1);
}

void Eve::displayFile() {
    int r = 0;
    int c = 0;
    int f = firstLine - row;
    deb("fPtr=" << f << ", row=" << row << ", f=" << f);
    if (f < 0) f = 0;
    while (r <= maxRow && f < fData.size()) {
        deb("row=" << r << ", f=" << f << ", data=" << fData[f]);
        tty.move(r++, c);
        tty.print(fData[f++], -1);
        tty.clearToEol();
    }
    if (r <= maxRow) {
    	deb("printing EOF marker at line " << r)
    	tty.mvPrint(r++, c, "[End of file]");
    }
    while (r <= maxRow) {
    	tty.move(r++, 0);
    	tty.clearToEol();
    }
    tty.move(row, col);
    tty.refresh();
}

void Eve::displayStatus() {
  int spaces = tty.getWidth() - 9 - fileName.length() - 27;
  stringstream ss;
  ss << " Buffer: " << fileName << string(spaces, ' ') << "| Write | Insert | Forward ";
  tty.putStatus(ss.str());
}

void Eve::insertChar() {
  adjustLength();
  deb("inserting " << key);
  fData[firstLine].insert(1, string(1, key));
  tty.putChar(key);
  deb("line before = |" << fData[firstLine] << "|");
  tty.move(row, 0);
//  fData[fPtr] = tty.getLine(fData[fPtr].length()+1);
  deb("line after = |" << fData[firstLine] << "|");
  if (col < maxCol) col++;
}

int Eve::adjustLength() {
  int curLen = fData[firstLine].length();
  if (col > curLen) {
    fData[firstLine] += string(col - curLen, ' ');
  }
  return fData[firstLine].length();
}

void Eve::breakLine() {
  int curLen = adjustLength();
  deb("current line =|" << fData[firstLine] << "|");
  string sright = fData[firstLine].substr(col, curLen - col);
  deb("right part =|" << sright << "|");
  tty.clearToEol();
  deb("cleared from cursor to eol");
  tty.move(row, 0);
  deb("moved to sol");
  string sleft = fData[firstLine].substr(0, col);
  deb("left part =|" << sleft << "|");
  fData[firstLine] = sleft;
  if (row < maxRow) {
	  row++;
	  deb("not at last line");
	  tty.move(row, 0);
	  tty.insertLine();
	  deb("inserted new blank line");
	  col = 0;
	  printStr(sright);
  } else {
	  deb("on last line!");
  }

  fData.insert(fData.begin() + ++firstLine, sright);
  this->col = 0;
  flines++;
}

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


void Eve::processCtrl() {
}

void Eve::processFunc() {
  switch(key) {
    case 258: Eve::moveDown(); break;
  }
}

void Eve::movePgDown() {
  firstLine += maxRow;
  if (firstLine >= flines) firstLine = flines - 1;
  displayFile();
}

void Eve::movePgUp() {
	firstLine -= maxRow;
	if (firstLine < 0) firstLine = 0;
	displayFile();
}

void Eve::moveDown() {
	deb("flines=" << flines << ", row=" << row << ", size=" << fData.size() << ", fPtr=" << firstLine);
	if (firstLine < fData.size() - 1) {
		firstLine++;
		if (selectActive) {
			tty.move(row, col);
			if (cmpPos(firstLine, col, selectLine, selectCol) > 0) tty.reverseEOL(); else tty.normalEOL();
		}
		if (row < maxRow) {
			row++;
		} else {
			deb("window should scroll here...");
			deb("fPtr: " << firstLine)
			deb("fData: " << fData[firstLine])
			tty.move(0, 0);
			tty.delLine();
			tty.move(maxRow, 0);
			printStr(fData[firstLine]);
		}
		if (selectActive) {
			tty.move(row, 0);
			if (cmpPos(firstLine, col, selectLine, selectCol) > 0) tty.reverseN(col); else tty.normalN(col);
		}
	} else {
		deb("already on last line");
	}
}

void Eve::moveUp() {
	deb("flines=" << flines << ", row=" << row << ", size=" << fData.size() << ", fPtr=" << firstLine);
	if (firstLine > 0) {
		--firstLine;
		if (selectActive) {
			tty.move(row, 0);
			if (cmpPos(firstLine, col, selectLine, selectCol) < 0) tty.reverseN(col); else tty.normalN(col);
		}
		if (row > 0) {
			--row;
		} else {
			deb("window should scroll here...");
			tty.move(0, 0);
			tty.insertLine();
			tty.move(0, 0);
			printStr(fData[firstLine]);
		}
		if (selectActive) {
			tty.move(row, col);
			if (cmpPos(firstLine, col, selectLine, selectCol) < 0) tty.reverseEOL(); else tty.normalEOL();
		}
	} else {
		deb("already at first line of file");
	}
}

int Eve::cmpPos(int r1, int c1, int r2, int c2) {
	if (r1 > r2) return 1;
	if (r1 < r2) return -1;
	if (c1 > c2) return 1;
	if (c1 < c2) return -1;
	return 0;
}

void Eve::moveLeft() {
  if (col > 0) {
    --col;
	if (selectActive) {
		if (cmpPos(firstLine, col, selectLine, selectCol) < 0) {
		    tty.reverseCur();
		} else {
			tty.normalCur();
		}
	}
  } else {
    deb("already at column 0");
  }
}

void Eve::moveRight() {
	if (col < maxCol ) {
		col++;
		if (selectActive) {
			if (cmpPos(firstLine, col, selectLine, selectCol) > 0) {
			    tty.reverseCur();
			} else {
				tty.normalCur();
			}
		}
	} else {
		deb("already at far left column")
	}
}

void Eve::gotoSol() {
  if (col != 0) {
    col = 0;
  } else {
    deb("already at start of line");
    tty.putMessage("You are already at the start of a line.");
  }
}

void Eve::gotoEol() {
  int curLen = fData[firstLine].length();
  if (col != curLen) {
    col = curLen;
  } else {
    deb("already at end of line");
    tty.putMessage("You are already at the end of a line.");
  }
}

void Eve::clearScreen() {
  tty.clearAll();
}

void Eve::refreshScreen() {
  clearScreen();
  displayFile();
  displayStatus();
}

void Eve::debugDump() {
  int i = 0;
  deb("----------");
  deb("flines=" << flines);
  for (auto f : fData) {
    deb(i++ << " [" << f.length() << "]: |" << f << "|");
  }
  deb("fPtr=" << firstLine);
  deb("----------");
}

void Eve::saveExit() {
	dispatchLoop = false;
}

void Eve::cmdShowScreen() {
	tty.putMessage("show screen");
}

void Eve::cmdShowDefault() {
	tty.putMessage("show default");
}

void Eve::cmdMark(string mrk) {
	markMap[mrk] = firstLine;
	tty.putMessage("Mark " + mrk + " set.");
}

void Eve::cmdGoto(string mrk) {
	unordered_map<string, int>::const_iterator find = markMap.find(mrk);
	if (markMap.find(mrk) != markMap.end()) {
		tty.putMessage("Going to mark " + mrk + ".");
		int lnr = markMap[mrk];
		gotoLine(lnr);
	} else {
		tty.putMessage("Mark " + mrk + " not set.");
	}
}

void Eve::gotoLine(int inlnr) {
	int lnr = inlnr;
	if (lnr > flines - 1) lnr = flines - 1;
	deb("row=" << row << ", fPtr=" << firstLine << ", flines=" << flines);
	col = 0;	//always goto beginning of line
	int topLine = firstLine - row;	//first line in view
	int botLine = topLine + maxRow;	//last line in view
	if (botLine > flines) botLine = flines;
	if (lnr < topLine || lnr > botLine) {
		deb("outside current window");
		if (lnr < firstLine) {
			row = 0;
		} else {
			row = maxRow;
		}
	} else {
		deb("inside current window");
		row += lnr - firstLine;
	}
	firstLine = lnr;
	displayFile();
}

void Eve::cmdLine(string lnr) {
	int lint = stoi(lnr) - 1;
	if (lint < 0) {
		tty.putMessage("Cannot move to line: " + lnr);
		return;
	}
	if (lint > flines - 1) {
		tty.putMessage("Buffer has only " + to_string(flines) + " lines.  (Now going to End of Buffer).");
		lint = flines - 1;
	}
	gotoLine(lint);
}

void Eve::cmdSelect() {
	if (selectActive) {
		if (cmpPos(firstLine, col, selectLine, selectCol) > 0) {
			int r = (firstLine - selectLine);
			if (r > row) r = row;
			tty.move(row -r, selectCol);
			tty.normalEOL();
			for (auto i=row-r+1; i<row; i++) {
				move(i, 0);
				tty.normalEOL();
			}
			tty.move(row, 0);
			tty.normalEOL();
		}tty.putMessage("Selection canceled.");
		selectActive = false;

	} else {
		selectActive = true;
		selectLine = firstLine;
		selectCol = col;
		tty.putMessage("Move the test cursor to select text.");
	}
}

void Eve::readCommand() {
	static vector<pair<int, string>> ptab {
		{1, "show default"},
		{2, "show screen"},
		{3, "mark *"},
		{4, "line *"},
		{5, "goto *"},
		{6, "select"},
		{7, "insert"},
		{8, "delete"},
    };
	Parse parse {ptab};
	string cmd = tty.readCmd();
	deb("parsing command: " << cmd);
	int res = parse.decode(cmd);
	switch(res) {
	case -2 : tty.putMessage("No command given."); break;
	case -1 : tty.putMessage("Ambigous command."); break;
	case  0 : tty.putMessage("Unrecognized command."); break;
	case  1 : cmdShowDefault(); break;
	case  2 : cmdShowScreen(); break;
	case  3 : cmdMark(parse.getParam()); break;
	case  4 : cmdLine(parse.getParam()); break;
	case  5 : cmdGoto(parse.getParam()); break;
	case  6 : cmdGoto(parse.getParam()); break;
	case  7 : cmdGoto(parse.getParam()); break;
	case  8 : cmdGoto(parse.getParam()); break;
	}
}

void Eve::processEscape() {
	static vector<string> validEsc {
		"Oj",
		"Om",
		"Oo"
	};
	static string escStr {""};
	escStr += static_cast<char>(key);
	int len = escStr.length();
	int match = 0;
	deb("key=" << key);
	deb("escStr=" << escStr << ", len=" << len);
	for (auto v : validEsc) {
		deb("string=" << v);
		string sub = v.substr(0, len);
		deb("sub=" << sub);
		deb("checking " << v.substr(0, len));
		if (v.substr(0, len) == escStr) {
			match++;
		}
	}
	deb("match = " << match);
	switch (match) {
	case 0 : {
		tty.putMessage("Invalid escape sequence.");
		escStr = "";
		escapeActive = false;
		break;
	}
	case 1 : {
		if (escStr == "Om") readCommand();
		escStr = "";
		escapeActive = false;
	}
	}
}


bool Eve::dispatch() {
	dispatchLoop = true;
	deb("key=" << key << ", Esc=" << escapeActive);
	if (escapeActive) {
		processEscape();
	} else {
		if (key == -1) saveExit();
		if (key == 0) return true;
		if (key == 4) debugDump();
		if (key == 5) gotoEol();
		if (key == 8) gotoSol();
		if (key == 13) breakLine();
		if (key == 23) refreshScreen();
		if (key == 26) saveExit();
		if (key == 27) escapeActive = true;
		if (key == 407) return false;
		if (key >= 32 && key <= 127) insertChar();
		if (key == 258) moveDown();
		if (key == 259) moveUp();
		if (key == 260) moveLeft();
		if (key == 261) moveRight();
		if (key == 263) deleteChar();
		if (key == 265) clearScreen();
		if (key == 276) readCommand();
		if (key == 338) movePgDown();
		if (key == 339) movePgUp();
		if (key == 360) cmdSelect();
		tty.move(row, col);
		tty.refresh();
	}
  return dispatchLoop;
}

Eve::Eve(string fileName) {
	tty.init();
	row = 0;
	col = 0;
	firstLine = 0;
	maxRow = tty.getHeight() - 4;
	maxCol = tty.getWidth() - 1;
	deb("tty created");
//	int apa = tty.getHeight();
	readFile(fileName);
	displayFile();
	displayStatus();
	key = 0;
    while (Eve::dispatch()) {
    	deb("row=" << row << "/" << maxRow << ", col=" << col << ", fPtr=" << firstLine << ", flines=" << flines);
    	key = tty.mvGetKey(row, col);
    }
}

int main(int args, char* argv[]) {
    if (args != 2) {
    	cout << "?Invalid number of parameters" << endl;
    } else {
    	ifstream infile {argv[1]};
    	if (infile) {
    		infile.close();
    		Eve eveMain(argv[1]);
    	} else {
    		cout << "?Could not open " << argv[1] << "for editing" << endl;
    	}
    }
}
