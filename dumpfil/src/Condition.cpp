/*
 * Condition.cpp
 *
 *  Created on: Jan 7, 2016
 *      Author: sebis
 */

#include "Condition.hpp"
#include "strings.hpp"

#include <string>
#include <vector>
#include <functional>
#include <exception>
#include <cctype>
#include <iostream>

using namespace std;

/*
 * 0 - looking for var or (
 * 1 - reading var. may encounter <>!=
 * 2 - looking for operator
 * 3 - reading operator, may enconter value
 */

bool varOK(char c,bool first = false) {
	if (isalnum(c)) return true;
	if (c == '_') return true;
	if (!first and c == '.') return true;
	return false;
}

bool valOK(char c) {
	if (isdigit(c)) return true;
	return false;
}

bool isOper(char c) {
	for (auto x : "<>=!") {
		if (c == x) return true;
	}
	return false;
}

string getOp(const string& s) {
	if (s.find("<=") != string::npos) return "<=";
	if (s.find(">=") != string::npos) return ">=";
	if (s.find("!=") != string::npos) return "!=";
	if (s.find("==") != string::npos) return "==";
	if (s.find("<") != string::npos) return "<";
	if (s.find(">") != string::npos) return ">";
	if (s.find("=") != string::npos) return "=";
	return "";


}


CondEle::CondEle(const string& s) {
	string op = getOp(s);
	if (op == "") throw logic_error("no relational operator in expression");
	vector<string>svec = s_split(s, op);

}

Condition::Condition(string s) {




//	int state = 0;
//	int pLev = 0;
//	int pos = 0;
//	string varName = "";
//	string oper = "";
//	string value = "";
//	for (auto c : s) {
//		cout << "pos=" << pos << ", state=" << state << ", char=" << c << ", plev=" << pLev << endl;
//		switch (state) {
//		case 0: {
//			if (c == '(') {
//				pLev++;
//			} else if ( c == ')') {
//				throw logic_error("unmatched right parenthesis found at position " + to_string(pos));
//			} else if (varOK(c, true)) {
//				varName += c;
//				state = 1;
//			} else if (c != ' ') {
//				throw logic_error("invalid character in variable name at position " + to_string(pos));
//			}
//			break;
//		}
//		case 1: { // allowed varname or < > = ! <sp>
//			if (c == ' ') {
//				state = 2;
//			} else if (isOper(c)) {
//				oper += c;
//				state = 3;
//			} else if (varOK(c)) {
//				varName += c;
//			} else throw logic_error("invalid character encountered at position " + to_string(pos));
//			break;
//		}
//		case 2: {
//			if (c == ' ') break;
//			if (isOper(c)) {oper += c; state = 3; break;}
//			throw logic_error("operator expected at position " + to_string(pos));
//			break;
//		}
//		case 3:
//			if (isOper(c)) {oper += c; break;}
//			if (c == ' ') {state = 4; break;}
//			if (valOK(c)) {value += c; state = 5; break;}
//			throw logic_error("invalid value");
//			break;
//		}
//		pos++;
//	}
}

vector<string>Condition::getVars() const {
	return vector<string> {"a"};
}

bool Condition::evaluate(vector<int> valvec) const {
	return false;
}

Condition::~Condition() {
	// TODO Auto-generated destructor stub
}

