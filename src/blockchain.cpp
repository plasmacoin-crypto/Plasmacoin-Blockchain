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
	for (const auto& block: m_Blockchain) {
		delete block;
	}
}

// Add a confirmed block to the blockchain
int Blockchain::Add(Block* block) {
	if (block == nullptr) {
		return -1;
	}
	else {
		m_Blockchain.push_back(new Block(*block));
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
	return m_Blockchain;
}

// Get the block that was most recently added to the blockchain
Block* Blockchain::GetLatest() const {
	return m_Blockchain.back();
}

// Get any block on the blockchain using its index
Block* Blockchain::Get(int index) const {
	return m_Blockchain[index];
}

float Blockchain::GetDifficulty() const {
	return m_Difficulty;
}

int256_t Blockchain::GetTarget() const {
	return m_Target;
}

bool Blockchain::Find(Transaction* transaction) {
	for (auto blockchainIter = m_Blockchain.begin(); blockchainIter != m_Blockchain.end(); std::advance(blockchainIter, 1)) {
		for (auto trxnIter = (*blockchainIter)->m_Transactions.begin(); trxnIter != (*blockchainIter)->m_Transactions.end(); std::advance(trxnIter, 1))   {
			if ((*trxnIter)->m_Hash == transaction->m_Hash) {
				return true;
			}

			//std::advance(trxnIter, 1);
		}

		//std::advance(blockchainIter, 1);
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

void Blockchain::CalcDifficulty() {
	std::vector<int64_t> miningTimes;
	//std::vector<Block*> last16(m_Blockchain.end() - DIFFICULTY_RECALC, m_Blockchain.end());

	// Get the time it took to mine the last 16 blocks
	for (auto iter = m_Blockchain.end() - DIFFICULTY_RECALC; iter != m_Blockchain.end(); std::advance(iter, 1)) {
		Block* block = *iter;
		miningTimes.push_back(block->m_MineTime - block->m_CreationTime);
	}

	float medianTime = utility::median(miningTimes);

	// Compute the new difficulty and set the new target hash
	m_Difficulty *= EXPECTED_MINE_TIME / medianTime;
	SetTarget();
}

void Blockchain::SetTarget() {
	m_Target = MAX_TARGET / boost::lexical_cast<int256_t>(m_Difficulty);
}

// Create a new block with unconfirmed transactions and run Proof-of-Woork
// on it.
pair<bool, uint8_t> Blockchain::Mine(Block& newBlock) {
	future<bool> runConsensus = std::async(std::launch::deferred, &Blockchain::Consensus, this, std::ref(newBlock));

	bool success = false;
	std::cout << "Mining" << std::endl;
	if (!newBlock.m_Transactions.empty()) {
		runConsensus.wait();
		success = runConsensus.get();
	}

	// By this point, if the node hasn't recieved information that the current block has been
	// completed, broadcast to the network that this node has completed it first.
	if (success) {
		std::cout << "Success" << std::endl;
	}
	else {
		std::cout << "Failure" << std::endl;
		std::cout << newBlock.m_Hash << std::endl;
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
