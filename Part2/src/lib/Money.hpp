/*
 * Money.hpp
 *
 *  Created on: Nov 3, 2015
 *      Author: sebis
 */

#ifndef MONEY_HPP_
#define MONEY_HPP_

#include <string>
#include <iostream>
#include "Currency.hpp"

using namespace std;

class Money {
	int value;
	Currency& curncy;
public:
	Money(int v, Currency& c): value(v), curncy(c) {}
	Money convert(Currency& c) {
		return Money(int(value * curncy.getRate() / c.getRate()), c);
	}
	string const toString() {return curncy.getName() + " " + to_string(value);}
};

ostream& operator <<(ostream& os, Money& m) {
	return os << m.toString();
}



#endif /* MONEY_HPP_ */
