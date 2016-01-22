#include <iostream>
#include <string>
#include <vector>
#include <cassert>
#include <map>
#include "strings.hpp"
#include "Condition.hpp"


using namespace std;

int main() {
	string str = "x > 0";
	Condition c {str};
	map<string, pair<char,string>> mm {"x", {'i', "3"}};
	bool b = c.evaluate(mm);
	cout << (b ? "true" : "false") << endl;
}
