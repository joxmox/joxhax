/*
 * temlat.cpp
 *
 *  Created on: Nov 3, 2015
 *      Author: sebis
 */

#include <string>
#include <iostream>

using namespace std;

template<typename T>
bool cmpequ(T a, T b, T c) {
	cout << "Comparing: " << a << "," << b << "," << c << endl;
	if ((a == b) && (b == c)) return true; else return false;
}

int main() {
	cout << cmpequ(1, 2, 3) << endl;
	cout << cmpequ(4, 4, 4) << endl;
	cout << cmpequ('x', 'y', 'z') << endl;
	cout << cmpequ("abc", "def", "gih") << endl;
	cout << cmpequ("foo", "foo", "foo") << endl;
	cout << cmpequ(string("aaa"), string("bbb"), string("ccc")) << endl;
	cout << cmpequ(string("apa"), string("apa"), string("apa")) << endl;
	cout << cmpequ(1.0, 1.000001, 1.0) << endl;
	cout << cmpequ(3.14, 3.14, 3.14) << endl;
}


