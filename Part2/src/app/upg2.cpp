#include <iostream>
#include <stdexcept>
#include "Trace.hpp"

using namespace std;

int factorial(int n) {
	Trace t {"factorial " + to_string(n)};
	if (n<=1) return 1;
	if (n==5) throw invalid_argument("5 is an evil number");
	return n * factorial(n-1);
}

void doFac(int n) {
	int r = factorial(n);
	cout << n << "! = " << r << endl;
}

int main() {
	try {
		doFac(4);
		doFac(8);
		doFac(2);
	} catch (exception& e) {
		cout << "error from factorial: " << e.what() << endl;
	}
	return 0;
}
