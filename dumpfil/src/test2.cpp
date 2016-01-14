
#include <iostream>
#include <vector>

using namespace std;

class apa {
  bool head;
  int value;
  vector<apa> next;
public:
  apa(): head(true) {}
  apa(int x): head(false), value(x) {}
  apa& add(int x) {apa a(x); next.push_back(a); return *next.begin();}
};

int main() {
  apa head;
  apa kaka = head.add(17);
}
