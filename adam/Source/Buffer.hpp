/*
 * Buffer.hpp
 *
 *  Created on: Oct 21, 2015
 *      Author: sebis
 */

#pragma once

#include <vector>
#include <fstream>

#include "Position.hpp"

class Buffer {
	int topLine;
	int maxLine;
	int curLine;
	Position pos;

	std::string file;
	std::string name;
	std::vector<std::string> data;
	bool selectActive = false;
	Position selectPos = {0, 0};
public:
	Buffer(std::string buffName);
	int readFile(std::string fileName);
	std::string getFileName();
	int getChar();
	std::string& currentLine();
	Position& getPos();
	int getRow();
	int getCol();
	int getTopLine();
	int getMaxLine();
	std::string getLine(int);
	std::string getCurLine();
	void insertChar(int key);
	void moveLeft();
	void moveRight();
	void moveUp();
	void moveDown();
	int getSelect();
	void dump();
	void adjustRow(Position& p);
};

