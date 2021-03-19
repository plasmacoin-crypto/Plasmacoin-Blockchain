//
// FILENAME: block.hpp | Plasmacoin Cryptocurrency
// DESCRIPTION: An item that holds data about a transaction
// CREATED: 2021-01-17 @ 9:37 PM
// COPYRIGHT: Copyright (c) 2021 by Ryan Smith <rysmith2113@gmail.com>
//

#ifndef BLOCK_HPP
#define BLOCK_HPP

#include <ctime>
#include <string>
#include <tuple>

#include "transaction.hpp"

using std::string;
using std::tuple;

class Block {
public:
	// The block contents
	int m_Index, m_Nonce = 0;
	string m_Hash, *m_PrevHash;

	// A sender and reciever signature used for verifying the transaction
	// on the block
	string m_SSignature, m_RSignature;

	Transaction* m_Transaction;
	char* m_Timestamp;

	Block(int index, string* prevHash, Transaction* transaction);

	bool Validate(string latestHash, const int& DIFFICULTY);
};

Block::Block(int index, string* prevHash, Transaction* transaction):
	m_Index(index),
	m_PrevHash(prevHash),
	m_Transaction(transaction)
{
	// Get a timestamp for the block
	time_t now = time(0);
	m_Timestamp = ctime(&now);
}

// Make sure the block is valid
bool Block::Validate(string latestHash, const int& DIFFICULTY) {
	return (
		(m_PrevHash != nullptr) &&	// Check if the previous hash exists on the block
		(latestHash == *m_PrevHash) &&	// Check if the previous hash is valid
		(m_Hash.find(string(DIFFICULTY, '0')) != string::npos)	// Check if the block hash is valid
	);
}

#endif // BLOCK_HPP