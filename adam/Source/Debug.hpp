/*
 * Debug.hpp
 *
 *  Created on: Nov 9, 2015
 *      Author: joxmox
 */

#pragma once

#include <fstream>
#include <string>

#define DBGFLG 1

#ifdef DBGFLG
#define DBG Debug::ofs << __FUNCTION__ << ": "
#define DBGINI(x) Debug dbg(x)
#else
#define DBG //
#define DBGINI //
#endif

class Debug {
	static int users;
	static std::string fileName;
public:
	static std::ofstream ofs;
	Debug(std::string s = "debug.log");
	~Debug();
};
