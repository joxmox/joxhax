/*
 * fibban.cpp
 *
 *  Created on: Nov 4, 2015
 *      Author: sebis
 */

#include <iostream>

using namespace std;

void dbg(string s) {
	cout << s << endl;
}

class Fib {
	int num;
public:
	Fib(int num = 10): num(num) {}
	struct iterator {
		long long count, first, second, current;
		iterator(int n): count(n), first(0), second(1), current(0) {}
		long long operator *() {return current;}
		iterator& operator ++() {first = second; second = current; current = first + second; count++; return *this;}
		bool operator !=(const iterator& z) {return this->count < z.count;}
	};
	iterator begin() {dbg("beg"); return {1};}
	iterator end() {dbg("end"); return {num + 1};}
};


int main() {
	Fib z(10);
	for (auto k : Fib(30)) cout << k << endl;
}


