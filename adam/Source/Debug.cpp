/*
 * Debug.cpp
 *
 *  Created on: Nov 9, 2015
 *      Author: joxmox
 */

#include <string>
#include <fstream>
#include "Debug.hpp"

using namespace std;

int Debug::users = 0;
string Debug::fileName;
ofstream Debug::ofs;


Debug::Debug(string s) {
	if (users++ == 0) {
		fileName = s;
		ofs.open(fileName.c_str());
	}
}

Debug::~Debug() {
	if (--users == 0) {
		ofs.close();
	}
}



