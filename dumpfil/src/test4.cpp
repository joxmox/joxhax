/*
 * test4.cpp
 *
 *  Created on: Jan 24, 2016
 *      Author: joxmox
 */

#include <iostream>
#include <string>
#include <map>
#include <stack>

using namespace std;

enum polType {pund, sval, nval, vnam, oper};
enum operType {ound, pleft, oplu, omul, ceq, cgt, land};
static map<string, operType> operName {
	{"+", oplu},
	{"*", omul},
	{"=", ceq},
	{">", cgt},
	{"and", land},
};
static map<operType, int> operValue {
	{ound, -10},
	{pleft, 0},
	{oplu, 10},
	{omul, 20},
	{cgt, 30},
	{ceq, 40},
	{land, 50},
};

class polEle {
public:
private:
	polType type = pund;
	operType oper = ound;
	int prec = 0;
	string value = "";
	polEle* next = nullptr;
public:
	polEle(operType);
	polEle(polType, const string&);
	polEle() = delete;
	int getPrec() {return prec;}
	operType getOper() {return oper;}
};

polEle::polEle(operType op) {
	type = polType::oper;
	oper = op;
	prec = operValue[oper];
}

polEle::polEle(polType pt, const string& s) {
	type = pt;
	value = s;
}

class polExp {
	void doToken(const string&);
	void doLeft();
	void doRight();
	stack<polEle*> resultStack;
	stack<polEle*> operStack;
public:
	enum types {undef, head, var, sval, nval, oper};
	enum opers {plus, minus, eq, gt};
	polExp(const string&);
	bool eval(map<string, string>&, map<string, char>&);
};

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

bool containsDot(const string& s) {
	for (auto c : s) {
		if (c == '.') return true;
	}
	return false;
}

bool okVariable(const string& s) {
	return true;
}


void polExp::doToken(const string& s) {
	polEle* newEle;
	bool oflag = false;
	if (isQuoted(s)) {
		newEle = new polEle {polType::sval, s};
	}

	else if (isNumeric(s)) {
		newEle = new polEle {polType::nval, s};
	}

	else if (operName.find(s) != operName.end()) {
		newEle = new polEle {operName[s]};
		while (operStack.top()->getPrec() >= newEle->getPrec()) {
			resultStack.push(operStack.top());
			operStack.pop();
		}
		oflag = true;
	}

	else if (okVariable(s)) {
		polEle* newEle = new polEle {vnam, s};
	}

	if (oflag) {
		operStack.push(newEle);
	} else {
		resultStack.push(newEle);
	}
}

void polExp::doLeft() {
	operStack.push(new polEle{pleft});
}

void polExp::doRight() {
	polEle* polTmp = operStack.top();
	operStack.pop();
	while (polTmp->getOper() != pleft) {
		resultStack.push(polTmp);
		polTmp = operStack.top();
		operStack.pop();
	}
}


polExp::polExp(const string& str) {
	string tok {""};
	for (auto c : str + " ") {
		switch(c) {
		case ' ': doToken(tok); break;
		case '(' : doLeft(); break;
		case ')' : doRight(); break;
		default: tok += c;
		}
	}
}

bool polExp::eval(map<string, string>& vm, map<string, char>& tm) {
	cout << "oper stack size: " << operStack.size() << endl;
	return true;
}


int main() {
	polExp exp {"x > 5"};
	map<string, string> vmap {{"x", "3"}};
	map<string, char> tmap {{"x", 'i'}};
	cout << exp.eval(vmap, tmap);
}




