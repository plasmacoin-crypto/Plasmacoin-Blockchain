//
// FILENAME: block.hpp | Plasmacoin Cryptocurrency
// DESCRIPTION: An item that holds data about a transaction
// CREATED: 2020-01-17 @ 9:37 PM
// COPYRIGHT: Copyright (c) 2021 by Ryan Smith <rysmith2113@gmail.com>
//

#ifndef BLOCK_HPP
#define BLOCK_HPP

#include <ctime>
#include <string>
#include <tuple>

#include "transaction.hpp"

using std::string;
using std::tuple;

class Block {
public:
	// The block contents
	int m_Index;
	const int DIFFICULTY = 5;
	string m_PrevHash;
	Transaction* m_Transaction;
	char* m_Timestamp;

	Block(int index, string prevHash, Transaction* transaction);
};

Block::Block(int index, string prevHash, Transaction* transaction):
	m_Index(index),
	m_PrevHash(prevHash),
	m_Transaction(transaction)
{
	// Get a timestamp for the block
	time_t now = time(0);
	m_Timestamp = ctime(&now);
}

#endif // BLOCK_HPP