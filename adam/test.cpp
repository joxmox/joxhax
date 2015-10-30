#include <iostream>
#include <string>
#include <cstring>

using namespace std;

int main() {
	string kaka  = "abå";
	cout <<  kaka << endl;
	cout << "l: " << kaka.length() << endl;
	cout << "s: " << kaka.size() << endl;
	cout << "w: " << wcslen(kaka.c_str()) << endl;
}
