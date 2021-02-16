//
// FILENAME: node.hpp | Plasmacoin Cryptocurrency
// DESCRIPTION: A computer (user) that has access to the blockchain
// CREATED: 2021-01-17 @ 9:54 PM
// COPYRIGHT: Copyright (c) 2021 by Ryan Smith <rysmith2113@gmail.com>
//

#ifndef NODE_HPP
#define NODE_HPP

#include <string>

#include "transaction.hpp"

using std::string;

class Node {
public:
	Node(string name, string username, string passwd, string ip);
	Transaction MakeTransaction(Node& recipient, float amount, string content) const;

	// Some getters
	string GetName() const, GetUsrName() const, GetIP() const;

private:
	string m_Name, m_Username, m_Password, m_IPAddr;
};

Node::Node(string name, string username, string passwd, string ip):
	// User data
	m_Name(name),
	m_Username(username),
	m_Password(passwd),
	m_IPAddr(ip)
{}

Transaction Node::MakeTransaction(Node& recipient, float amount, string content) const {
	// From Transaction::m_Condensed:
	// <SENDER>: <AMOUNT> Plasmacoins to <RECIPIENT>; <NONCE>
	string condensed = recipient.GetUsrName() + ": " + std::to_string(amount) +
					   " Plasmacoins to " + recipient.GetUsrName() + "; 0"; // Use 0 as the starting nonce

	// A new transaction between the current user and another user in the
	// network.
	return Transaction(Node(m_Name, m_Username, m_Password, m_IPAddr),
					   recipient, content, amount, condensed);
}

// Get the user's name
string Node::GetName() const {
	return m_Name;
}

// Get the user's username
string Node::GetUsrName() const {
	return m_Username;
}

// Get the user's global IP address
string Node::GetIP() const {
	return m_IPAddr;
}

#endif // NODE_HPP
