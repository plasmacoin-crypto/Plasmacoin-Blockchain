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

#include "receipt.hpp"
#include "utility.hpp"
#include "signature.hpp"

class Transaction {
public:
	Transaction(const string& senderAddr, const string& recipientAddr, float amount, float fee, const string& content);
	Transaction(
		const string& senderAddr, const string& recipientAddr, const string& creationTime, const string& signTime, float amount,
		float fee, const string& content, Signature* signature, const string& hash
	);

	Receipt* GetReceipt();

	string m_SenderAddr, m_RecipientAddr;
	string m_CreationTime, m_SignTime;
	float m_Amount, m_Fee;
	string m_Content;

	// A sender and reciever signature used for verifying the transaction
	// on the block
	Signature m_Signature;

	string m_Hash;
};

#endif // TRANSACTION_HPP
