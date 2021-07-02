//
// FILENAME: blockchain.cpp | Plasmacoin Cryptocurrency
// DESCRIPTION: The source file for blockchain.hpp
// CREATED: 2021-03-34 @ 11:34 PM
// COPYRIGHT: Copyright (c) 2021 by Ryan Smith <rysmith2113@gmail.com>
//

#include "blockchain.hpp"
#include <iostream>

Blockchain::Blockchain() {
	// Add a Genesis block
	Block* genesis = new Block(0, nullptr, nullptr);
	Add(genesis);
}

// Add a confirmed block to the blockchain
int Blockchain::Add(Block* block) {
	if (block == nullptr) {
		return -1;
	}
	else {
		m_Chain.push_back(block);
	}

	return 0;
}

// Add an unconfirmed transaction to the ledger
int Blockchain::AddToLedger(Transaction* transaction) {
	if (transaction == nullptr) {
		return -1;
	}
	else {
		m_Unconfirmed.push(transaction);
	}

	return 0;
}

// Get the blockchain
vector<Block*> Blockchain::Get() const {
	return m_Chain;
}

// Get the block that was most recently added to the blockchain
Block* Blockchain::GetLatest() const {
	return m_Chain.back();
}

// Create a new block with an unconfirmed transaction and run Proof-of-Woork
// on it.
bool Blockchain::Mine(Block& newBlock) {
	std::cout << "Mining" << std::endl;
	if (!m_Unconfirmed.empty()) {
		Block* latest = GetLatest();

		// Create a new block that the node will be mining
		newBlock = Block(latest->m_Index + 1, &latest->m_Hash, m_Unconfirmed.front());
		m_Unconfirmed.pop();

		bool result = Consensus(newBlock); // Run Proof-of-Woork on the block
		Add(&newBlock); // Add it to the blockchain

		std::cout << "Done" << std::endl;
		return result;
	}
	else {
		std::cout << "Done" << std::endl;
		return false;
	}
}

// Complete the Proof-of-Work consensus protocol on a block. Return true
// if the correct hash was successfully found. The only way false would be
// returned is if a node was able to complete the hash before another.
bool Blockchain::Consensus(Block& block) {
	// Get the nonce. If the difficulty is 5, the string representation
	// of the nonce will be "00000".
	string strNonce = string(DIFFICULTY, '0');

	string hash = Hash(*block.m_Transaction); // Hash the block

	while (hash.substr(0, strNonce.size()) != strNonce) {
		// Increase the nonce and update the condensed block data
		block.m_Nonce++;
		block.m_Transaction->Update(block.m_Nonce);

		hash = Hash(*block.m_Transaction);
	}

	block.m_Hash = hash;
	std::cout << hash << std::endl;

	return true;
}

// Make sure the blockchain isn't corrupted
bool Blockchain::Validate() {
	string hash;

	for (auto block: m_Chain) {
		hash = Hash(*block->m_Transaction); // Regenerate the block hash

		// Make sure the block is valid
		if (!block->Validate(hash, DIFFICULTY)) {
			return false;
		}
	}

	return true;
}

// Use Crypto++ to hash the transaction data
string Blockchain::Hash(Transaction transaction) {
	CryptoPP::SHA256 hash;
	string digest; // The result
	string message = transaction.m_Condensed;

	// Use the library
	//
	// No objects have to be freed because of Crypto++'s pipelining
	// functionality
	//
	CryptoPP::StringSource ssource(message, true,
		new CryptoPP::HashFilter(hash,
			new CryptoPP::HexEncoder(
				new CryptoPP::StringSink(digest)
			)
		)
	);

	return digest;
}

// Use Crypto++ to hash a string
string Blockchain::Hash(string input) {
	CryptoPP::SHA256 hash;
	string digest; // The result

	// Use the library
	//
	// No objects have to be freed because of Crypto++'s pipelining
	// functionality
	//
	CryptoPP::StringSource ssource(input, true,
		new CryptoPP::HashFilter(hash,
			new CryptoPP::HexEncoder(
				new CryptoPP::StringSink(digest)
			)
		)
	);

	return digest;
}