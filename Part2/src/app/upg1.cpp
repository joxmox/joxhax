#include <vector>
#include <iostream>
#include "Acc.hpp"

Account a0 {"0000-000000"};
int Account::instCount = 0;
vector<Account> accVec;

void check() {
	cout << "Number of active accounts: " << Account::getInstCount() << endl;
	for (int i=0; i<accVec.size(); i++) {
		cout << " [" << i << "]" << accVec[i].toString() << endl;;
	}
}

void apa(const Account& a) {
	Account b1 {"1122-112233"};
	Account b2 {"6666-666666", 9100, 2.2, 92};
	check();
}

Account genAcc(int i) {
	Account a {to_string(i) + "-000000"};
	return a;
}

int main() {
	check();
    accVec.push_back(Account {"1111-222222"});
    accVec.push_back(Account {"1234-567890", 10500, 1.25, 17});
    check();
    a0.addBal(-3200);
    check();
    cout << "now calling apa" << endl;
    apa(accVec[1]);
    cout << "back from apa" << endl;
    check();
    accVec[0].setBal(20000);
    accVec[0].setRate(0.75);
    accVec[1].addBal(7500);
    check();
    accVec.push_back(Account {accVec[0]});
    accVec.push_back(genAcc(4711));
    accVec.push_back(Account {7373});
    check();
}
