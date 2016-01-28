/*
 * expression.hpp
 *
 *  Created on: Jan 28, 2016
 *      Author: joxmox
 */

#ifndef SRC_RPN_EXPRESSION_HPP_
#define SRC_RPN_EXPRESSION_HPP_

#include <string>
#include <vector>
#include <map>

namespace jox {

using namespace std;

using varMap = map<string, string>;

class InfixExpress {
	string express;
public:
	InfixExpress() = delete;
	InfixExpress(const string&);
	vector<string>getInfixTokens();
	vector<string>getPostfixTokens();
	bool evaluateBool(varMap&);
	int evaluateInt(varMap&);
	string evaluateString(varMap&);
};

}



#endif /* SRC_RPN_EXPRESSION_HPP_ */
