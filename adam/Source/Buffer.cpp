/*
 * Buffer.cpp
 *
 *  Created on: Oct 21, 2015
 *      Author: sebis
 */

#include <string>
#include "debug.hpp"
#include "Buffer.hpp"
#include "Position.hpp"
#include "ops.hpp"
#include <iostream>

using namespace std;

Buffer::Buffer (string buffName) {
	pos = Position(0, 0);
	name = buffName;
	maxLine = -1;
	topLine = 0;
	curLine = 0;
}

int Buffer::readFile(string fileName) {
	cout << "in readfile " << fileName << endl;
	file = fileName;
	data.clear();
	pos.setPos(0, 0);
	ifstream inf{file};
	if (!inf) {
		// throw error
	}
	string line;
	while (getline(inf, line)) {
		data.push_back(line);
		maxLine++;
	}
	return maxLine + 1;
}

string Buffer::getFileName() {
	return file;
}

string& Buffer::currentLine() {
	return data[pos.getRow()];
}

int Buffer::getChar() {
  return 0;
}

int Buffer::getRow() {
	return pos.getRow();
}

int Buffer::getCol() {
	return pos.getCol();
}

int Buffer::getTopLine() {
	return 0;
}

int Buffer::getMaxLine() {
	return data.size();
}

string Buffer::getLine(int i) {
	return data[i];
}

void Buffer::insertChar(int key) {
	data[pos.getRow()].insert(pos.getCol(), string(1, key));
	pos++;
}

void Buffer::moveLeft() {
	if (pos.getCol() > 0) pos--;
}

void Buffer::moveRight() {
	deb("Col: " + to_string(pos.getCol()))
	if (pos.getCol() < data[pos.getRow()].length()) {
		pos++;
	}
}

int Buffer::getSelect() {
	if (selectActive) {
		if (pos < selectPos) {
			return -1;
		} else {
			return 1;
		}
	} else {
		return 0;
	}
}

void Buffer::dump() {
	for (auto x : data) {
		deb(x);
	}
}
