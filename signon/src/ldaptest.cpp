/*
 * orig.cpp
 *
 *  Created on: Feb 3, 2016
 *      Author: joxmox
 */

#include <iostream>
#define LDAP_DEPRECATED 1
#include "ldap.h"

/* Specify the search criteria here. */

#define HOSTNAME "localhost"
#define PORTNUMBER 389
#define BASEDN "dc=test,dc=com"
#define SCOPE LDAP_SCOPE_SUBTREE
#define FILTER "(sn=Tillas)"

using namespace std;

int main() {

	/* STEP 1: Get a handle to an LDAP connection and set any session preferences. */

	cout << "Connecting to host " << HOSTNAME << " at port " << PORTNUMBER << "...";
	LDAP *ld = ldap_init(HOSTNAME, PORTNUMBER);
	if (ld == nullptr) {
		cout << "Failed!" << endl;
		return(1);
	}
	cout << "OK!" << endl;

	/* Use the LDAP_OPT_PROTOCOL_VERSION session preference to specify that the client is an LDAPv3 client. */

	cout << "Setting protocol version to " << LDAP_VERSION3 <<  "...";
	int version = LDAP_VERSION3;
	int rc = ldap_set_option( ld, LDAP_OPT_PROTOCOL_VERSION, &version );
	if (rc != LDAP_SUCCESS) {
		cout << "Failed!" << endl;
        cerr << ldap_err2string(rc) << endl;
		return(1);
	}
	cout << "OK!" << endl;

	/* STEP 2: Bind to the server.
In this example, the client binds anonymously to the server
(no DN or credentials are specified). */

	cout << "Binding anonymously...";
	rc = ldap_simple_bind_s(ld, nullptr, nullptr);
	if (rc != LDAP_SUCCESS) {
		cout << "Failed!" << endl;
        cerr << ldap_err2string(rc) << endl;
		return(1);
	}
	cout << "OK!" << endl;


	/* STEP 3: Perform the LDAP operations.
In this example, a simple search operation is performed.
The client iterates through each of the entries returned and
prints out the DN of each entry. */

	cout << "Searching directory from " << BASEDN << " using scope " << SCOPE << " and filter " << FILTER << "...";
	LDAPMessage *result;
	rc = ldap_search_ext_s(ld, BASEDN, SCOPE, FILTER, nullptr, 0, nullptr, nullptr, nullptr, 0, &result);
	if (rc != LDAP_SUCCESS) {
		cout << "Failed!" << endl;
        cerr << ldap_err2string(rc) << endl;
		return(1);
	}
	cout << "OK!" << endl;


	char *dn;
	for (auto e = ldap_first_entry(ld, result); e != nullptr; e = ldap_next_entry(ld, e)) {
		if ((dn = ldap_get_dn(ld, e)) != nullptr) {
			cout << "dn: " << dn << endl;
			ldap_memfree(dn);
		}
	}

	ldap_msgfree(result);

	/* STEP 4: Disconnect from the server. */

	ldap_unbind(ld);

	return(0);

}


