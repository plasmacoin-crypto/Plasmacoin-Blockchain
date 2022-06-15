//
// FILENAME: receipt.cpp | Plasmacoin Cryptocurrency
// DESCRIPTION: The source file for receipt.hpp
// CREATED: 2021-02-06 @ 6:55 PM
// COPYRIGHT: Copyright (c) 2022 by Ryan Smith <rysmith2113@gmail.com>
//

#include "receipt.hpp"

Receipt::Receipt(
	const string& senderAddr, const string& recipientAddr, time_t trxnTime, time_t signTime,
	float amount, float fee, const string& hash
):
	m_SenderAddr(senderAddr),
	m_RecipientAddr(recipientAddr),
	m_TransactionTime(trxnTime),
	m_SignTime(signTime),
	m_Amount(amount),
	m_Fee(fee),
	m_Hash(hash)
{}

Receipt::Receipt(
	const string& senderAddr, const string& recipientAddr, time_t trxnTime, time_t signTime,
	float amount, float fee, const Signature& signature, const string& hash
):
	Receipt(senderAddr, recipientAddr, trxnTime, signTime, amount, fee, hash)
{
	m_Signature = signature;
}

Receipt::~Receipt() {}