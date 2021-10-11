//
// FILENAME: block.cpp | Plasmacoin Cryptocurrency
// DESCRIPTION: The source file for block.hpp
// CREATED: 2021-03-31 @ 11:33 PM
// COPYRIGHT: Copyright (c) 2021 by Ryan Smith <rysmith2113@gmail.com>
//

#include "block.hpp"
#include <iostream>

Block::Block(int index, string prevHash, vector<Transaction*> transactions, bool genesis):
	m_Index(index),
	m_PrevHash(prevHash),
	m_IsGenesis(genesis),
	m_Transactions(transactions)
{
	// Get a timestamp for the block
	time_t now = time(0);
	char* time = ctime(&now);
	m_Timestamp = string(time).substr(0, strlen(time) - 1);

	// The genesis block will have a hash of 0x0
	if (m_IsGenesis) {
		m_Hash = string(64, '0');
	}
}

// Make sure the block is valid
bool Block::Validate(const string& hash, const string& prevHash, const int& DIFFICULTY) {
	if (m_IsGenesis) {
		return true; // Assume all genesis blocks are valid
	}

	return (
		m_PrevHash != "" &&									// Check if the previous hash exists on the block
		ValidateHash(m_PrevHash, prevHash, DIFFICULTY) &&	// Check if the previous hash is valid
		ValidateHash(m_Hash, hash, DIFFICULTY)				// Check if the block hash is valid
	);
}

bool Block::ValidateHash(const string& orig, const string& val, const int& DIFFICULTY) {
	// Check the difficulty using the second hash, because the first one could be
	// tampered with. Thanks to short-circuit evaluation, either one will technically
	// at this point.
	return (orig == val) && (val.find(string(DIFFICULTY, '0')) != string::npos);
}

string Block::Stringify() {
	//
	// All blocks will be output to a .dat file in a similar fashion. This
	// way, they can be easily parsed and converted back into blocks that the
	// blockchain can recognize. Using this method, the blockchain can effectively
	// rebuild itself when you launch the client, so all your data will be available.
	//
	// Block data formatting
	// ---------------------------------
	// ```
	// BEGIN BLOCK
	// index: <index>
	// nonce: <nonce>
	// timestamp: <timestamp>
	// hash: <hash>
	// previous_hash: <previous_hash>
	// transaction: <transaction>	List all of these
	// END BLOCK
	// ```
	//

	string prevHash = m_IsGenesis? "none" : m_PrevHash; // The genesis block has no previous hash
	string result = "";

	result += "BEGIN BLOCK\n"; 			 		   		   			// Header
	result += "index: " 		+ std::to_string(m_Index) + "\n";	// Index
	result += "nonce: " 		+ std::to_string(m_Nonce) + "\n";	// Nonce
	result += "timestamp: " 	+ m_Timestamp 	  		  + "\n"; 	// Timestamp
	result += "hash: " 			+ m_Hash 				  + "\n";	// Hash
	result += "previous_hash: " + prevHash 		  		  + "\n";	// Previous hash

	// The genesis block has no transactions
	if (!m_IsGenesis) {
		for (auto t: m_Transactions) {
			result += "transaction: " + t->m_Condensed + "\n";  	// Transactions
		}
	}

	result += "END BLOCK";								   			// Footer

	return result;
}