//
// FILENAME: transaction.cpp | Plasmacoin Cryptocurrency
// DESCRIPTION: The source file for transaction.hpp
// CREATED: 2021-03-31 @ 11:26 PM
// COPYRIGHT: Copyright (c) 2021 by Ryan Smith <rysmith2113@gmail.com>
//

#include "transaction.hpp"

Transaction::Transaction(const string& senderAddr, const string& recipientAddr, float amount, float fee, const string& content):
	m_SenderAddr(senderAddr),
	m_RecipientAddr(recipientAddr),
	m_Amount(amount),
	m_Fee(fee),
	m_Content(content)
{}
