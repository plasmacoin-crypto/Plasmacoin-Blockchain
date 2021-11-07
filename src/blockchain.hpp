//
// FILENAME: blockchain.hpp | Plasmacoin Cryptocurrency
// DESCRIPTION: The main Plasmacoin blockchain functionality
// CREATED: 2021-01-18 @ 8:51 PM
// COPYRIGHT: Copyright (c) 2021 by Ryan Smith <rysmith2113@gmail.com>
//

#ifndef BLOCKCHAIN_HPP
#define BLOCKCHAIN_HPP

#include <vector>
#include <iostream>
#include <thread>
#include <future>
#include <chrono>
#include <functional>
#include <utility>

#include <unistd.h>

#include <QDebug>

// This header file groups three Crypto++ headers to save space
// and also provide them with a descriptive, overall name.
#include "cryptopp-sha256-libs.h"

#include "block.hpp"
#include "merkle-helpers.h"
#include "dat-fs.hpp"

// Include Go code
namespace go {
	#include "goexports.h"
}

using std::vector;
using std::pair;
using std::future;

class Blockchain {
public:
	Blockchain();
	~Blockchain();

	// Both will return 0 on success
	int Add(Block* block); // Add a block with a confirmed transaction to the blockchain
	int AddToLedger(Transaction* transaction); // Add an unconfirmed transaction to the ledger

	vector<Block*> Get() const;
	Block* GetLatest() const;
	inline constexpr size_t Size() const;

private:
	const int DIFFICULTY = 5;

	vector<Block*> m_Chain;
	vector<Transaction*> m_Unconfirmed; // Blocks waiting to be mined (the ledger)

	void Save(Block* block) const;
	void Compress();
	template<typename T> bool IsReady(const future<T>& future);

public:
	pair<bool, uint8_t> Mine(Block& newBlock);
	bool Consensus(Block& block, future<void> exitSignal); // Evaluate Proof-of-Work

	bool Validate();
	bool ValidateHash(const string& hash);

private:
	string Hash(const string& input);
	string Hash(const Transaction& transaction);
	string Hash(const Block& block);
};

template<typename T>
bool Blockchain::IsReady(const future<T>& future) {
	return future.wait_for(std::chrono::seconds(0)) == std::future_status::ready;
}

#endif // BLOCKCHAIN_HPP
