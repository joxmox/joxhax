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
  int fPtr;
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
  fPtr = 0;
  stringstream ss;
  ss << flines << " lines read from " << fileName; 
  tty.putMessage(ss.str());
  return true;
}

void Eve::displayFile() {
    int r = 0;
    int f = fPtr - row;
    int mark1r, mark1c, mark2r, mark2c;
    deb("fPtr=" << f << ", row=" << row << ", f=" << f);
    if (selectActive) {
    	if (cmpPos(fPtr, col, selectLine, selectCol) == 1) {
    		mark1r = fPtr;
    		mark1c = col;
    		mark2r = selectLine;
    		mark2c = selectCol;
    	} else {
       		mark1r = fPtr;
        	mark1c = col;
        	mark2r = selectLine;
       		mark2c = selectCol;
    	}
    }
    if (f < 0) f = 0;
    while (r <= maxRow && f < fData.size()) {
        deb("row=" << r << ", f=" << f << ", data=" << fData[f]);
        if (selectActive) {
        	if (f == selectLine) {
        		if (f == mark1r) {
        			tty.mvPrint(r, 0, fData[f].substr(0, mark1c));
        			tty.reverseOn();
        			tty.mvPrint(r, col, fData[f].substr(mark1c));
        		}
        		if (f == mark2r) {
        			tty.mvPrint(r, 0, fData[f].substr(0, mark2c));
        			tty.reverseOff();
        			tty.mvPrint(r, col, fData[f].substr(mark2c));
        		}
        	}
        } else {
          tty.mvPrint(r, 0, fData[f]);
        }
        tty.clearToEol();
        f++;
        r++;
    }
    if (r <= maxRow) {
    	deb("printing EOF marker at line " << r)
    	tty.mvPrint(r++, 0, "[End of file]");
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
	fData[fPtr].insert(fData[fPtr].begin() + col, key);
	col++;
}

int Eve::adjustLength() {
  int curLen = fData[fPtr].length();
  if (col > curLen) {
    fData[fPtr] += string(col - curLen, ' ');
  }
  return fData[fPtr].length();
}

void Eve::breakLine() {
	adjustLength();
	fData.insert(fData.begin() + fPtr + 1, fData[fPtr].substr(col));
	fData[fPtr].erase(col);
	col = 0;
	fPtr++;
	if (row < maxRow) row++;
	flines++;
}

void Eve::deleteChar() {
	adjustLength();
	if (col > 0) {
		fData[fPtr].erase(fData[fPtr].begin() + --col);
	} else {
		if (fPtr > 0) {
			col = fData[fPtr-1].length();
			fData[fPtr-1] += fData[fPtr];
			fData.erase(fData.begin() + fPtr--);
		}
		--flines;
	}
}
      
    
void Eve::processCtrl() {
}

void Eve::processFunc() {
  switch(key) {
    case 258: Eve::moveDown(); break;
  }
}

void Eve::moveDown() {
	deb("flines=" << flines << ", row=" << row << ", size=" << fData.size() << ", fPtr=" << fPtr);
	if (fPtr < fData.size() - 1) {
		fPtr++;
		if (row < maxRow) {
			row++;
		} else {
			deb("window should scroll here...");
			deb("fPtr: " << fPtr)
			deb("fData: " << fData[fPtr])
			tty.move(0, 0);
			tty.delLine();
			tty.move(maxRow, 0);
			tty.print(fData[fPtr]);
		}
	} else {
		deb("already on last line");
	}
}

void Eve::moveUp() {
	deb("flines=" << flines << ", row=" << row << ", size=" << fData.size() << ", fPtr=" << fPtr);
	if (fPtr > 0) {
		--fPtr;
		if (row > 0) {
			--row;
		} else {
			deb("window should scroll here...");
			tty.move(0, 0);
			tty.insertLine();
			tty.move(0, 0);
			tty.print(fData[fPtr]);
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
  } else {
    deb("already at column 0");
  }
}

void Eve::moveRight() {
	if (col < maxCol) {
		col++;
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
  int curLen = fData[fPtr].length();
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
}

void Eve::debugDump() {
  int i = 0;
  deb("----------");
  deb("flines=" << flines);
  for (auto f : fData) {
    deb(i++ << " [" << f.length() << "]: |" << f << "|");
  }
  deb("fPtr=" << fPtr);
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
	markMap[mrk] = fPtr;
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
	deb("row=" << row << ", fPtr=" << fPtr << ", flines=" << flines);
	col = 0;	//always goto beginning of line
	int topLine = fPtr - row;	//first line in view
	int botLine = topLine + maxRow;	//last line in view
	if (botLine > flines) botLine = flines;
	if (lnr < topLine || lnr > botLine) {
		deb("outside current window");
		if (lnr < fPtr) {
			row = 0;
		} else {
			row = maxRow;
		}
	} else {
		deb("inside current window");
		row += lnr - fPtr;
	}
	fPtr = lnr;
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
		selectActive = false;
	} else {
		selectActive = true;
		selectLine = fPtr;
		selectCol = col;
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
	int res = parse.decode(cmd);
	switch(res) {
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
		if (key == 360) cmdSelect();
		displayFile();
	}
  return dispatchLoop;
}

Eve::Eve(string fileName) {
	Tty tty;
	row = 0;
	col = 0;
	fPtr = 0;
	maxRow = tty.getHeight() - 4;
	maxCol = tty.getWidth() - 1;
	deb("tty created");
	tty.init();
	deb("tty initialized");
	readFile(fileName);
	deb("file read");
	displayFile();
	deb("file displayed");
	displayStatus();
	key = 0;
    while (Eve::dispatch()) {
    	deb("row=" << row << "/" << maxRow << ", col=" << col << ", fPtr=" << fPtr << ", flines=" << flines);
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







