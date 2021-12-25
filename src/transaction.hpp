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

#include <cryptopp/rsa.h> 		 // Use Crypto++'s RSA functionality
#include <cryptopp/config_int.h> // Use CryptoPP::byte

using CryptoPP::byte;
using CryptoPP::RSA;

class Node;

struct Signature {
	byte* m_signature;
	RSA::PublicKey m_PublicKey;
	size_t m_Length;
}

class Transaction {
public:
	Transaction(const string& senderAddr, const string& recipientAddr, float amount, float fee, const string& content);

	string m_SenderAddr, m_RecipientAddr;
	float m_Amount, m_Fee;
	string m_Content;

	// A sender and reciever signature used for verifying the transaction
	// on the block
	Signature* signature;
};

#endif // TRANSACTION_HPP
