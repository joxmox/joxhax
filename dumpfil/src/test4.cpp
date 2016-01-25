/*
 * test4.cpp
 *
 *  Created on: Jan 24, 2016
 *      Author: joxmox
 */

#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <regex>

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

class polStack : public vector<polEle*> {
	string name;
public:
	polStack(const string& n): name(n) {}
	void push(polEle*);
	polEle* pop();
	polEle* peek();
	void dump();
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
	polStack resultStack;
	polStack operStack;
public:
	enum types {undef, head, var, sval, nval, oper};
	enum opers {plus, minus, eq, gt};
	polExp(const string&);
	bool eval(map<string, string>&, map<string, char>&);
};

vector<string> regSplit(const string& s, const string& d) {
  regex r {d};
  vector<string> v;
  sregex_token_iterator i {s.begin(), s.end(), r, -1};
  sregex_token_iterator e;
  for ( ; i != e; ++i) {
    v.push_back(*i);
  }
  return v;
}

void regReplace(string& s, const string& f, const string& t) {
	regex r1 {f};
	s = regex_replace(s, r1, t);
}

void strTrim(string& s) {
//	static string operList = "\\=\\<\\>\\!\\+\\-\\*\\/\\%\\^";
	static string operList = "\\=\\<\\>\\!\\+\\-\\/\\*\\%\\^";
	regReplace(s, "\\s+", " ");
	regReplace(s, "(^\\s|\\s$)", "");
	regReplace(s, "([" + operList + "])([a-zA-Z0-9])", "$1 $2");
	cout << s << endl;
	regReplace(s, "([a-zA-Z0-9])([" + operList + "])", "$1 $2");
}

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
	cout << "processing token: " << s << endl;
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
		while (operStack.peek()->getPrec() >= newEle->getPrec()) {
			resultStack.push(operStack.pop());
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

	polEle* polTmp = operStack.pop();
	while (polTmp->getOper() != pleft) {
		resultStack.push(polTmp);
		polTmp = operStack.pop();
	}
}

polEle* polStack::pop() {
	int siz = this->size();
	if (siz < 1) throw logic_error("stack " + name + " is empty - cannot pop");
	polEle* result = this->back();
	this->pop_back();
	return result;
}

void polStack::push(polEle* pe) {
	this->push_back(pe);
}

polEle* polStack::peek() {
	return this->back();
}


polExp::polExp(const string& s) {
	string str {s};
	static string operList = "\\=\\<\\>\\!\\+\\-\\/\\*\\%\\^";
	regReplace(str, "\\s+", " ");
	regReplace(str, "(^\\s|\\s$)", "");
	regReplace(str, "([" + operList + "])([a-zA-Z0-9])", "$1 $2");
	regReplace(str, "([a-zA-Z0-9])([" + operList + "])", "$1 $2");
	vector<string> tokens = regSplit(str, " ");
	for (auto tok : tokens) {
		doToken(tok);
	}
}

bool polExp::eval(map<string, string>& vm, map<string, char>& tm) {
	cout << "oper stack size: " << operStack.size() << endl;
	return true;
}


int main() {
	string apa = " x  >5 and k= 3 or  k*3=2 or k/2=1/2";
	cout << "/" << apa << "/" << endl;
	strTrim(apa);
	cout << "/" << apa << "/" << endl;
	polExp exp {"x > 5"};
	map<string, string> vmap {{"x", "3"}};
	map<string, char> tmap {{"x", 'i'}};
	cout << exp.eval(vmap, tmap);
}




