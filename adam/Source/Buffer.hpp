/*
 * Buffer.hpp
 *
 *  Created on: Oct 21, 2015
 *      Author: sebis
 */

#ifndef BUFFER_HPP_
#define BUFFER_HPP_

#include <vector>

#include "Position.hpp"

class Buffer {
	Position pos;
	std::string file;
	std::string name;
	std::vector<std::string> data;
	Tty tty;
public:
	Buffer(std::string fileName, std::string bufName, Tty& tty);
	void readFile();
	int getChar();
	std::string& currentLine();
};


#endif /* BUFFER_HPP_ */
