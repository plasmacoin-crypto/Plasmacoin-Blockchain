//
// FILENAME: receipt.hpp | Plasmacoin Cryptocurrency
// DESCRIPTION: A transaction receipt
// CREATED: 2021-02-06 @ 6:55 PM
// COPYRIGHT: Copyright (c) 2022 by Ryan Smith <rysmith2113@gmail.com>
//

#ifndef RECEIPT_HPP
#define RECEIPT_HPP

#include <string>

using std::string;

#include "signature.hpp"

class Receipt {
public:
	Receipt(
		const string& senderAddr, const string& recipientAddr, const string& trxnTime, const string& signTime,
		float amount, float fee, const string& hash
	);
	~Receipt();

	string m_SenderAddr, m_RecipientAddr;
	string m_TransactionTime, m_SignTime;
	float m_Amount, m_Fee;

	Signature m_Signature;

	string m_Hash;
};

#endif // RECEIPT_HPP