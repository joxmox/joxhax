#include <iostream>
#include <vector>
#define deb(x) cout << __FUNCTION__ << ": " << x << endl;

using namespace std;

void sune() {
  int apa = 17;
  deb("test3");
  deb("apa = " << apa);
}

void dump(vector<int> v) {
  for (auto i: v) {
    cout << i << endl;
  }
}

int main() {
//  cout << "HEJ" << "test1" << endl;
  deb("test2");
  sune();
  vector<int> v;
  for (int i=0; i<10; i++) {
    v.push_back(i*i);
  }
  dump(v);
  int z = 4;
  cout << "4: " << v[4] << endl;
  v.insert(v.begin() + 4, 12);
  dump(v);
}
