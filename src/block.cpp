//
// FILENAME: block.cpp | Plasmacoin Cryptocurrency
// DESCRIPTION: The source file for block.hpp
// CREATED: 2021-03-31 @ 11:33 PM
// COPYRIGHT: Copyright (c) 2021 by Ryan Smith <rysmith2113@gmail.com>
//

#include "block.hpp"
#include <iostream>

Block::Block(
	int index, const string& prevHash, const vector<Transaction*>& transactions,
	int64_t difficulty, bool genesis
):
	m_Index(index),
	m_Difficulty(difficulty),
	m_PrevHash(prevHash),
	m_CreationTime(utility::getUTCTime()),
	m_IsGenesis(genesis),
	m_Transactions(transactions)
{}

Block::Block(
	int index, int nonce, const string& hash, const string& prevHash, const string& minerAddr,
	const string& creationTime, const string& mineTime, const vector<Transaction*>& transactions,
	int64_t difficulty, bool genesis
):
	m_Index(index),
	m_Nonce(nonce),
	m_Difficulty(difficulty),
	m_Hash(hash),
	m_PrevHash(prevHash),
	m_MinerAddr(minerAddr),
	m_CreationTime(creationTime),
	m_MineTime(mineTime),
	m_IsGenesis(genesis),
	m_Transactions(transactions)
{}

Block::Block(int index, const vector<Transaction*>& transactions, int64_t difficulty, bool genesis):
	Block(index, "", transactions, difficulty, genesis)
{}
