/*
 * Buffer.hpp
 *
 *  Created on: Oct 21, 2015
 *      Author: sebis
 */

#ifndef BUFFER_HPP_
#define BUFFER_HPP_

#include <vector>
#include <fstream>

#include "Position.hpp"

class Buffer {
	Position pos;
	std::string file;
	std::string name;
	std::vector<std::string> data;
public:
	Buffer(std::string buffName);
	int readFile(std::string fileName);
	int getChar();
	std::string& currentLine();
};


#endif /* BUFFER_HPP_ */
