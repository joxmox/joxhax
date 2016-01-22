/*
 * Condition.hpp
 *
 *  Created on: Jan 7, 2016
 *      Author: sebis
 */

#ifndef SRC_CONDITION_HPP_
#define SRC_CONDITION_HPP_

#include <string>
#include <vector>
#include <functional>

class CondEle {
	int num;
	int cnt = 0;
	std::function<int(int, int)> cond;
	int value;
	CondEle* next = nullptr;
public:
//	CondEle(std::function<int(int, int)> c, int v, bool h = false) : cond(c), value(v), head(h) {}
//	CondEle(bool h): head(h), top(this) {}
	CondEle* add(std::function<int(int, int)>, int);
	CondEle(const std::string&);
};

class Condition {
	std::vector<CondEle> condList;
	std::vector<std::string> vars;
	std::vector<int> values;
public:
	Condition() = delete;
	Condition(std::string>);
	std::vector<std::string>getVars () const;
	bool evaluate (std::vector<int>) const;
	virtual ~Condition();
};

#endif /* SRC_CONDITION_HPP_ */
