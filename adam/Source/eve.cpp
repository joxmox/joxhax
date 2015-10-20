#include <iostream>
#include <fstream>
#include "tty.hpp"
#include "parse.hpp"
#include <unistd.h>
#include <list>
#include <vector>
#include <sstream>

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
  Tty tty;
  vector<string> fData;
  int fPtr;
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
  void cmdShowDefault();
  void cmdShowScreen();
  void cmdMark(string mrk);
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
    clearScreen();
    int r = 0;
    int c = 0;
    int f = fPtr - row;
    if (f < 0) f = 0;
    while (r <= maxRow && f < fData.size()) {
        deb("row=" << r << ", f=" << f << ", data=" << fData[f]);
        tty.mvPrint(r++, c, fData[f++]);
    }
    if (r <= maxRow) {
    	deb("printing EOF marker at line " << r)
    	tty.mvPrint(r, c, "[End of file]");
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
  tty.putChar(key);
  deb("line before = |" << fData[fPtr] << "|");
  tty.move(row, 0);
  fData[fPtr] = tty.getLine(fData[fPtr].length()+1);
  deb("line after = |" << fData[fPtr] << "|"); 
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
  int curLen = adjustLength(); 
  deb("current line =|" << fData[fPtr] << "|");
  string sright = tty.getLine(curLen - this->col);
  deb("right part =|" << sright << "|");
  tty.clearToEol();
  deb("cleared from cursor to eol");
  tty.move(row, 0);
  deb("moved to sol");
  string sleft = tty.getLine(col);
  deb("left part =|" << sleft << "|");
  fData[fPtr] = sleft;
  tty.move(++row, 0);
  tty.insertLine();
  deb("inserted new blank line");
  tty.print(sright);
  fData.insert(fData.begin() + ++fPtr, sright);
  this->col = 0;
  flines++;
}

void Eve::deleteChar() {
  int curLen = adjustLength();
  if (col > 0) {
    tty.move(row, --col);
    tty.delChar();
    tty.move(row, 0);
    fData[fPtr] = tty.getLine(curLen - 1);
  } else {
    if (fPtr > 0) {
      col = fData[fPtr-1].length();
      string str = fData[fPtr];
      tty.delLine();
      tty.move(--row, col);
      tty.print(str);
      fData[fPtr-1] += fData[fPtr];
      fData.erase(fData.begin() + fPtr--);
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
	tty.putMessage("mark " + mrk);
}

void Eve::readCommand() {
	static vector<pair<int, string>> ptab {
		{1, "show default"},
		{2, "show screen"},
		{3, "mark *"},
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
		tty.move(row, col);
		tty.refresh();
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
	int apa = tty.getHeight();
	readFile(fileName);
	displayFile();
	displayStatus();
	key = 0;
    while (Eve::dispatch()) {
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







