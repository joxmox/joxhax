/*
 * rpnExp.cpp
 *
 *  Created on: Jan 25, 2016
 *      Author: joxmox
 */

#include "rpnStuff.hpp"

#include <string>
#include <iostream>
#include <vector>
#include <map>

#include "strings.hpp"

namespace jox {
namespace rpn {

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

Element* Stack::pop() {
	int siz = this->size();
	if (siz < 1) throw logic_error("stack " + name + " is empty - cannot pop");
	Element* result = this->back();
	this->pop_back();
	return result;
}

void Stack::push(Element* pe) {
	cout << "pushing to stack " << name << endl;
	this->push_back(pe);
}

Element* Stack::peek() {
	if (this->size() < 1) logic_error("stack " + name + " is empty - cannot peek");
	return this->back();
}

void Stack::dump() {
	cout << "Stack: " << name << endl;
	for (int i=0; i<this->size(); i++) {
		Element* e = this->at(i);
		cout << "" << i << ": " << this->at(i)->getTxt() << endl;
	}
}

// rpnExp (main class)

Expression::Expression(const string& s) {
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
			operStack.push(new Element {tok, pleft});
		}
		else if (isQuoted(tok)) resultStack.push(new Element {tok, sval, tok});
		else if (isNumeric(tok)) resultStack.push(new Element {tok, nval, tok});
		else if (operName.find(tok) != operName.end()) {
			Element* e = new Element {tok, operName[tok]};
			if (operStack.getSize() > 0) {
				int x = (operStack.peek())->getPrec();
				while (operStack.getSize() > 0 && operStack.peek()->getPrec() >= e->getPrec()) {
					resultStack.push(operStack.pop());
				}
			}
			operStack.push(e);
		}
		else if (tok == ")") {
			Element* e = operStack.pop();
			while (e->getOper() != pleft) {
				resultStack.push(e);
				e = operStack.pop();
			}
		}
		else if (okVariable(tok)) {
			resultStack.push(new Element {tok, vnam, tok});
		}
	}
	while (operStack.getSize() > 0) {
		resultStack.push(operStack.pop());
	}
}


int Expression::evalI(map<string, int>& vm) {
	vector<int> evalStack;
	cout << "oper stack size: " << operStack.size() << endl;
	for (auto e : resultStack) {
		switch(e->getType()) {
		case sval: throw logic_error("cannot evaluate as integer expressions where strings found");
		case nval: evalStack.push_back(stoi(e->getValue())); break;
		case vnam: evalStack.push_back(vm[e->getValue()]); break;
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

bool Expression::evalB(map<string, string>& vm) {
	vector<string> evalStack;
	for (auto e : resultStack) {
		switch (e->getType()) {
		case sval: evalStack.push_back(e->getValue()); break;
		case nval: evalStack.push_back(e->getValue()); break;
		case vnam: evalStack.push_back(vm[e->getValue()]); break;
		case oper:
			string a = evalStack.back();
			bool an = isNumeric(a);
			evalStack.pop_back();
			string b = evalStack.back();
			bool bn = isNumeric(b);
			bool nn = isNumeric(b) && isNumeric(a);
			evalStack.pop_back();
			string c;
			switch (e->getOper()) {
			case oplu:
				if (nn) {
					c = to_string(stod(a) + stod(b));
				} else {
					c = a + b;
				}
			case omul:
				if (nn) {
					c = to_string(stod(a) * stod(b));
				} else {
					throw logic_error("cannot multiply two string values")
				}
			case ceq:
				bool f;
				if (nn)đ

		}
	}

}

void Expression::dump() {
	operStack.dump();
	resultStack.dump();
}

}
}

