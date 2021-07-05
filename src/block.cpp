//
// FILENAME: block.cpp | Plasmacoin Cryptocurrency
// DESCRIPTION: The source file for block.hpp
// CREATED: 2021-03-31 @ 11:33 PM
// COPYRIGHT: Copyright (c) 2021 by Ryan Smith <rysmith2113@gmail.com>
//

#include "block.hpp"

Block::Block(int index, string* prevHash, deque<Transaction*> transactions):
	m_Index(index),
	m_PrevHash(prevHash),
	m_Transactions(transactions)
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