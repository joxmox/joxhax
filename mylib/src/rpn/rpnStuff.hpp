/*
 * rpnExp.hpp
 *
 *  Created on: Jan 25, 2016
 *      Author: joxmox
 */

#ifndef SRC_RPNSTUFF_HPP_
#define SRC_RPNSTUFF_HPP_

#include <string>
#include <vector>
#include <map>

namespace rpn {

using namespace std;

enum rpnType {pund, sval, nval, bval, vnam, oper};
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
	{cgt, 5},
	{ceq, 5},
	{land, 3},
};



class Element {
public:
private:
	string txt = "";
	rpnType type = pund;
	operType oper = ound;
	int prec = 0;
	string value = "";
	string sValue = "";
	double nValue = 0;
	bool bValue = false;
public:
	Element() = delete;
	Element(const string& t, operType ot);
	Element(const string& t, rpnType pt, const string& s);
	int getPrec() {return prec;}
	rpnType getType() {return type;}
	operType getOper() {return oper;}
	string getValue() {return value;}
	string getTxt() {return txt;}
};

class Stack : public vector<Element*> {
	string name;
public:
	Stack(const string& n): name(n) {}
	void push(Element*);
	Element* pop();
	Element* peek();
	void dump();
	int getSize() {return this->size();}
};

class Expression {
	void doToken(const string&);
	void doLeft();
	void doRight();
	Stack resultStack {"result"};
	Stack operStack {"operator"};
public:
	Expression(const string&);
	int evalI(map<string, int>&);
	int evalF(map<string, double&>);
	bool evalB(map<string, string>&);
	void dump();
};

}


#endif /* SRC_RPNSTUFF_HPP_ */
