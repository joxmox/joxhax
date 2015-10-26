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
	buffer->getChar();
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


