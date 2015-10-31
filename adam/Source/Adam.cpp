/*
 * adam.cpp
 *
 *  Created on: Oct 21, 2015
 *      Author: sebis
 */

#include <string>
#include "tty.hpp"
#include "Buffer.hpp"
#include "Position.hpp"
#include "Screen.hpp"
#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

//vector<*Buffer> bufferVec;
unordered_map<string, *Buffer> bufferMap;
Buffer *buffer;
Tty *tty;
int key;
Screen *scr;

bool dispatchKey(int key) {
	bool sts = true;
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

int main(int argc, char* argv[]) {
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
	scr = new Screen;
	buffer = new Buffer(fileName);
	bufferVec.push_back(buffer);
	bufferMap[fileName] = buffer;
	int readLines = buffer->readFile(fileName);
//	scr->displayBuffer(buffer);

	tty->putMessage(readLines + " lines read from " + fileName);
	int dispatchLoop = true;
	while (dispatchLoop) {
		dispatchLoop = dispatchKey(tty->getKey());
	}
}


