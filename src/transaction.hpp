//
// FILENAME: transaction.hpp | Plasmacoin Cryptocurrency
// DESCRIPTION: A transaction between nodes
// CREATED: 2020-01-18 @ 10:01 PM
// COPYRIGHT: Copyright (c) 2021 by Ryan Smith <rysmith2113@gmail.com>
//

#ifndef TRANSACTION_HPP
#define TRANSACTION_HPP

#include <string>

using std::string;

class Node;

class Transaction {
public:
	// Node m_Sender, m_Recipient;
	float m_Amount;
	string m_Content;

	Transaction(const Node& sender, Node& recipient, string content, float amount);
};

Transaction::Transaction(const Node& sender, Node& recipient, string content, float amount):
	// m_Sender(sender),
	// m_Recipient(recipient),
	m_Content(content),
	m_Amount(amount)
{}

#endif // TRANSACTION_HPP
