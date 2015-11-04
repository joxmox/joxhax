/*
 * random.cpp
 *
 *  Created on: Nov 4, 2015
 *      Author: sebis
 */

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

class Random {
	string fileName;
public:
	Random(string f): fileName(f) {}
	struct Position {
		int lnr;
		const string& fileName;
		Position(int l, const string& f): lnr(l), fileName(f) {}
		operator string() const {}
		Position& operator=(const string& l) {
			return Position(1, "2");
		}
	};
};

int main() {
	Random("random.txt");

}


