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

	// A sender and reciever signature used for verifying the transaction
	// on the block
	string m_SSignature, m_RSignature;

	Transaction(const Node& sender, Node& recipient, string content, float amount, string condensed);
	void Update(int nonce);

	// A condensed version of the transaction in the form:
	// <SENDER>: <AMOUNT> Plasmacoins to <RECIPIENT>; <NONCE>
	string m_Condensed;
};

#endif // TRANSACTION_HPP
