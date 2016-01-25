/*
 * test5.cpp
 *
 *  Created on: Jan 25, 2016
 *      Author: joxmox
 */

#include <iostream>
#include <map>

using namespace std;

enum e {ape, fish, gnu, fly, snake, man};

static map<e, int> x {
	{ape, 4},
	{fish, 0},
	{gnu, 4},
	{fly, 6},
	{snake, 0},
	{man, 2},
};

int main() {
	cout << x[fly] << endl;
}

