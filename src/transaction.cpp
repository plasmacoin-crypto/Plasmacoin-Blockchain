//
// FILENAME: transaction.cpp | Plasmacoin Cryptocurrency
// DESCRIPTION: The source file for transaction.hpp
// CREATED: 2021-03-31 @ 11:26 PM
// COPYRIGHT: Copyright (c) 2021 by Ryan Smith <rysmith2113@gmail.com>
//

#include "transaction.hpp"

Transaction::Transaction(const string& senderAddr, const string& recipientAddr, double amount, double fee, const string& content):
	m_SenderAddr(senderAddr),
	m_RecipientAddr(recipientAddr),
	m_Amount(amount),
	m_Fee(fee),
	m_Content(content)
{
	m_CreationTime = utility::getUnixEpoch();
}

Transaction::Transaction(
	const string& senderAddr, const string& recipientAddr, time_t creationTime, time_t signTime, double amount,
	double fee, const string& content, Signature* signature, const string& hash
):
	m_SenderAddr(senderAddr),
	m_RecipientAddr(recipientAddr),
	m_CreationTime(creationTime),
	m_SignTime(signTime),
	m_Amount(amount),
	m_Fee(fee),
	m_Content(content),
	m_Signature(*signature),
	m_Hash(hash)
{}

// Create a receipt for the transaction
Receipt* Transaction::GetReceipt() {
	return new Receipt(
		m_SenderAddr, m_RecipientAddr, m_CreationTime,
		m_SignTime, m_Amount, m_Fee, m_Signature, m_Hash
	);
}
