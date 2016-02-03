/*
 * LdapConn.hpp
 *
 *  Created on: Feb 3, 2016
 *      Author: joxmox
 */

#ifndef SRC_LDAPCONN_HPP_
#define SRC_LDAPCONN_HPP_

#include <string>
#include <vector>
#include <ldap.h>

class LdapConn {
	std::string server;
	int port;
	int proto;
	LDAP* ld;
public:
	LdapConn() = delete;
	LdapConn(const std::string&, int = LDAP_PORT);
	~LdapConn();
	void connect(const std::string& = "", const std::string& = "");
	std::vector<std::string> search(const std::string&, const std::string&);
};

#endif /* SRC_LDAPCONN_HPP_ */
