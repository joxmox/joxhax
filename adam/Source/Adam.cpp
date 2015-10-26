/*
 * adam.cpp
 *
 *  Created on: Oct 21, 2015
 *      Author: sebis
 */

#include <string>
#include "Adam.hpp"
#include "tty.hpp"
#include "Buffer.hpp"
#include "Position.hpp"
#include "Screen.hpp"
#include <iostream>

using namespace std;

Adam::Adam(string fileName) {
	this->fileName = fileName;
	cout << "opening " << fileName << endl;
	tty.init();
	this->buffer = this->createBuffer(fileName);
	buffer->readFile(fileName);
	dispatchKey(tty.getKey());
}

vector<Buffer>::iterator Adam::createBuffer(string bufName) {
	this->bufferVec.push_back(Buffer(bufName));
	vector<Buffer>::iterator curBuff = bufferVec.end();
	--curBuff;
	this->bufferMap[bufName] = curBuff;
	return curBuff;
}

bool Adam::endedInError() {
	return false;
}

string Adam::getExitError() {
	return "";
}

void Adam::dispatchKey(int key) {
//	dispatchLoop = true;
	int sts = true;
//	deb("key=" << key << ", Esc=" << escapeActive);
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
		tty.move(row, col);
		tty.refresh();
	}
  return dispatchLoop;
}

}


