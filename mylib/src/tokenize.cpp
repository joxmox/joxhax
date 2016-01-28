/*
 * tokenize.cpp
 *
 *  Created on: Jan 28, 2016
 *      Author: joxmox
 */

#include <string>
#include <vector>
#include <map>
#include <iostream>

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
	{"(", 80},
};

enum tokenState {isNum, isAlpha, isQuote, isSpace, isDot, isOper, isLpar, isRpar, isError, isEnd};

bool isOperator(const string& op) {
	if (operatorMap.find(op) == operatorMap.end()) return false;
	else return true;
}

int operatorCmp(const string& opa, const string& opb) {
	cout << "comparing operators " << opa << " : " << opb << endl;

	if (operatorMap.find(opa) == operatorMap.end() || operatorMap.find(opb) == operatorMap.end()) {
		throw logic_error("invalid operator");
	}
	if (operatorMap[opa] == operatorMap[opb]) return 0;
	if (operatorMap[opa] > operatorMap[opb]) return 1;
	return -1;
}


void doToken(vector<string>& tokArr, string& tok, tokenState& curState, tokenState newState, const string& newTok = "", char c = '\0') {
	if (tok != "") {
		tokArr.push_back(tok);
		tok = "";
	}
	curState = newState;
	if (newTok != "") tokArr.push_back(newTok);
	if (c != '\0') tok += c;
}

vector<string> tokenize(const string& str) {
	static string opList = "+-*/%^=<>!";
	tokenState oldState = isSpace;
	tokenState curState;
	string tok = "";
	vector<string> result;
	bool qFlag = false;
	int pos = 0;

	for (auto c : str) {

		pos++;
		if (c >= '0' && c <= '9') curState = isNum;
		else if (c >= 'a' && c<= 'z') curState = isAlpha;
		else if (c == ' ') curState = isSpace;
		else if (c == '"') curState = isQuote;
		else if (c == '.') curState = isDot;
		else if (c == '(') curState = isLpar;
		else if (c == ')') curState = isRpar;
		else if (opList.find(c) != string::npos) curState = isOper;
		else curState = isError;

		if (qFlag) {
			tok += c;
			if (c == '"') {
				qFlag = false;
				doToken(result, tok, curState, isSpace);
			}
		}

		else {

			string dummy;
			switch(curState) {


			case isLpar:
				if (oldState == isNum || oldState == isAlpha) doToken(result, tok, curState, isLpar, "*");
				doToken(result, tok, curState, isSpace, "(");
				break;

			case isRpar:
				doToken(result, tok, curState, isSpace, ")");
				break;

			case isAlpha:
				if (oldState == isNum) doToken(result, tok, curState, isAlpha, "*", c);
				else if (oldState == isOper) doToken(result, tok, curState, isAlpha, "", c);
				else tok += c;
				break;

			case isNum:
				if (oldState == isOper) doToken(result, tok, curState, isNum, "", c);
				else tok += c;
				break;

			case isSpace:
				if (oldState != isSpace) doToken(result, tok, curState, isSpace, "");
				break;

			case isOper:
				if (oldState == isNum or oldState == isAlpha) doToken(result, tok, curState, isOper, "", c);
				else tok += c;
				break;

			case isDot:
				if (oldState == isNum) doToken(result, dummy, curState, isNum, "", c);
				else if (oldState == isAlpha) doToken(result, dummy, curState, isAlpha, "", c);
				else doToken(result, tok, curState, isNum, "", c);
				break;

			case isQuote:
				doToken(result, tok, curState, isSpace, "", c);
				qFlag = true;
				break;

			case isError:
				string msg = "illegal character '" + string(1, c) + "' at position " + to_string(pos) + "\n";
				msg += str + "\n" + string(pos - 1, ' ') + "^";
				throw logic_error(msg);

			}
		}
		oldState = curState;
	}
	doToken(result, tok, curState, isEnd);
	return result;
}


vector<string> infix2postfix(vector<string>& inTok) {
	vector<string> result;
	vector<string> stack;
	for (auto tok : inTok) {
		cout << "result:";
		for (auto q : result) cout << " " << q;
		cout << endl;
		cout << "stack: ";
		for (auto q : stack) cout << " " << q;
		cout << endl;
		cout << "processing token: " << tok << endl;
		if (tok == "(") {
			stack.push_back("(");
		}
		else if (tok == ")") {
			if (stack.size() > 0) {
				string tmp = stack.back();
				stack.pop_back();
				while (tmp != "(" && stack.size() > 0) {
					result.push_back(tmp);
					tmp = stack.back();
					stack.pop_back();
				}
			}
		}
		else if (isOperator(tok)) {
			while (stack.size() > 0 && operatorCmp(stack.back(), tok) <= 0) {
				result.push_back(stack.back());
				stack.pop_back();
			}
			stack.push_back(tok);
		}
		else {
			result.push_back(tok);
		}
	}
	while (stack.size() > 0) {
		result.push_back(stack.back());
		stack.pop_back();
	}
	return result;
}




}


