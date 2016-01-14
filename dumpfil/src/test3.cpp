#include <iostream>
#include <functional>
#include <vector>
#include <exception>
#include <typeinfo>

using namespace std;

class condBlock {
  int num;
  int cnt = 0;
  function<int(int, int)> cond;
  int value;
  bool head = false;
  condBlock *top = nullptr;
  vector<condBlock*> next;
  vector<int> arr;
  bool dig();
public:
  condBlock(function<int(int, int)> c, int v, bool h = false) : cond(c), value(v), head(h) {}
  condBlock(bool h): head(h), top(this) {}
  bool calc(vector<int>&);
  condBlock* add(function<int(int, int)>, int);
};

condBlock* condBlock::add(function<int(int, int)> c, int v) {
  condBlock* cb = new condBlock{c, v};
  cb->num = top->cnt++;
  cb->top = top;
  next.push_back(cb);
  return cb;
}

bool condBlock::calc(vector<int>& iv) {
  if (!this->head) throw logic_error("Condition evaluation must start at head");
  arr = iv;
  bool result = false;
  if (next.size() == 0) return true;
  for (auto a : next) {
    if (a->dig()) result = true;
  }  int num;
  int cnt = 0;
  function<int(int, int)> cond;
  int value;
  bool head = false;
  condBlock *top = nullptr;
  vector<condBlock*> next;
  vector<int> arr;
  bool dig();

  return result;
}

bool condBlock::dig() {
  bool result = cond(top->arr[num], value);
  cout << num << ": ";
  cout << top->arr[num] << " ";
  if (cond(1,1)) cout << " = ";
  if (cond(1,2)) cout << " < ";
  if (cond(2,1)) cout << " > ";
  cout << value;
  cout << " >>> " << result << endl;
  if (!result) return false;
  if (next.size() == 0) return true;
  result = false;
  for (auto a : next) {
    if (a->dig()) result = true;
  }
  return result;
}
  

int main() {
  condBlock* c1 = new condBlock {true};
  condBlock* c2 = c1->add(greater<int>(), 1);
  condBlock* c3 = c1->add(less<int>(), 9);
  condBlock* c4 = c2->add(equal_to<int>(), 7);
  vector<int> v1 {5, 6, 7};
  cout << c1->calc(v1) << endl;
  vector<int> v2 {1, 9, 1};
  cout << c1->calc(v2) << endl;

}
