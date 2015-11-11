/*
 * Buffer.hpp
 *
 *  Created on: Oct 21, 2015
 *      Author: sebis
 */

#pragma once

#include <vector>
#include <fstream>
#include <unordered_map>

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
	std::unordered_map<std::string, Position> markMap;
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
	void setPos(Position);
	Position getEndPos();
	int getEndLine();
	std::string getLine(int);
	std::string getLine(Position);
	std::string getCurLine(int=0);
	void insertChar(int key);
	void moveLeft();
	void moveRight();
	void moveUp();
	void moveDown();
	int getSelect();
	void dump();
	void adjustRow(Position& p);
	void breakLine();
	void delChar();
	int joinLines();
	int getDataSize();
	void setMark(std::string);
	Position getMark(std::string);
	void recalcMarks(int);

};

