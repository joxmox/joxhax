/*
 * adam.cpp
 *
 *  Created on: Oct 21, 2015
 *      Author: sebis
 */

#include "tty.hpp"
#include "Buffer.hpp"
#include "Position.hpp"
#include "Screen.hpp"

using namespace std;

Adam::Adam(string fileName) {
	this->fileName = fileName;
	this->tty = Tty();									// we need one tty
	this->buffer = this->createBuffer(this->fileName, this->fileName, tty);
	buffer->readFile();
	buffer->getChar();

}

vector<Buffer>::iterator Adam::createBuffer(string bufName, string fileName, Tty& tty) {
	this->bufferVec.push_back(Buffer(bufName, fileName, tty));
	vector<Buffer>::iterator curBuff = bufferVec.end();
	--curBuff;
	this->bufferMap[bufName] = curBuff;
	return curBuff;
}




