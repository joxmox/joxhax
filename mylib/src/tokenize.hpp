/*
 * tokenize.hpp
 *
 *  Created on: Jan 28, 2016
 *      Author: joxmox
 */

#ifndef SRC_RPN_TOKENIZE_HPP_
#define SRC_RPN_TOKENIZE_HPP_

#include <string>
#include <vector>

namespace jox {

using namespace std;

vector<string> tokenize(const string&);
vector<string> infix2postfix(vector<string>&);
bool isOperator(const string&);
int operatorCmp(const string&, const string&);

}



#endif /* SRC_RPN_TOKENIZE_HPP_ */
