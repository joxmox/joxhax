/*
 * Exchange.cpp
 *
 *  Created on: Nov 3, 2015
 *      Author: sebis
 */


#include <string>
#include <iostream>
#include "Currency.hpp"
#include "Money.hpp"

using namespace std;

int main() {
	Currency sek {"SEK"};
	Currency usd {"USD", 8.4942};
	Currency eur {"EUR", 9.7320};
	Currency dkk {"DKK", 1.2558};
	Money m1 {1000, usd};
	Money m2 {250, eur};
	cout << m1 << endl;
	cout << m2 << endl;
	Money m3 = m2.convert(usd);
	cout << m3 << endl;
	cout << m2 << " = " << m2.convert(usd) << endl;
//    cout << m2.convert(usd) << endl;
}

