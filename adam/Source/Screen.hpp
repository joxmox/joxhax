/*
 * Screen.hpp
 *
 *  Created on: Oct 20, 2015
 *      Author: joxmox
 */

#pragma once

#include "Position.hpp"
#include "tty.hpp"
#include "Buffer.hpp"
#include "Size.hpp"
#include <iostream>

class Tty;

class Screen {
public:
	enum scrMode {full, upper, lower};
private:
	static int idCnt;
	int id = 0;
	int win = 0;
	int stsWin;
	Tty* tty;
	Buffer* buf;
	scrMode mode;
	Size siz;
	Position pos;
	Position statusPos;
	std::string stsBuf = "MAIN";
	std::string stsWrt = "Write";
	std::string stsIns = "Insert";
	std::string stsDir = "Forward";
public:
	Screen(Tty* tty, scrMode mode = full);
	Screen(Tty* tty, Buffer* buf, scrMode mode = full);
	bool inView(Position& bPos);
	void setBuffer(Buffer*);
	void displayBuffer();
	Size& getSize();
	Position& getPos();
	void setSize(Size& s);
	void initScreen();
	void printStatus();
	void insertChar(int key);
	void position();
	void moveRight();
	void moveLeft();
	void moveUp();
	void moveDown();
	void breakLine();
	void deleteChar();
	void adjust();
	void gotoPos(Position);
	void readCommand();
	void cmdMark(std::string);
	void cmdLine(std::string);
	void cmdGoto(std::string);
	void pageUp();
	void pageDown();
	std::string toString() const;
	void setStsBuf(std::string s) {stsBuf = s;}
	std::string getStsBuf() {return stsBuf;}
	std::string getStsWrt() {return stsWrt;}
	std::string getStsIns() {return stsIns;}
	std::string getStsDir() {return stsDir;}
	int getId() const {return id;}
};
std::ostream& operator <<(std::ostream&, const Screen);

