/*
 * main.cpp
 *
 *  Created on: Oct 21, 2015
 *      Author: sebis
 */

#include <fstream>
#include <iostream>
#include "Adam.hpp"

using namespace std;

int main(int argc, char* argv[]) {
	/*
    if (argc != 2) {
    	cout << "?Invalid number of parameters" << endl;
    	return 1;
    }
	ifstream infile {argv[1]};
	if (!infile) {
		cout << "?Could not open " << argv[1] << "for editing" << endl;
		return 1;
    }
	Adam adam(argv[1]);
	*/
	Adam adam("apa.txt");
	if (adam.endedInError()) {
		cout << adam.getExitError() << endl;
	}
}


