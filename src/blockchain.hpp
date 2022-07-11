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
#include <string>
#include <cstdlib>
#include <cmath>

#include <unistd.h>

// This header file groups three Crypto++ headers to save space
// and also provide them with a descriptive, overall name.
#include "cryptopp-sha256-libs.h"

#include <boost/multiprecision/cpp_int.hpp>
#include <boost/lexical_cast.hpp>

#include "block.hpp"
#include "merkle-helpers.h"
#include "dat-fs.hpp"
#include "packet-types.h"
#include "shared-mem.hpp"
#include "parse-json.hpp"
#include "validation.hpp"
#include "hashing.hpp"
#include "utility.hpp"

// Include Go code
namespace go {
	#include "pcnetworkd.h"
}

using std::vector;
using std::pair;
using std::future;
using std::string;

using boost::multiprecision::int256_t;

class Blockchain {
public:
	Blockchain();
	~Blockchain();

	// Both will return 0 on success
	int Add(Block* block); // Add a block with a confirmed transaction to the blockchain
	int AddToLedger(Transaction* transaction); // Add an unconfirmed transaction to the ledger

	vector<Block*> GetBlockchain() const;
	Block* GetLatest() const;
	Block* Get(int index) const;

	size_t Size() const;
	bool Empty() const;

	float GetDifficulty() const;
	int256_t GetTarget() const;

	bool Find(Transaction* transaction);

private:
	// "0x00000fffffffffffffffffffffffffffffffffffffffffffffffffffffffffff"
	const int256_t MAX_TARGET {"0x00fffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff"};
	double m_Difficulty = 1;
	int256_t m_Target = MAX_TARGET / boost::lexical_cast<int256_t>(m_Difficulty);

	const int DIFFICULTY_RECALC = 16;
	const int EXPECTED_MINE_TIME = 300;

	vector<Transaction*> m_Unconfirmed; // Blocks waiting to be mined (the ledger)
	vector<Block*> m_Blockchain;

	void Save(Block* block) const;
	void Compress();

	void CalcDifficulty();
	void SetTarget();

public:
	pair<bool, uint8_t> Mine(Block& newBlock);
	bool Consensus(Block& block); // Evaluate Proof-of-Work
	void StopMining(std::promise<void>&& exitSignal);
};

// Get the number of blocks in the blockchain
inline size_t Blockchain::Size() const {
	return m_Blockchain.size();
}

// Check if the blockchain is empty
inline bool Blockchain::Empty() const {
	return m_Blockchain.empty();
}

#endif // BLOCKCHAIN_HPP
