/*
 * Debug.cpp
 *
 *  Created on: Oct 25, 2015
 *      Author: joxmox
 */


#include <string>
#include <fstream>

using namespace std;

void dbgInit(const string s) {
	fstream f;
	f.open("adam.log", fstream::out | fstream::trunc);
	f << "----------------------------------------------" << endl;
	f << s << ": initialized" << endl;
	f.close();
}

void dbg(const string a, const string b, const string s) {
	fstream f;
	f.open("adam.log", fstream::out | fstream::app);
	f << a << " " << b << ": " << s << endl;
	f.close();
}
