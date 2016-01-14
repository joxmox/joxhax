#include <iostream>
#include <cstring>

using namespace std;

int main() {
  double d = 17.0;
  char s[8];
  double* p = &d;
  memcpy(s, p, 8);
  d = -666;
  cout << d << endl;
  memcpy(p, s, 8);
  cout << d << endl;
}
