//
// FILENAME: mining.hpp | Plasmacoin Cryptocurrency
// DESCRIPTION: Mining/PoW processes for the blockchain
// CREATED: 2022-06-17 @ 11:48 AM
// COPYRIGHT: Copyright (c) 2022 by Ryan Smith <rysmith2113@gmail.com>
//

#ifndef MINING_HPP
#define MINING_HPP

#include <string>
#include <utility>

#include "blockchain.hpp"
#include "transaction.hpp"
#include "utility.hpp"
#include "transmitter.hpp"

namespace mining {
	Block makeBlock(Blockchain* blockchainCopy, const vector<Transaction*>& transactions, int64_t difficulty);
	std::pair<bool, uint8_t> mine(Blockchain* blockchainCopy, Block& block);
	bool validate(Blockchain* blockchainCopy, Block* block);
	void transmitBlock(Block* block, const std::vector<string>& hosts);
}

#endif // MINING_HPP