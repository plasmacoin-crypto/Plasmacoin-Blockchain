//
// FILENAME: mining.hpp | Plasmacoin Cryptocurrency
// DESCRIPTION: Mining/PoW processes for the blockchain
// CREATED: 2022-06-17 @ 11:48 AM
// COPYRIGHT: Copyright (c) 2022 by Ryan Smith <rysmith2113@gmail.com>
//

#include "mining.hpp"

Block mining::makeBlock(Blockchain* blockchainCopy, const vector<Transaction*>& transactions, double difficulty) {
	if (blockchainCopy->Size() == 0) {
		return Block(0, transactions, difficulty, true); // Create a new block
	}
	else {
		Block* latest = blockchainCopy->GetLatest(); // Get the latest block
		return Block(latest->m_Index + 1, latest->m_Hash, transactions, difficulty); // Create a new block
	}
}

std::pair<bool, uint8_t> mining::mine(Blockchain* blockchainCopy, Block& block) {
	bool success;
	uint8_t code;
	std::tie(success, code) = blockchainCopy->Mine(block); // Mine the block

	std::cout << "Success: " << success << std::endl;
	std::cout << "Code: " << (uint)code << std::endl;

	// Verify and append the block
	if (success) {
		block.m_MineTime = utility::getUnixEpoch(); // Timestamp the block
	}

	return std::make_pair(success, code);
}

bool mining::validate(Blockchain* blockchainCopy, Block* block) {
	Blockchain* tempChain = new Blockchain(*blockchainCopy);
	tempChain->Add(block);
	return validation::validate(*tempChain);
}

void mining::transmitBlock(Block* block, const std::vector<string>& hosts) {
	Transmitter* transmitter = new Transmitter();
	auto data = transmitter->Format(block);
	transmitter->Transmit(data, std::stoi(data[0]), hosts);
	delete transmitter;
}

