/*
 * adam.cpp
 *
 *  Created on: Oct 21, 2015
 *      Author: sebis
 */

#include <debug.hpp>
#include <string>
#include "tty.hpp"
#include "Buffer.hpp"
#include "Position.hpp"
#include "Screen.hpp"
#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

vector<Buffer *> bufferVec;
unordered_map<string, Buffer *> bufferMap;
Buffer *buffer;
Tty *tty;
int key;
Screen *scr;

bool dispatchKey(int key) {
	bool sts = true;
	if (key == 26) sts = false;
//	deb("key=" << key << ", Esc=" << escapeActive);
	//if (escapeActive) key = processEscape();
	/*
	if (key == -1) saveExit();
	if (key == 0) return true;
	if (key == 4) debugDump();
	if (key == 5) gotoEol();
	if (key == 8) gotoSol();
	if (key == 13) breakLine();
	if (key == 23) refreshScreen();
	if (key == 26) saveExit();
	if (key == 27) escape_active = true;
	if (key == 407) return false;
	if (key >= 32 && key <= 127) insertChar();
	if (key == 258) moveDown();
	if (key == 259) moveUp();
	if (key == 260) moveLeft();
	if (key == 261) moveRight();
	if (key == 263) deleteChar();
	if (key == 265) clearScreen();
	if (key == 360) cmdSelect();
	*/
	tty->move(buffer->getRow(), buffer->getCol());
	tty->refresh();
  return sts;
}

void displayBuffer(Buffer* buf) {
    int r = 0;
    int f = buf->getTopLine();
    for (f=buf->getTopLine(); f<=buf->getMaxLine(), r<=maxRow; r++, f++) {
        tty->move(r, 0);
        tty->print(fData[f], -1);
        tty->clearToEol();
    }
    if (r <= maxRow) {
    	deb("printing EOF marker at line ");
    	tty->move(r++, 0);
    	tty->print("[End of file]", -1);
    }
    while (r <= maxRow) {
    	tty->move(r++, 0);
    	tty->clearToEol();
    }
}

int main(int argc, char* argv[]) {
	debInit();
    if (argc != 2) {
    	cout << "?Invalid number of parameters" << endl;
    	return 1;
    }
    string fileName = argv[1];
	ifstream infile {fileName};
	if (!infile) {
		cout << "?Could not open " << fileName << "for editing" << endl;
		return 1;
    }
	tty = new Tty;
	deb("tty created");
//	scr = new Screen(tty);
	buffer = new Buffer(fileName);
	bufferVec.push_back(buffer);
	bufferMap[fileName] = buffer;
	deb("buffer " + fileName + " created");
	int readLines = buffer->readFile(fileName);
	deb(to_string(readLines) + " lines read");
//	scr->displayBuffer(buffer);
	displayBuffer(buffer);

	tty->putMessage(to_string(readLines) + " lines read from " + fileName);
	int dispatchLoop = true;
	while (dispatchLoop) {
		dispatchLoop = dispatchKey(tty->getKey());
	}
	deb("delete tty");
	delete(tty);
	deb("exiting");
}


