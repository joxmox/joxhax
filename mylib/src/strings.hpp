#ifndef __STRINGS_HPP__
#define __STRINGS_HPP__

#include <string>
#include <regex>
#include <algorithm>
#include <vector>
#include <cctype>
#include <iostream>

using namespace std;

void s_remove(string& s, const string& p);
void s_replace(string& s, const string& f, const string& t);
void s_decomment(string& s);
void s_compress(string& s);
void s_collapse(string& s);
void s_trim(string& s);
void s_upper(string& s);
void s_lower(string& s);
vector<string> s_split(const string& s, const string& d);
bool s_match(const string& s, const string& p, vector<string>& v);

#endif

