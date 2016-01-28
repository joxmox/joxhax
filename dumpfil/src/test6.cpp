/*
 * test6.cpp
 *
 *  Created on: Jan 26, 2016
 *      Author: joxmox
 */

#include <string>
#include <vector>
#include <stdexcept>
#include <iostream>

namespace jox {

namespace rpnStuff {

using namespace std;

enum postfixState {isNum, isAlpha, isQuote, isSpace, isDot, isOper, isLpar, isRpar, isError, isEnd};

void doToken(vector<string>& tokArr, string& tok, postfixState& curState, postfixState newState, const string& newTok = "", char c = '\0') {
	if (tok != "") {
		tokArr.push_back(tok);
		tok = "";
	}
	curState = newState;
	if (newTok != "") tokArr.push_back(newTok);
	if (c != '\0') tok += c;
}


vector<string> tokenizeInfix(const string& str) {
	static string opList = "+-*/%^=<>";
	postfixState oldState = isSpace;
	postfixState curState;
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
}
}

using namespace std;

int main() {
	string infix = "3+4*b - 7x *(y-3) + \"apa\" - $s3/7 + 4qq^2 = 1.12 < ax.ax";
	cout << infix << endl;
	vector<string> tokens = jox::rpnStuff::tokenizeInfix(infix);
	for (auto tok : tokens) {
		cout << tok << endl;
	}
}


