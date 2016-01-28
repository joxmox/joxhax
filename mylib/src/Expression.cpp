/*
 * expression.cpp
 *
 *  Created on: Jan 28, 2016
 *      Author: joxmox
 */

#include <iostream>

#include "Expression.hpp"
#include "tokenize.hpp"

namespace jox {

using namespace std;

void substitute(string& a, string& b, varMap& vm) {
	if (vm.find(a) != vm.end()) a = vm[a];
	if (b == "") return;
	if (vm.find(b) != vm.end()) b = vm[b];
}

bool isNumeric(string& s) {
	int i = 0;
	for (auto c : s) {
		if (i++ > 0 && c == '-') return false;
		if (((c < '0') || (c > '9')) && (c != '.') && (c != '-')) return false;
	}
	return true;
}

bool isNumeric(string& a, string& b) {
	return isNumeric(a) && isNumeric(b);
}

bool binaryOperator(string& op) {
	return true;
}

void applyOperator(string& op, vector<string>& stack, varMap& vm) {
	if (stack.size() == 0) throw logic_error("operand stack is empty");
	string a = stack.back();
	string b;
	stack.pop_back();
	if (binaryOperator(op)) {
		if (stack.size() == 0) throw logic_error("operand stack is empty");
		b = a;
		a = stack.back();
		stack.pop_back();
	}
	substitute(a, b, vm);
	int numFlag = isNumeric(a, b);
	if (op == "+") {
		if (numFlag) stack.push_back(to_string(stod(a) + stod(b)));
		else stack.push_back(a + b);
	}
	else if (op == "*") {
		if (numFlag) stack.push_back(to_string(stod(a) * stod(b)));
		else throw logic_error("string multiplication not implemented");
	}
	else if (op == "=" || op == "==") {
		if (numFlag) stack.push_back(to_string(stod(a) == stod(b)));
		else stack.push_back(to_string(a == b));
	}
	else if (op == ">") {
		if (numFlag) stack.push_back(to_string(stod(a) > stod(b)));
		else stack.push_back(to_string(a > b));
	}
	else if (op == ">=") {
		if (numFlag) stack.push_back(to_string(stod(a) >= stod(b)));
		else stack.push_back(to_string(a >= b));
	}
	else if (op == "<") {
		if (numFlag) stack.push_back(to_string(stod(a) < stod(b)));
		else stack.push_back(to_string(a < b));
	}
	else if (op == "<=") {
		if (numFlag) stack.push_back(to_string(stod(a) <= stod(b)));
		else stack.push_back(to_string(a <= b));
	}
	else if (op == "!=") {
		if (numFlag) stack.push_back(to_string(stod(a) != stod(b)));
		else stack.push_back(to_string(a != b));
	}
	else {
		if (!numFlag) throw logic_error("cannot apply operator " + op + " on strings");
		else {
			if (op == "-") stack.push_back(to_string(stod(a) - stod(b)));
			else if (op == "/") stack.push_back(to_string(stod(a) / stod(b)));
//			else if (op == "^") stack.push_back(to_string(pow(stod(a),  stod(b))));
//			else if (op == "%") stack.push_back(to_string(stod(a) % stod(b)));
			else if (op == "and" || op == "&&") stack.push_back(to_string(stod(a) && stod(b)));
			else if (op == "or" || op == "||") stack.push_back(to_string(stod(a) || stod(b)));
			else if (op == "not" || op == "!") stack.push_back(to_string(!stod(a)));
			else throw ("unknown operator " + op);
		}
	}
}


// + - * / % ^ and/&& or/|| not/! = > < <= >= !=
// y   z                          y y y y   y  y


string eval(vector<string> postTok, varMap& vm) {
	vector<string> resStack;
	vector<string> opStack;
	for (auto tok : postTok) {
		if (isOperator(tok)) applyOperator(tok, resStack, vm);
		else resStack.push_back(tok);
	}
	return resStack.back();
}

InfixExpress::InfixExpress(const string& express): express(express) {}

vector<string> InfixExpress::getInfixTokens() {
	return tokenize(express);
}

string InfixExpress::evaluateString(varMap& vm) {
	vector<string>inTok = tokenize(express);
	cout << "result from tokenize:" << endl;
	for (auto t : inTok) {
		cout << "  " << t << endl;
	}
	vector<string> postTok = infix2postfix(inTok);
	cout << "result from infix2postfix:" << endl;
	for (auto t : postTok) {
		cout << "  " << t << endl;
	}
	return eval(postTok, vm);
}
}


