/*
 * rpnExp.hpp
 *
 *  Created on: Jan 25, 2016
 *      Author: joxmox
 */

#ifndef SRC_RPNEXP_HPP_
#define SRC_RPNEXP_HPP_

#include <string>
#include <vector>

using namespace std;

enum rpnType {pund, sval, nval, vnam, oper};
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



class rpnEle {
public:
private:
	string txt = "";
	rpnType type = pund;
	operType oper = ound;
	int prec = 0;
	string value = "";
	rpnEle* next = nullptr;
public:
	rpnEle() = delete;
	rpnEle(const string& t, operType ot): type(rpnType::oper), oper(ot), txt(t), prec(operValue[ot]) {}
	rpnEle(const string& t, rpnType pt, const string& s): type(pt), value(s), txt(t) {}
	int getPrec() {return prec;}
	rpnType getType() {return type;}
	operType getOper() {return oper;}
	string getValue() {return value;}
	string getTxt() {return txt;}
};

class rpnStack : public vector<rpnEle*> {
	string name;
public:
	rpnStack(const string& n): name(n) {}
	void push(rpnEle*);
	rpnEle* pop();
	rpnEle* peek();
	void dump();
	int getSize() {return this->size();}
};

class rpnExp {
	void doToken(const string&);
	void doLeft();
	void doRight();
	rpnStack resultStack {"result"};
	rpnStack operStack {"operator"};
public:
	rpnExp(const string&);
	int eval(map<string, string>&);
	void dump();
};



#endif /* SRC_RPNEXP_HPP_ */
