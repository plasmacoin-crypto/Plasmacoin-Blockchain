//
// FILENAME: transaction.hpp | Plasmacoin Cryptocurrency
// DESCRIPTION: A transaction between nodes
// CREATED: 2021-01-17 @ 10:01 PM
// COPYRIGHT: Copyright (c) 2021 by Ryan Smith <rysmith2113@gmail.com>
//

#ifndef TRANSACTION_HPP
#define TRANSACTION_HPP

#include <string>

using std::string;

class Node;

class Transaction {
public:
	const Node& m_Sender;
	Node& m_Recipient;

	float m_Amount;
	string m_Content;

	Transaction(const Node& sender, Node& recipient, string content, float amount);

	string Condense();
};

Transaction::Transaction(const Node& sender, Node& recipient, string content, float amount):
	m_Sender(sender),
	m_Recipient(recipient),
	m_Amount(amount),
	m_Content(content)
{}

// Condense the transaction data into a form that can be hashed
// by the SHA-256 algorithm.
string Transaction::Condense() {
	
}

#endif // TRANSACTION_HPP
