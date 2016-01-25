/*
 * rpnExp.cpp
 *
 *  Created on: Jan 25, 2016
 *      Author: joxmox
 */

#include <string>
#include <iostream>
#include <vector>
#include <map>

#include "strings.hpp"
#include "rpnExp.hpp"

using namespace std;

// general functions
bool isQuoted(const string& s) {
	if (s.size() < 2) return false;
	if (s[0] != '"') return false;
	if (s[s.size() - 1] != '"') return false;
	return true;
}

bool isNumeric(const string& s) {
	for (auto c : s) {
		if (((c < '0') or (c > '9')) and (c != '.')) return false;
	}
	return true;
}


bool okVariable(const string& s) {
	return true;
}


// RpnStack

rpnEle* rpnStack::pop() {
	int siz = this->size();
	if (siz < 1) throw logic_error("stack " + name + " is empty - cannot pop");
	rpnEle* result = this->back();
	this->pop_back();
	return result;
}

void rpnStack::push(rpnEle* pe) {
	cout << "pushing to stack " << name << endl;
	this->push_back(pe);
}

rpnEle* rpnStack::peek() {
	if (this->size() < 1) logic_error("stack " + name + " is empty - cannot peek");
	return this->back();
}

void rpnStack::dump() {
	cout << "Stack: " << name << endl;
	for (int i=0; i<this->size(); i++) {
		rpnEle* e = this->at(i);
		cout << "" << i << ": " << this->at(i)->getTxt() << endl;
	}
}

// rpnExp (main class)

rpnExp::rpnExp(const string& s) {
	string str {s};
	static string operList = "\\=\\<\\>\\!\\+\\-\\/\\*\\%\\^";
	s_replace(str, "\\s+", " ");
	s_replace(str, "(^\\s|\\s$)", "");
	s_replace(str, "([" + operList + "])([a-zA-Z0-9])", "$1 $2");
	s_replace(str, "([a-zA-Z0-9])([" + operList + "])", "$1 $2");
	vector<string> tokens = s_split(str, " ");
	for (auto tok : tokens) {
		cout << "processing token: " << tok << endl;
		if (tok == "(") {
			operStack.push(new rpnEle {tok, pleft});
		}
		else if (isQuoted(tok)) resultStack.push(new rpnEle {tok, sval, tok});
		else if (isNumeric(tok)) resultStack.push(new rpnEle {tok, nval, tok});
		else if (operName.find(tok) != operName.end()) {
			rpnEle* e = new rpnEle {tok, operName[tok]};
			if (operStack.getSize() > 0) {
				int x = (operStack.peek())->getPrec();
				while (operStack.getSize() > 0 && operStack.peek()->getPrec() >= e->getPrec()) {
					resultStack.push(operStack.pop());
				}
			}
			operStack.push(e);
		}
		else if (tok == ")") {
			rpnEle* e = operStack.pop();
			while (e->getOper() != pleft) {
				resultStack.push(e);
				e = operStack.pop();
			}
		}
		else if (okVariable(tok)) {
			resultStack.push(new rpnEle {tok, vnam, tok});
		}
	}
	while (operStack.getSize() > 0) {
		resultStack.push(operStack.pop());
	}
}


int rpnExp::eval(map<string, string>& vm) {
	vector<int> evalStack;
	cout << "oper stack size: " << operStack.size() << endl;
	for (auto e : resultStack) {
		switch(e->getType()) {
		case sval: throw logic_error("cannot evaluate as integer expressions where strings found");
		case nval: evalStack.push_back(stoi(e->getValue())); break;
		case vnam: evalStack.push_back(stoi(vm[e->getValue()])); break;
		case oper: {
			int a = evalStack.back(); evalStack.pop_back();
			int b = evalStack.back(); evalStack.pop_back();
			int c;
			switch (e->getOper()) {
			case oplu: c = a + b; break;
			case omul: c = a * b; break;
			}
			evalStack.push_back(c);
		}
		}
	}
	return evalStack.back();
}

void rpnExp::dump() {
	operStack.dump();
	resultStack.dump();
}


