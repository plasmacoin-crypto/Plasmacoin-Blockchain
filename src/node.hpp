//
// FILENAME: node.hpp | Plasmacoin Cryptocurrency
// DESCRIPTION: A computer (user) that has access to the blockchain
// CREATED: 2020-01-18 @ 9:54 PM
// COPYRIGHT: Copyright (c) 2021 by Ryan Smith <rysmith2113@gmail.com>
//

#ifndef NODE_HPP
#define NODE_HPP

#include <string>

using std::string;

#include "transaction.hpp"

class Node {
public:
	string m_Name, m_Username;

	Node(string name, string username, string passwd, string ip);
	Transaction MakeTransaction(Node& recipient, float amount, string content) const;

private:
	string m_Password, m_IPAddr;
};

Node::Node(string name, string username, string passwd, string ip):
	// User data
	m_Name(name),
	m_Username(username),
	m_Password(passwd),
	m_IPAddr(ip)
{}

Transaction Node::MakeTransaction(Node& recipient, float amount, string content) const {
	// A new transaction between the current user and another user in the
	// network.
	return Transaction(Node(m_Name, m_Username, m_Password, m_IPAddr), 
					   recipient, content, amount);
}

#endif // NODE_HPP
