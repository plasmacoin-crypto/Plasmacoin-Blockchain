//
// FILENAME: transaction.cpp | Plasmacoin Cryptocurrency
// DESCRIPTION: The source file for transaction.hpp
// CREATED: 2021-03-31 @ 11:26 PM
// COPYRIGHT: Copyright (c) 2021 by Ryan Smith <rysmith2113@gmail.com>
//

#include "transaction.hpp"

Transaction::Transaction(const Node* sender, Node* recipient, string content, float amount, string condensed):
	m_Sender(sender),
	m_Recipient(recipient),
	m_Amount(amount),
	m_Content(content),
	m_Condensed(condensed)
{}

// Update the transaction to have the latest nonce value
void Transaction::Update(int nonce) {
	auto semicolon = std::find(m_Condensed.begin(), m_Condensed.end(), ';'); // The nonce is after a semicolon
	const string NEW_VALUE = "; " + std::to_string(nonce);

	m_Condensed.replace(semicolon, m_Condensed.end(), NEW_VALUE); // Replace the old data with the new data
}