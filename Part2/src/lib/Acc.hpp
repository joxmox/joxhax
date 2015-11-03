#include <string>
#include <iostream>
#include <sstream>

using namespace std;

class Account {
    string accno;
    int balance;
    float rate;
    int* ref;
    static int instCount;
public:
    Account(const string& an): accno(an) {
        cout << "[Account::Account{1par}] create(" << ++instCount << "): " << this << endl;
        balance = 0;
        rate = 0.0;
        ref = nullptr;
    }
    Account(const string& an, int b, float r, int rf): accno(an), balance(b), rate(r){
        cout << "[Account::Account{3par}] create(" << ++instCount << "): " << this << endl;
        ref = new int {rf};
    }
    Account(const Account& a) {
    	this->accno = a.accno;
    	this->balance = a.balance;
    	this->rate = a.rate;
    	if (a.ref != nullptr) {
    		this->ref = new int {*a.ref};
    	} else {
    		this->ref = nullptr;
    	}
    	cout << "[Account::Account{copy}] create(" << ++instCount << "): " << this << endl;
    }

    Account(Account&& a) {
    	this->accno = a.accno;
    	this->balance = a.balance;
    	this->rate = a.rate;
    	this->ref = a.ref;
    	cout << "[Account::Account{move}] create(" << ++instCount << "): " << this << endl;
    }

    Account(int a) {
    	this->accno = to_string(a) + "-" + to_string(a) + "00";
    	this->balance = 0;
    	this->rate = 2.0;
    	this->ref = nullptr;
    	cout << "[Account::Account{cvt}] create(" << ++instCount << "): " << this << endl;
    }

    ~Account() {
      cout << "[Account::~Account] destroy(" << instCount-- << "): " << this << endl;
    }
    void setBal(int b) {
      balance = b;
      cout << "[Account::setBal] " << this << endl;
    }
    void addBal(int b) {
      balance += b;
      cout << "[Account::addBal] " << this << endl;
    }
    void setRate(float r) {
      rate = r;
      cout << "[Account::setRate] " << this << endl;
    }
    int getBal() const {
    	return balance;
    }

    string toString() {
        stringstream ss;
        ss << this;
        return "Accno: " + accno + ", " +
                                  "Balance: " + to_string(balance) + ", " +
                                  "Rate: " + to_string(rate) + ", " +
                                  "(" + ss.str() + ")";
    }

    static void resetInstCount() {
    	instCount = 0;
    }

    static int getInstCount() {
    	return instCount;
    }

};


