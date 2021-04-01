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
	bool Validate();
private:
	string Hash(Transaction transaction);
};

#endif // BLOCKCHAIN_HPP
