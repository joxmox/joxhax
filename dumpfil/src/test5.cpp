/*
 * test5.cpp
 *
 *  Created on: Jan 25, 2016
 *      Author: joxmox
 */

#include <iostream>
#include <map>

#include "rpnExp.hpp"

using namespace std;

int main() {
	rpnExp pe {" 5 + x * 3  "};
	pe.dump();
	map<string, string> m;
	m["x"] = "2";
	m["y"] = "3";
	m["z"] = "-1";
	cout << pe.eval(m) << endl;
	rpnExp p2 {"5 * x + z * ( y + 3 )"};
	cout << p2.eval(m) << endl;
}


