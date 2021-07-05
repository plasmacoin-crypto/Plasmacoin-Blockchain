//
// FILENAME: block.hpp | Plasmacoin Cryptocurrency
// DESCRIPTION: An item that holds data about a transaction
// CREATED: 2021-01-17 @ 9:37 PM
// COPYRIGHT: Copyright (c) 2021 by Ryan Smith <rysmith2113@gmail.com>
//

#ifndef BLOCK_HPP
#define BLOCK_HPP

#include <ctime>
#include <string>
#include <tuple>
#include <deque>

#include "transaction.hpp"

using std::string;
using std::tuple;
using std::deque;

class Block {
public:
	Block(int index, string* prevHash, deque<Transaction*> transactions);
	bool Validate(string latestHash, const int& DIFFICULTY);

	// The block contents
	int m_Index, m_Nonce = 0;
	string m_Hash, *m_PrevHash;

	deque<Transaction*> m_Transactions;
	char* m_Timestamp;
};

#endif // BLOCK_HPP