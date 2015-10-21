/*
 * Buffer.cpp
 *
 *  Created on: Oct 21, 2015
 *      Author: sebis
 */

#include "Buffer.hpp"

#include "Source/Position.hpp"
#include "tty.hpp"

using namespace std;

Buffer::Buffer (string fileName, string buffName, Tty& tty) {
	pos = Position(0, 0);
	file = fileName;
	name = buffName;
	if (file != "") {
		this->readFile();
	}
	this->tty = tty;
}

void Buffer::readFile() {
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
	stringstream ss;
	ss << cnt << " lines read from " << file;
	tty.putMessage(ss.str());
}

string& Buffer::currentLine() {
	return string& data[pos.row];
}

