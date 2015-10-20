#include <iostream>

using namespace std;

class Kaka {
  int a;
public:
  void printa();
  Kaka();
};

Kaka::Kaka() {
  this->a = 7;
}

void Kaka::printa() {
  cout << this->a * 2 << endl;
}

int main() {
  Kaka k;
  k.printa();
}
