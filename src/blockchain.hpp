//
// FILENAME: blockchain.hpp | Plasmacoin Cryptocurrency
// DESCRIPTION: The main Plasmacoin blockchain functionality
// CREATED: 2020-01-18 @ 8:51 PM
// COPYRIGHT: Copyright (c) 2021 by Ryan Smith <rysmith2113@gmail.com>
//

#ifndef BLOCKCHAIN_HPP
#define BLOCKCHAIN_HPP

#include <set>
#include <queue>

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
};

Blockchain::Blockchain() {
	Add(&Block(0, "", nullptr));  // Add a Genesis block
}

int Blockchain::Add(Block* block) {
	m_Chain.insert(block);
}

set<Block*> Blockchain::Get() const {
	return m_Chain;
}

int Blockchain::Mine() {
	// Get the block that the node will be mining
	Block block = *m_Unconfirmed.front();
	m_Unconfirmed.pop();


}

#endif // BLOCKCHAIN_HPP
