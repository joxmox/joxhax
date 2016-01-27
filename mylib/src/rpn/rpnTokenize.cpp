/*
 * test5.cpp
 *
 *  Created on: Jan 25, 2016
 *      Author: joxmox
 */

#include <iostream>
#include <map>

#include "rpnStuff.hpp"

using namespace std;

int main() {
	rpn::Expression pe {" 5 + x * 3  "};
	pe.dump();
	map<string, string> m;
	m["x"] = "2";
	m["y"] = "3";
	m["z"] = "-1";
	cout << pe.evalI(m) << endl;
	rpn::Expression p2 {"5 * x + z * ( y + 3 )"};
	cout << p2.evalI(m) << endl;
}


