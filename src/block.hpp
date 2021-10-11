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
#include <cstring>
#include <tuple>
#include <vector>

#include "transaction.hpp"

using std::string;
using std::tuple;
using std::vector;

class Block {
public:
	Block(int index, string prevHash, vector<Transaction*> transactions, bool genesis = false);

	bool Validate(const string& hash, const string& prevHash, const int& DIFFICULTY);
	bool ValidateHash(const string& orig, const string& val, const int& DIFFICULTY);

	string Stringify();

	// The block contents
	int m_Index, m_Nonce = 0;
	string m_Hash, m_PrevHash, m_Timestamp;
	bool m_IsGenesis;

	vector<Transaction*> m_Transactions;
};

#endif // BLOCK_HPP