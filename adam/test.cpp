#include <iostream>

using namespace std;

void dbgInit(const std::string s);
void dbg(const std::string s);

#define kaka(x) apa(x)
#define debInit() dbgInit(__FUNCTION__);
#define deb(x) dbgInit(x);

void apa(int a) {
	cout << a*2 << endl;
}

int main() {
	kaka(2);
}
