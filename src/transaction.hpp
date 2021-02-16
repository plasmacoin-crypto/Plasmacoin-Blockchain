//
// FILENAME: transaction.hpp | Plasmacoin Cryptocurrency
// DESCRIPTION: A transaction between nodes
// CREATED: 2021-01-17 @ 10:01 PM
// COPYRIGHT: Copyright (c) 2021 by Ryan Smith <rysmith2113@gmail.com>
//

#ifndef TRANSACTION_HPP
#define TRANSACTION_HPP

#include <string>
#include <algorithm>

using std::string;

class Node;

class Transaction {
public:
	const Node& m_Sender;
	Node& m_Recipient;

	float m_Amount;
	string m_Content;

	Transaction(const Node& sender, Node& recipient, string content, float amount, string condensed);
	string Update(int nonce);

	// A condensed version of the transaction in the form:
	// <SENDER>: <AMOUNT> Plasmacoins to <RECIPIENT>; <NONCE>
	string m_Condensed;
};

Transaction::Transaction(const Node& sender, Node& recipient, string content, float amount, string condensed):
	m_Sender(sender),
	m_Recipient(recipient),
	m_Amount(amount),
	m_Content(content),
	m_Condensed(condensed)
{}

// Update the transaction to have the latest nonce value
string Transaction::Update(int nonce) {
	auto start = std::find(m_Condensed.begin(), m_Condensed.end(), ';'); // The nonce is after a semicolon
	m_Condensed.erase(start, m_Condensed.end());

	m_Condensed += "; " + std::to_string(nonce);
	return m_Condensed;
}

#endif // TRANSACTION_HPP
