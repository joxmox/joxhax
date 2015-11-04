/*
 * Trace.hpp
 *
 *  Created on: Nov 2, 2015
 *      Author: sebis
 */

#ifndef SRC_LIB_TRACE_HPP_
#define SRC_LIB_TRACE_HPP_

#include <string>
using namespace std;

class Trace {
	string func;
public:
	Trace(string s) {
		func = s;
		cout << "[enter] " << s << endl;
	}
	~Trace() {
		cout << "[exit] " << func << endl;
	}
};

#endif /* SRC_LIB_TRACE_HPP_ */
