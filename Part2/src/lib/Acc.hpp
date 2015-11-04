#include <string>
#include <iostream>
#include <sstream>
#include <iomanip>

using namespace std;

class Account {

    string accno;
    int balance;
    float rate;
    static int instCount;

public:

    Account(const string &an, int b, float r): accno(an), balance(b), rate(r) {};

    Account(const string& an): accno(an) {
        balance = 0;
        rate = 0.0;
        instCount++;
    }

    Account(const Account& a) {
    	this->accno = a.accno;
    	this->balance = a.balance;
    	this->rate = a.rate;
    	instCount++;
    }

    Account(int a) {
    	this->accno = to_string(a) + "-" + to_string(a) + "00";
    	this->balance = 0;
    	this->rate = 2.0;
    	instCount++;
    }

    ~Account() {
    	instCount--;
    }

    void setBal(int b) {
      balance = b;
    }
    void addBal(int b) {
      balance += b;
    }
    void setRate(float r) {
      rate = r;
    }
    int getBal() const {
    	return balance;
    }

    static int getInstCount() {
    	return instCount;
    }

    string const toString() {
    	stringstream ss;
    	ss << "Accno: " << accno << ", Balance: $" << balance << ", Rate: " << setprecision(2) << fixed << rate << "%";
    	return ss.str();
    }

    static void resetInstCount() {
    	instCount = 0;
    }

    void operator +=(int a) {this->addBal(a);}


};

bool operator <(Account& a, Account& b) {
	return a.getBal() < b.getBal();
}

bool operator ==(Account& a, Account& b) {
	return a.getBal() == b.getBal();
}

void operator %(Account& a, float r) {
	a.setBal(int(a.getBal() * (1 + r/100)));
}

ostream& operator <<(ostream& os, Account& acc)  {
	os << acc.toString();
	return os;
}



