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
#include "Size.hpp"
#include "Screen.hpp"
#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

Buffer* buffer;
vector<Buffer*> bufferVec;
unordered_map<string, Buffer*> bufferMap;
Tty* tty;
int key;
Screen* scr;
unordered_map<string, Screen*> scrMap;

bool dispatchKey(int key) {
	deb ("key = " + to_string(key));
	bool sts = true;
	if (key == 26) sts = false;
	if (key == 407) sts = false;
	if (key == 410) tty->handleResize();
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
	Size fullSize = tty->getTtySize();
	deb("tty created: " + to_string(fullSize.getHeight()) + "x" + to_string(fullSize.getWidth()));

	scr = new Screen(tty, Screen::full);
	deb("default full screen created: " + to_string((long long) scr));
	tty->setScreen(scr);
	scrMap["default"] = scr;
//	scrMap["upper"] = new Screen(tty, upperHalf);
//	scrMap["lower"] = new Screen(tty, lowerHalf);
	deb("created other screens");

	buffer = new Buffer(fileName);
	bufferVec.push_back(buffer);
	bufferMap[fileName] = buffer;
	deb("buffer " + fileName + " created");
	scr->setBuffer(buffer);
	deb("default screen linked to buffer");

	int readLines = buffer->readFile(fileName);
	deb(to_string(readLines) + " lines read");
	scr->displayBuffer();
	deb("buffer contents displayed");

	tty->putMessage(to_string(readLines) + " lines read from " + fileName);
	int dispatchLoop = true;
	while (dispatchLoop) {
		dispatchLoop = dispatchKey(tty->getKey());
	}
	deb("delete tty");
	delete(tty);
	deb("exiting");
}


