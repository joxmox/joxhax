#ifndef __STRINGS_HPP__
#define __STRINGS_HPP__

#include <string>
#include <regex>
#include <algorithm>
#include <vector>
#include <cctype>
#include <iostream>

using namespace std;

void s_remove(string& s, const string& p) {
  regex r_remove {p};
  s = regex_replace(s, r_remove, "");
}

void s_replace(string& s, const string& f, const string& t) {
  regex r_replace {f};
  s = regex_replace(s, r_replace, "$1"); 
}

void s_decomment(string& s) {
  static regex r_decomment {"^(.*)\\!.*$"};
  s =  regex_replace(s, r_decomment, "$1");
}

void s_compress(string& s) {
  static regex r_compress {"\\s+"};
  s = regex_replace(s, r_compress, " ");
}

void s_collapse(string& s) {
  static  regex r_collapse {"\\s+"};
  s = regex_replace(s, r_collapse, "");
}

void s_trim(string& s) {
  static regex r_trim {"(,? ?&?$|^ | $)"};
  s = regex_replace(s, r_trim, "");
}

void s_upper(string& s) {
  transform(s.begin(), s.end(), s.begin(), ::toupper);
}

void s_lower(string& s) {
  transform(s.begin(), s.end(), s.begin(), ::tolower);
}

vector<string> s_split(const string& s, const string& d) {
  regex r {d};
  vector<string> v;
  sregex_token_iterator i {s.begin(), s.end(), r, -1};
  sregex_token_iterator e;
  for ( ; i != e; ++i) {
    v.push_back(*i);
  }
  return v;
}

bool s_match(const string& s, const string& p, vector<string>& v) {
  smatch sm;
  bool b;
  return b;
}

#endif

