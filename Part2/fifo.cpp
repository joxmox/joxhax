/*
 * fifo.cpp
 *
 *  Created on: Nov 3, 2015
 *      Author: sebis
 */

#include <iostream>

using namespace std;

template<typename T, unsigned N>
class Stack  {
	T stk[N];
	unsigned top=0;
public:
	bool empty() {return (top == 0);}
	bool full() {return (top == N);}
	void push(T x) {stk[top++] = x;}
	T pop() {return stk[--top];}
	void operator <<(T x) {stk[top++] = x;}
	T operator >>() {return stk[--top];}
	bool operator ==(int x) {return top == x;}
	bool operator !=(int x) {return top != x;}
};

int main() {
	Stack<int, 10> s1;
	s1.push(10); s1.push(20); s1.push(30);
	while (!s1.empty()) cout << s1.pop() << endl;
	cout << endl;

	Stack<string, 10> s2;
	s2.push("hi"); s2.push("yo"); s2.push("howdy");
	while (!s2.empty()) cout << s2.pop() << endl;
	cout << endl;

	Stack<short, 10> s3;
	int i = 1;
	while (!s3.full()) s3.push(i++);
	while (!s3.empty()) cout << s3.pop() << endl;
	cout << endl;

	Stack<int, 3> s4;
	s4 << 11; s4 << 22; s4 << 33;
    while(s4 != 0) {int a; s4 >> a; cout << a << endl;}
	return 0;
}



