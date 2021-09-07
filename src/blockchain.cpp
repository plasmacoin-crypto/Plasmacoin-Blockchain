//
// FILENAME: blockchain.cpp | Plasmacoin Cryptocurrency
// DESCRIPTION: The source file for blockchain.hpp
// CREATED: 2021-03-34 @ 11:34 PM
// COPYRIGHT: Copyright (c) 2021 by Ryan Smith <rysmith2113@gmail.com>
//

#include "blockchain.hpp"
#include <iostream>

Blockchain::Blockchain() {
	// Add a Genesis block
	Block* genesis = new Block(0, nullptr, {nullptr});
	Add(genesis);
}

// Add a confirmed block to the blockchain
int Blockchain::Add(Block* block) {
	if (block == nullptr) {
		return -1;
	}
	else {
		m_Chain.push_back(block);
	}

	return 0;
}

// Add an unconfirmed transaction to the ledger
int Blockchain::AddToLedger(Transaction* transaction) {
	if (transaction == nullptr) {
		return -1;
	}
	else {
		m_Unconfirmed.push_back(transaction);
	}

	return 0;
}

// Get the blockchain
vector<Block*> Blockchain::Get() const {
	return m_Chain;
}

// Get the block that was most recently added to the blockchain
Block* Blockchain::GetLatest() const {
	return m_Chain.back();
}

size_t Blockchain::Size() const {
	return m_Chain.size();
}

// Create a new block with an unconfirmed transaction and run Proof-of-Woork
// on it.
bool Blockchain::Mine(Block& newBlock) {
	std::cout << "Mining" << std::endl;
	if (!newBlock.m_Transactions.empty()) {
		Block* latest = GetLatest();

		// Create a new block that the node will be mining
		//newBlock = Block(latest->m_Index + 1, &latest->m_Hash, m_Unconfirmed);
		m_Unconfirmed.clear();

		bool result = Consensus(newBlock); // Run Proof-of-Woork on the block
		Add(&newBlock); // Add it to the blockchain

		std::cout << "Done" << std::endl;
		return result;
	}
	else {
		std::cout << "Done" << std::endl;
		return false;
	}
}

// Complete the Proof-of-Work consensus protocol on a block. Return true
// if the correct hash was successfully found. The only way false would be
// returned is if a node was able to complete the hash before another.
bool Blockchain::Consensus(Block& block) {
	// Get the nonce. If the difficulty is 5, the string representation
	// of the nonce will be "00000".
	string strNonce = string(DIFFICULTY, '0');
	string hash;

	do {
		std::cout << "Nonce: " << block.m_Nonce << std::endl;
		hash = Hash(block); // Hash the block

		// Increase the nonce and update the condensed block data
		block.m_Nonce++;
	} while (hash.substr(0, strNonce.size()) != strNonce);

	block.m_Hash = hash;
	std::cout << hash << std::endl;

	return true;
}

// Make sure the blockchain isn't corrupted
bool Blockchain::Validate() {
	string hash;

	for (auto block: m_Chain) {
		hash = Hash(*block); // Regenerate the block hash

		// Make sure the block is valid. One invalid block invalidates the whole
		// chain, because the previous hash fields of all the following blocks will
		// be invalid.
		if (!block->Validate(block->m_Hash, hash, DIFFICULTY)) {
			return false;
		}
	}

	return true;
}

// Use Crypto++ to hash the transaction data
string Blockchain::Hash(const Transaction& transaction) {
	CryptoPP::SHA256 hash;
	string digest; // The result
	string message = transaction.m_Condensed;

	// Use the library
	//
	// No objects have to be freed because of Crypto++'s pipelining
	// functionality
	//
	CryptoPP::StringSource ssource(message, true,
		new CryptoPP::HashFilter(hash,
			new CryptoPP::HexEncoder(
				new CryptoPP::StringSink(digest)
			)
		)
	);

	return digest;
}

// Use Crypto++ to hash a string
string Blockchain::Hash(const string& input) {
	CryptoPP::SHA256 hash;
	string digest; // The result

	// Use the library
	//
	// No objects have to be freed because of Crypto++'s pipelining
	// functionality
	//
	CryptoPP::StringSource ssource(input, true,
		new CryptoPP::HashFilter(hash,
			new CryptoPP::HexEncoder(
				new CryptoPP::StringSink(digest)
			)
		)
	);

	return digest;
}

// Hash a block by constructing a Merkle Tree. Each block hash will be make up of hashes of
// concatenations of hashes until a root node for the tree is generated.
string Blockchain::Hash(const Block& block) {
	// Declare some variables
	int leaves = block.m_Transactions.size(), // Each transaction's hash becomes a leaf
		pads   = mh_pads(leaves),
		height = mh_height(leaves),
		nodes  = mh_nodes(height);

	string* tree[nodes]; // The Merkle Tree
	int index = nodes;	 // The current node that's being accessed

	// Add the hashes of all the transactions on the block to the tree.
	// These hashes will be stored in the leaf nodes.
	for (auto trans: block.m_Transactions) {
		string hash = Hash(*trans);
		tree[index - 1] = &hash;

		index--;
	}

	// Pad the leaves, if necessary
	while (leaves % 2 != 0) {
		tree[index - 1] = tree[index];
		index--, leaves++, pads--;
	}

	int npl = leaves; // The number of nodes per level of the tree
	index = nodes - leaves - 1; // Set the index to the number of remaining nodes
	string hash;

	while (index >= 0) {
		// A parent node's children are at 2i + 1 (left) and 2i + 2 (right).
		hash = Hash(*tree[2 * index + 1] + *tree[2 * index + 2]);
		tree[index] = &hash;
		index--;

		//
		// Pad any levels that become uneven in the tree generation process.
		// For example, a tree with a second row of 3 nodes will need to be
		// padded to 4.
		//
		// The root node is the top of the tree, not a row with 1 node that needs
		// to be padded to 2.
		//
		if (npl % 2 != 0 && npl > 1) {
			*tree[index - 1] = *tree[index];
			index--, pads--;
		}

		npl /= 2;
	}

	return Hash(*tree[0] + std::to_string(block.m_Nonce));
}