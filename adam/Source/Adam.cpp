/*
 * adam.cpp
 *
 *  Created on: Oct 21, 2015
 *      Author: sebis
 */

#include <Debug.hpp>
#include <string>
#include "tty.hpp"
#include "Buffer.hpp"
#include "Position.hpp"
#include "Size.hpp"
#include "Screen.hpp"
#include "ops.hpp"
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
	DBG << "Key :" << key << endl;
	bool sts = true;
	if (key == 4) buffer->dump();
	if (key == 13) scr->breakLine();
	if (key == 26) sts = false;
	if (key >= 32 && key <= 127) scr->insertChar(key);
	if (key == 258) scr->moveDown();
	if (key == 259) scr->moveUp();
	if (key == 260) scr->moveLeft();
	if (key == 263) scr->deleteChar();
	if (key == 261) scr->moveRight();
	if (key == 276) scr->readCommand();
	if (key == 407) sts = false;
	if (key == 410) tty->handleResize();
//	deb("key=" << key << ", Esc=" << escapeActive);
	//if (escapeActive) key = processEscape();
	/*
	if (key == -1) saveExit();
	if (key == 0) return true;
	if (key == 5) gotoEol();
	if (key == 8) gotoSol();
	if (key == 23) refreshScreen();
	if (key == 26) saveExit();
	if (key == 27) escape_active = true;
	if (key == 407) return false;
	if (key >= 32 && key <= 127) insertChar();
	if (key == 265) clearScreen();
	if (key == 360) cmdSelect();
	*/
    scr->position();
	tty->refresh();
  return sts;
}


int main(int argc, char* argv[]) {
	DBGINI("adam.log");
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
	DBG << "tty created: " << fullSize.getHeight() << "x" << fullSize.getWidth() << endl;

	scr = new Screen(tty, Screen::full);
	DBG << "default full screen created " << endl;
	tty->setScreen(scr);
	scrMap["default"] = scr;
//	scrMap["upper"] = new Screen(tty, upperHalf);
//	scrMap["lower"] = new Screen(tty, lowerHalf);
	DBG << "created other screens" << endl;

	buffer = new Buffer(fileName);
	bufferVec.push_back(buffer);
	bufferMap[fileName] = buffer;
	DBG << "buffer " << fileName << " created" << endl;
	scr->setBuffer(buffer);
	DBG << "default screen linked to buffer" << endl;

	int readLines = buffer->readFile(fileName);
	DBG << readLines << " lines read from " << fileName << endl;
	scr->displayBuffer();
	DBG << "buffer contents displayed" << endl;

	tty->putMessage(to_string(readLines) + " lines read from " + fileName);
	int dispatchLoop = true;
	scr->position();
	while (dispatchLoop) {
		DBG << "Buf: " << buffer->getPos() << " Scr: " << scr->getPos() << endl;
		dispatchLoop = dispatchKey(tty->getKey());
	}
	DBG << "deleting tty" << endl;
	delete(tty);
	DBG << "exiting" << endl;
}


