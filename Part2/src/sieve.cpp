/*
 * sieve.cpp
 *
 *  Created on: Oct 14, 2015
 *      Author: sebis
 */

#include <iostream>
#include <vector>
#include <string>
#include <cmath>

using namespace std;

int main(int args, char* argv[]) {
  if (args != 2) {
    cout << "?Incorrect number of arguments" << endl;
    return 1;
  }
  int n = stoi(argv[1]);
  if (n < 2) {
    cout << "?That small value does not make sense" << endl;
  }
  vector<bool> p(n, true);
  int i = 1;
  while (++i < sqrt(n)) {
    if (p[i]) {
      for (int x=2*i; x<n; x+=i) {
        p[x] = false;
      }
    }
  }
  string apa;
  for (int x=2; x<n; x++) {
    if (p[x]) {
      if (apa.length() > 0) {
    	  apa += " ";
    	  cout << " ";
      }
      apa += to_string(x);
      cout << x;
      if (apa.size() > 120) {
    	  apa.clear();
    	  cout << endl;
      }
    }
  }
}
