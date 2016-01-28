/*
 * tokenize.cpp
 *
 *  Created on: Jan 28, 2016
 *      Author: joxmox
 */

#include <string>
#include <vector>
#include <map>

namespace jox {

using namespace std;

static map<string, int> operatorMap {
	{"!", 10},
	{"not", 10},
	{"*", 20},
	{"/", 20},
	{"+", 30},
	{"-", 30},
	{"<", 40},
	{"<=", 40},
	{">", 40},
	{">=", 40},
	{"==", 50},
	{"=", 50},
	{"!=", 50},
	{"&&", 60},
	{"and", 60},
	{"||", 70},
	{"or", 70},
};

vector<string> tokenize(const string&) {
	vector<string> result;
	return result;
}

vector<string> infix2postfix(vector<string>&) {
	vector<string> result {"x", "y", "*", "zz", "and"};
	return result;
}

bool isOperator(const string& op) {
	if (operatorMap.find(op) == operatorMap.end()) return false;
	else return true;
}

int operatorCmp(const string& opa, const string& opb) {

	if (operatorMap.find(opa) == operatorMap.end() || operatorMap.find(opb) == operatorMap.end()) {
		throw logic_error("invalid operator");
	}
	if (operatorMap[opa] == operatorMap[opb]) return 0;
	if (operatorMap[opa] > operatorMap[opb]) return 1;
	return -1;
}

}


