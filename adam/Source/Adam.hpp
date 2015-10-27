/*
 * Adam.hpp
 *
 *  Created on: Oct 21, 2015
 *      Author: sebis
 */

#ifndef ADAM_HPP_
#define ADAM_HPP_

#include <vector>
#include <unordered_map>
#include "tty.hpp"
#include "Buffer.hpp"
#include "Position.hpp"
#include "Screen.hpp"

class Adam {
	std::string fileName;
	std::vector<Buffer> bufferVec;
	std::unordered_map<std::string, std::vector<Buffer>::iterator> bufferMap;
	std::vector<Buffer>::iterator buffer;
	Tty tty;
	int key;
public:
	Adam(std::string fileName);
	std::vector<Buffer>::iterator createBuffer(std::string buffName);
	bool endedInError();
	std::string getExitError();
	void dispatchKey(int);
};



#endif /* ADAM_HPP_ */
