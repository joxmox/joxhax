/*
 * testExpression.cpp
 *
 *  Created on: Jan 28, 2016
 *      Author: joxmox
 */

#include <iostream>
#include "Expression.hpp"

using namespace std;

int main()  {
	jox::InfixExpress myExp {"x != y"};
	jox::varMap vm;
	vm["x"] = "4.5";
	vm["y"] = "-1.5";
	vm["z"] = "2";
	cout << myExp.evaluateString(vm) << endl;
}


