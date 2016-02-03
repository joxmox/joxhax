/*
 * ldaptest.cpp
 *
 *  Created on: Feb 3, 2016
 *      Author: joxmox
 */

#define LDAP_DEPRECATED 1
#include <ldap.h>
#include <iostream>

/* Specify the search criteria here. */

#define MY_HOSTNAME "localhost"
#define MY_PORTNUMBER 389
#define BASEDN "dc=seb,dc=net"
#define SCOPE LDAP_SCOPE_SUBTREE
//#define FILTER "(&(cn=*)(memberUid=s49830))"
#define FILTER "(sn=Tillas)"
//char *attrs[] = {"cp", NULL};
const char MY_URL[] {"ldap://localhost"};
const int MY_VERSION {LDAP_VERSION3};

using namespace std;


int main( int argc, char **argv ) {

    LDAP* ld;
    int sts;

    LDAPMessage *result, *e;
    char *dn;

    int version, rc;

    cout << "Connecting to URL " << MY_URL << " ...";
//    sts = ldap_initialize(&ld, MY_URL);
    ld = ldap_init(MY_HOSTNAME, MY_PORTNUMBER);
    if (ld == nullptr) {
        cout << "not ok" << endl;
        return -1;
    }
    cout << "OK!" << endl;

    cout << "Setting protocol version ...";
    sts = ldap_set_option(ld, LDAP_OPT_PROTOCOL_VERSION,  &MY_VERSION);
    if (sts != LDAP_SUCCESS) {
        cout << "not ok" << endl;
        cout << ldap_err2string(sts) << endl;
        return -1;
    }
    cout << "OK!" << endl;


    cout << "Binding ...";
//    sts = ldap_sasl_bind_s(ld, "dc=test,dc=com,ou=users,cn=s49830", nullptr, nullptr, nullptr, nullptr, nullptr);
    sts = ldap_simple_bind_s(ld, nullptr, nullptr);
    if (sts != LDAP_SUCCESS) {
        cout << "not ok" << endl;
        cout << ldap_err2string(sts) << endl;
        return -1;
    }
    cout << "OK!" << endl;

    cout << "Searching ...";
    sts = ldap_search_ext_s( ld, BASEDN, SCOPE, FILTER, NULL, 0, NULL, NULL, NULL, 0, &result );
    if (sts != LDAP_SUCCESS) {
        cout << "not ok" << endl;
        cout << ldap_err2string(sts) << endl;
        return -1;
    }
    cout << "OK!" << endl;

    return 0;
}



