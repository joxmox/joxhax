/*
 * accountant.cpp
 *
 *  Created on: Nov 2, 2015
 *      Author: sebis
 */
//Compile: g++ accountant.cpp -std=c++14 -o accountant && ./accountant
#include <iostream>

using namespace std;

enum class AccountType {savings, check, loan, transfer};

struct Account {
  AccountType type;
  int balance;
  float rate;
};

int main() {

  Account a1 = {AccountType::savings, 15392, 1.3};
  Account a2 = {AccountType::check, -7200, 6.5};

  cout << "Account 1: type=" << static_cast<int>(a1.type) << ", balance=" << a1.balance << ", rate=" << a1.rate << "%" << endl;
  cout << "Account 2: type=" << static_cast<int>(a2.type) << ", balance=" << a2.balance << ", rate=" << a2.rate << "%" << endl;

  Account acc[] = {
    {AccountType::savings, 15392, 1.3},
    {AccountType::check, -7200, 6.5},
    {AccountType::transfer, 1195, 12},
    {AccountType::loan, -150000, 3.2},
  };

  cout << "----------" << endl;

  const int N = sizeof(acc) / sizeof(Account);

  for(int i=0; i<N; i++) {
    cout << "Account " << i+1 << ":" << "type=" << static_cast<int>(acc[i].type) << ", balance=" << acc[i].balance << ", rate=" << acc[i].rate << "%" << endl;
  }

}




