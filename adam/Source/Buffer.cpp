/*
 * Buffer.cpp
 *
 *  Created on: Oct 21, 2015
 *      Author: sebis
 */

#include <Debug.hpp>
#include <string>
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

Position& Buffer::getPos() {
	return pos;
}

int Buffer::getTopLine() {
	return 0;
}

int Buffer::getMaxLine() {
	return data.size();
}

string Buffer::getLine(int i) {
	if (i < data.size()) return data[i];
	if (i > data.size()) return "";
	return "[End of file]";
}

string Buffer::getCurLine(int a) {
	return getLine(pos.getRow() + a);
}

void Buffer::insertChar(int key) {
	data[pos.getRow()].insert(pos.getCol(), string(1, key));
	pos++;
}

void Buffer::moveLeft() {
	if (pos.getCol() > 0) pos--;
}

void Buffer::moveRight() {
	DBG << "Col: " << pos.getCol() << endl;
//	deb("Col: " + to_string(pos.getCol()))
	if (pos.getCol() < data[pos.getRow()].length()) {
		pos++;
	}
}

void Buffer::moveUp() {
	if (pos.getRow() > 0) pos.moveUp();
}

void Buffer::moveDown() {
	pos.moveDown();
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
		DBG << x << endl;
	}
}

void Buffer::adjustRow(Position& p) {
	DBG << p << " " << pos << endl;
	int c = pos.setCol(p.getCol());
	int r = pos.getRow();
	int s = data[r].size();
	if (c > s) {
		DBG << "|" << data[r] << "|" << endl;
		data[r] += string(c - s, ' ');
		DBG << "|" << data[r] << "|" << endl;
	}
}

void Buffer::breakLine() {
	string ss = data[pos.getRow()];
	int len = ss.length();
	int row = pos.getRow();
	int col = pos.getCol();
	string sr = ss.substr(col, len - col);
	data[row] = ss.substr(0, col);
	data.insert(data.begin() + row + 1, sr);
	pos.moveDown();
	pos.setCol(0);
}

