/*
 * Buffer.cpp
 *
 *  Created on: Oct 21, 2015
 *      Author: sebis
 */

#include <string>
#include "Buffer.hpp"
#include "Position.hpp"
#include <iostream>

using namespace std;

Buffer::Buffer (string buffName) {
	pos = Position(0, 0);
	name = buffName;
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
	int cnt = 0;
	string line;
	while (getline(inf, line)) {
		data.push_back(line);
		cnt++;
	}
	return cnt;
}

string& Buffer::currentLine() {
	return data[pos.getRow()];
}

int Buffer::getChar() {
	return 1;
}

