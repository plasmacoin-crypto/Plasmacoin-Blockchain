//
// FILENAME: hashing.cpp | Plasmacoin Cryptocurrency
// DESCRIPTION: The source file for hashing.hpp
// CREATED: 2022-01-21 @ 1:23 PM
// COPYRIGHT: Copyright (c) 2021 by Ryan Smith <rysmith2113@gmail.com>
//

#include "hashing.hpp"

// Hash some data
string hashing::hash(const string& input) {
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

// Hash a transaction
string hashing::hash(const Transaction& transaction) {
	string message = transaction.m_SenderAddr + transaction.m_RecipientAddr + \
					 std::to_string(transaction.m_Amount + transaction.m_Fee) + \
					 transaction.m_Content;

	return hashing::hash(message);
}

// Hash a block using a Merkle Tree
string hashing::hash(const Block& block) {
	if (block.m_Transactions.size() == 1) {
		return hashing::hash(hashing::hash(*block.m_Transactions[0]) + std::to_string(block.m_Nonce));
	}

	// Declare some variables
	int leaves = block.m_Transactions.size(), // Each transaction's hash becomes a leaf
		pads   = mh_pads(leaves),
		height = mh_height(leaves),
		nodes  = mh_nodes(height);

	string tree[nodes]; // The Merkle Tree
	int index = nodes;	 // The current node that's being accessed

	// Add the hashes of all the transactions on the block to the tree.
	// These hashes will be stored in the leaf nodes.
	for (auto trans: block.m_Transactions) {
		string hash = hashing::hash(*trans);

		tree[index - 1] = hash;
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
		hash = hashing::hash(tree[2 * index + 1] + tree[2 * index + 2]);
		tree[index] = hash;
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
			tree[index - 1] = tree[index];
			index--, pads--;
		}

		npl /= 2;
	}

	return hashing::hash(tree[0] + std::to_string(block.m_Nonce));
}