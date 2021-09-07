//
// FILENAME: block.cpp | Plasmacoin Cryptocurrency
// DESCRIPTION: The source file for block.hpp
// CREATED: 2021-03-31 @ 11:33 PM
// COPYRIGHT: Copyright (c) 2021 by Ryan Smith <rysmith2113@gmail.com>
//

#include "block.hpp"

Block::Block(int index, string* prevHash, vector<Transaction*> transactions):
	m_Index(index),
	m_PrevHash(prevHash),
	m_Transactions(transactions)
{
	// Get a timestamp for the block
	time_t now = time(0);
	m_Timestamp = ctime(&now);
}

// Make sure the block is valid
bool Block::Validate(const string& hash, const string& prevHash, const int& DIFFICULTY) {
	return (
		m_PrevHash != nullptr &&							// Check if the previous hash exists on the block
		ValidateHash(*m_PrevHash, prevHash, DIFFICULTY) &&	// Check if the previous hash is valid
		ValidateHash(m_Hash, hash, DIFFICULTY)				// Check if the block hash is valid
	);
}

bool Block::ValidateHash(const string& orig, const string& val, const int& DIFFICULTY) {
	// Check the difficulty using the second hash, because the first one could be
	// tampered with. Thanks to short-circuit evaluation, either one will technically
	// at this point.
	return (orig == val) && (val.find(string(DIFFICULTY, '0')) != string::npos);
}