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

#include "SHA256.h"

#include "block.hpp"

using std::set;
using std::queue;

class Blockchain {
public:
	Blockchain();

	int Add(Block* block); // Will return 0 on success
	set<Block*> Get() const;

	int Mine();
private:
	set<Block*> m_Chain;
	queue<Block*> m_Unconfirmed; // Blocks waiting to be mined

	SHA256 hasher;

	bool Consensus(Block block); // Evaluate Proof-of-Work
	string Hash(Transaction transaction);
};

Blockchain::Blockchain() {
	// Add a Genesis block
	Block* genesis = new Block(0, "", nullptr);
	Add(genesis);
}

int Blockchain::Add(Block* block) {
	m_Chain.insert(block);
	return -1; // tmp
}

set<Block*> Blockchain::Get() const {
	return m_Chain;
}

int Blockchain::Mine() {
	// Get the block that the node will be mining
	Block block = *m_Unconfirmed.front();
	m_Unconfirmed.pop();

	Consensus(block);

	return -1; // tmp
}

bool Blockchain::Consensus(Block block) {
	return false; // tmp
}

string Blockchain::Hash(Transaction transaction) {
	// Use the SHA-256 library to has the transaction data
	hasher.update(transaction.Condense());
	uint8_t* digest = hasher.digest();

	string hash = SHA256::toString(digest);

	delete[] digest; // Free the digest

	return hash;
}

#endif // BLOCKCHAIN_HPP
