#include <iostream>
#include <string>
#include <vector>
#include <cassert>
#include "strings.hpp"

using namespace std;

int main() {
  string t1 = "Hej Hopp";
  s_upper(t1);
  assert(t1 == "HEJ HOPP");

  t1 = "kalle!anka";
  s_decomment(t1);
  assert(t1 == "kalle");

  t1 = " apa   kaka  muppet  ";
  s_compress(t1);
  assert(t1 == " apa kaka muppet ");

  s_trim(t1);
  assert(t1 == "apa kaka muppet");

  t1 = "hej||hopp||gummi|snopp";
  vector<string>v1 = s_split(t1, "\\|\\|");
  vector<string>v2 = {"hej", "hopp", "gummi|snopp"};
  assert(v1 == v2);

  cout << "Tests OK" << endl;

  t1 = "kaka=12";
  v1 = s_split(t1, "=");
  v2 = {"kaka", "12"};
  assert(v1 == v2);

  t1 = "balle";
  v1 = s_split(t1, "=");
  v2 = {"balle"};
  assert(v1 == v2);
}

