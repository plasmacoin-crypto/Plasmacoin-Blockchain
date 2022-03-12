//
// FILENAME: blockchain.cpp | Plasmacoin Cryptocurrency
// DESCRIPTION: The source file for blockchain.hpp
// CREATED: 2021-03-34 @ 11:34 PM
// COPYRIGHT: Copyright (c) 2021 by Ryan Smith <rysmith2113@gmail.com>
//

#include "blockchain.hpp"
#include <iostream>

Blockchain::Blockchain() {}

Blockchain::~Blockchain() {
	for (auto block: m_Chain) {
		delete block;
	}
}

// Add a confirmed block to the blockchain
int Blockchain::Add(Block* block) {
	if (block == nullptr) {
		return -1;
	}
	else {
		m_Chain.push_back(new Block(*block));
		Save(block);
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
vector<Block*> Blockchain::GetBlockchain() const {
	return m_Chain;
}

// Get the block that was most recently added to the blockchain
Block* Blockchain::GetLatest() const {
	return m_Chain.back();
}

int64_t Blockchain::GetDifficulty() const {
	return m_Difficulty;
}

int256_t Blockchain::GetTarget() const {
	return m_Target;
}

bool Blockchain::Find(Transaction* transaction) {
	for (auto blockchainIter = m_Chain.begin(); blockchainIter != m_Chain.end(); std::advance(blockchainIter, 1)) {
		for (auto trxnIter = (*blockchainIter)->m_Transactions.begin(); trxnIter != (*blockchainIter)->m_Transactions.end(); std::advance(trxnIter, 1))   {
			if ((*trxnIter)->m_Hash == transaction->m_Hash) {
				return true;
			}

			std::advance(trxnIter, 1);
		}

		std::advance(blockchainIter, 1);
	}

	return false;
}

void Blockchain::Save(Block* block) const {
	datfs::saveBlock(block);
}

void Blockchain::Compress() {
	string path;

	for (unsigned int i = 0; i < this->Size(); i++) {
		path = datfs::BLOCKS_LOC + datfs::DELIM + "block" + std::to_string(i) + ".dat";
		go::gzipCompress(path.c_str());
	}
}

// Create a new block with unconfirmed transactions and run Proof-of-Woork
// on it.
pair<bool, uint8_t> Blockchain::Mine(Block& newBlock) {
	future<bool> runConsensus = std::async(std::launch::deferred, &Blockchain::Consensus, this, std::ref(newBlock));

	bool success = false;
	std::cout << "Mining" << std::endl;
	if (!newBlock.m_Transactions.empty()) {
		Block* latest = GetLatest();

		runConsensus.wait();
		success = runConsensus.get();
	}

	// By this point, if the node hasn't recieved information that the current block has been
	// completed, broadcast to the network that this node has completed it first.
	if (success) {
		std::cout << "Success" << std::endl;

		// const char* code[] = {"0"};
		// go::GoSlice slice = {code, 1, 1};

		// future<void> dial = std::async(&go::dial, "tcp", "192.168.1.44", "8080", static_cast<uint8_t>(go::PacketTypes::ID_CODE), slice);
	}
	else {
		std::cout << "Failure" << std::endl;

		std::cout << newBlock.m_Hash << std::endl;

		// const char* code[] = {"4"};
		// go::GoSlice slice = {code, 1, 1};

		// future<void> dial = std::async(&go::dial, "tcp", "192.168.1.44", "8080", static_cast<uint8_t>(go::PacketTypes::ID_CODE), slice);
	}

	return std::make_pair(success, 0);
}

// Complete the Proof-of-Work consensus protocol on a block. Return true
// if the correct hash was successfully found. The only way false would be
// returned is if a node was able to complete the hash before another.
bool Blockchain::Consensus(Block& block) {
	// Get the nonce. If the difficulty is 5, the string representation
	// of the nonce will be "00000".
	//string strNonce = string(DIFFICULTY, '0');
	string hash = "";

	//exitSignal.wait_for(std::chrono::milliseconds(1)) == std::future_status::timeout

	while (!validation::validate(hash, m_Target)) {
		string mem = shared_mem::readMemory(true);
		shared_mem::deleteMemory(shared_mem::FILENAME);

		if (json::getPacketType(json::parse(mem)) == static_cast<uint8_t>(go::PacketTypes::BLOCK)) {
			// Read the block from shared memory and convert it to a class
			Block* blockFromMem = json::toBlock(json::parse(mem));
			block = Block(*blockFromMem);
			return false;
		}

		//std::cout << "Nonce: " << block.m_Nonce << std::endl;
		hash = hashing::hash(block); // Hash the block

		if (validation::validate(hash, m_Target)) {
			break;
		}

		block.m_Nonce++; // Increase the nonce
	}

	std::cout << "Thread exited" << std::endl;

	block.m_Hash = hash;

	return true && validation::validate(block.m_Hash, m_Target);
}

void Blockchain::StopMining(std::promise<void>&& exitSignal) {
	exitSignal.set_value();
}

// Make sure the blockchain isn't corrupted
// bool Blockchain::Validate() {
// 	string hash;

// 	std::cout << "Validating Blockchain" << std::endl;

// 	for (auto block: m_Chain) {
// 		hash = hashing::hash(*block); // Regenerate the block hash

// 		// Make sure the block is valid. One invalid block invalidates the whole
// 		// chain, because the previous hashes of all the following blocks will
// 		// be invalid.
// 		if (!block->Validate(block->m_Hash, block->m_PrevHash, DIFFICULTY)) {
// 			return false;
// 		}
// 	}

// 	return true;
// }

// bool Blockchain::ValidateHash(const string& hash) {
// 	if (hash.empty()) {
// 		return false;
// 	}

// 	string substring = hash.substr(0, DIFFICULTY); // The first characters of the hash that represent the difficulty
// 	return substring.find(string(DIFFICULTY, '0')) != string::npos;
// }

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

// Use Crypto++ to hash the transaction data
string Blockchain::Hash(const Transaction& transaction) {
	string message = transaction.m_SenderAddr + transaction.m_RecipientAddr + \
					 std::to_string(transaction.m_Amount + transaction.m_Fee) + \
					 transaction.m_Content;

	return Hash(message);
}

// Hash a block by constructing a Merkle Tree. Each block hash will be make up of hashes of
// concatenations of hashes until a root node for the tree is generated.
string Blockchain::Hash(const Block& block) {
	if (block.m_IsGenesis) {
		return string(64, '0');
	}
	else if (block.m_Transactions.size() == 1) {
		return Hash(Hash(*block.m_Transactions[0]) + std::to_string(block.m_Nonce));
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
		string hash = Hash(*trans);

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
		hash = Hash(tree[2 * index + 1] + tree[2 * index + 2]);
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

	return Hash(tree[0] + std::to_string(block.m_Nonce));
}