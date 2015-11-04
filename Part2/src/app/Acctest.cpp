#include <vector>
#include <iostream>
#include "Acc.hpp"

int Account::instCount = 0;

void check(vector<Account>& vec) {
	cout << "Number of active accounts: " << Account::getInstCount() << endl;
	for (int i=0; i<vec.size(); i++) {
		cout << " [" << i << "]" << vec[i] << endl;;
	}
}


Account genAcc(int i) {
	Account a {to_string(i) + "-000000"};
	return a;
}

int main() {
	vector<Account> accVec;
	check(accVec);
    accVec.push_back(Account {"1111-222222"});
    accVec.push_back(Account {"1234-567890", 10500, 1.25});
    check(accVec);
    check(accVec);
    accVec[0].setBal(20000);
    accVec[0].setRate(0.75);
    accVec[1].addBal(7500);
    check(accVec);
    accVec.push_back(Account {accVec[0]});
    accVec.push_back(genAcc(4711));
    accVec.push_back(Account {7373});
    check(accVec);
    accVec[2].setRate(1.63);
    accVec[2] += 2220;
    accVec[3] += 9250;
    accVec[3] % 2.5;
    check(accVec);
}
