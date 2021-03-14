//
// FILENAME: blockchain.hpp | Plasmacoin Cryptocurrency
// DESCRIPTION: The main Plasmacoin blockchain functionality
// CREATED: 2021-01-18 @ 8:51 PM
// COPYRIGHT: Copyright (c) 2021 by Ryan Smith <rysmith2113@gmail.com>
//

#ifndef BLOCKCHAIN_HPP
#define BLOCKCHAIN_HPP

#include <set>
#include <queue>

// This header file groups thre Crypto++ headers to save space
// and also provide them with a descriptive overall name.
#include "cryptopp-sha256-libs.h"

#include "block.hpp"

using std::set;
using std::queue;

class Blockchain {
public:
	Blockchain();

	// Both will return 0 on success
	int Add(Block* block); // Add a confirmed block to the blockchain
	int AddToLedger(Block* block); // Add an unconfirmed block to the ledger

	set<Block*> Get() const;
	Block* GetLatest() const;

	int Mine();
private:
	const int DIFFICULTY = 5;

	set<Block*> m_Chain;
	queue<Block*> m_Unconfirmed; // Blocks waiting to be mined (the ledger)
public:
	bool Consensus(Block& block); // Evaluate Proof-of-Work
private:
	string Hash(Transaction transaction);
};

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
int AddToLedger(Block* block) {
	if (block == nullptr) {
		return -1;
	}
	else {
		m_Unconfirmed.push(block);
	}

	return 0;
}

// Return the blockchain
set<Block*> Blockchain::Get() const {
	return m_Chain;
}

Block* Blockchain::GetLatest() const {
	return m_Chain.back();
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
// returned is if a node was able to complete the hash before another user.
bool Blockchain::Consensus(Block& block) {
	// Get the nonce. If the difficulty is 5, the string representation
	// of the nonce will be "00000".
	string strNonce = string(DIFFICULTY, '0');

	string hash = this->Hash(*block.m_Transaction); // Hash the block

	while (hash.substr(0, strNonce.size()) != strNonce) {
		// Increase the nonce and update the condensed block data
		block.m_Nonce++;
		block.m_Transaction->Update(block.m_Nonce);

		hash = this->Hash(*block.m_Transaction);
	}

	block.m_Hash = hash;

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

#endif // BLOCKCHAIN_HPP
