/*
 * LdapConn.cpp
 *
 *  Created on: Feb 3, 2016
 *      Author: joxmox
 */

#include <string>
#include <vector>
#include <stdexcept>
#include <iostream>
#define LDAP_DEPRECATED 1
#include <ldap.h>
#include "LdapConn.hpp"

using namespace std;

LdapConn::LdapConn(const string& server, int port): server(server), port(port), proto(LDAP_VERSION3), ld(nullptr) {
}

LdapConn::~LdapConn() {
	ldap_unbind(ld);
}

void LdapConn::connect(const string& user, const string& passwd) {
	ld = ldap_init(server.c_str(), port);
	if (ld == nullptr) throw logic_error("ldap_init returned error!");
	int rc = ldap_set_option(ld, LDAP_OPT_PROTOCOL_VERSION, &proto);
	if (rc != LDAP_SUCCESS) throw logic_error("ldap_set_option: " + string(ldap_err2string(rc)));
    rc = ldap_simple_bind_s(ld, nullptr, nullptr);
    if (rc != LDAP_SUCCESS) throw logic_error("ldap_simple_bind_s: " + string(ldap_err2string(rc)));
}

vector<string> LdapConn::search(const string& base, const string& filter) {
	LDAPMessage *result;
	vector<string> vec;
	char* attr[] = {"cn", nullptr};
	attr[1] = nullptr;
	int rc = ldap_search_ext_s(ld, base.c_str(), LDAP_SCOPE_SUBTREE, filter.c_str(), attr, 1, nullptr, nullptr, nullptr, 0, &result);
	if (rc != LDAP_SUCCESS) throw logic_error("ldap_search_ext_s: " + string(ldap_err2string(rc)));
	char *dn;
	for (auto e = ldap_first_entry(ld, result); e != nullptr; e = ldap_next_entry(ld, e)) {
		if ((dn = ldap_get_dn(ld, e)) != nullptr) {
			vec.push_back(dn);
			ldap_memfree(dn);
		}
	}
	ldap_msgfree(result);
	return vec;
}

