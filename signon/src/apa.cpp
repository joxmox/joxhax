/*
 * apa.cpp
 *
 *  Created on: Feb 3, 2016
 *      Author: joxmox
 */

#include <iostream>
#include <stdexcept>
#include "LdapConn.hpp"

using namespace std;

int main() {
	LdapConn ldc {"localhost"};
	try {
		ldc.connect();
		vector<string>result = ldc.search("dc=test,dc=com", "(&(cn=*)(memberUid=s49830))");
		for (auto s : result) {
			cout << s << endl;
		}
	}
	catch (logic_error& e) {
		cout << "Error reported from LDAP server: " << e.what() << endl;
	}
}


