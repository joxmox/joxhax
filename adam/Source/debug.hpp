/*
 * Debug.hpp
 *
 *  Created on: Oct 25, 2015
 *      Author: joxmox
 */

#ifndef DEBUG_HPP_
#define DEBUG_HPP_

#ifdef DBG
#include <string>
#include <sstream>
void dbgInit(const std::string s);
void dbg2()
void dbg(const std::string a, const std::string b, const std::string s);
#define debInit() dbgInit(__FUNCTION__);
#define deb(x) dbg(__FILE__, __FUNCTION__, x);
#else
#define deb(x) //
#endif

#endif /* DEBUG_HPP_ */

void dbg8(std::stringstream s) {

}

dbg8("kalle" << "sune");

