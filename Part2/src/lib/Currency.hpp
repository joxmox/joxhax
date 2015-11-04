/*
 * Currency.hpp
 *
 *  Created on: Nov 3, 2015
 *      Author: sebis
 */

#ifndef CURRENCY_HPP_
#define CURRENCY_HPP_

#include <string>

using namespace std;

class Currency {
	string name;
	double rate;
public:
	Currency(const string& n, double r): name(n), rate(r) {}
	Currency(const string& n): name(n), rate(1.0) {}
	string const getName() {return name;}
	double getRate() {return rate;}
};


#endif /* CURRENCY_HPP_ */
