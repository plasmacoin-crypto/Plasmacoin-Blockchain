//
// FILENAME: blockchain.cpp | Plasmacoin Cryptocurrency
// DESCRIPTION: The source file for blockchain.hpp
// CREATED: 2021-03-34 @ 11:34 PM
// COPYRIGHT: Copyright (c) 2021 by Ryan Smith <rysmith2113@gmail.com>
//

#include "blockchain.hpp"

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
		m_Chain.insert(block);
	}

	return 0;
}

// Add an unconfirmed block to the ledger
int Blockchain::AddToLedger(Block* block) {
	if (block == nullptr) {
		return -1;
	}
	else {
		m_Unconfirmed.push(block);
	}

	return 0;
}

// Get the blockchain
set<Block*> Blockchain::Get() const {
	return m_Chain;
}

// Get the block that was most recently added to the blockchain
Block* Blockchain::GetLatest() const {
	return *m_Chain.end();
}

// Mine a block
int Blockchain::Mine() {
	if (!m_Unconfirmed.empty()) {
		// Get the block that the node will be mining
		Block block = *m_Unconfirmed.front();
		m_Unconfirmed.pop();

		Consensus(block);
	}
	else {
		return -1;
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