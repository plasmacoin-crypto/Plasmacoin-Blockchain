//
// FILENAME: validation.cpp | Plasmacoin Cryptocurrency
// DESCRIPTION: The source file for validation.hpp
// CREATED: 2022-01-21 @ 12:57 PM
// COPYRIGHT: Copyright (c) 2021 by Ryan Smith <rysmith2113@gmail.com>
//

#include "validation.hpp"

bool validation::validate(const Blockchain& blockchain) {
	std::cout << "Validating Blockchain" << std::endl;

	bool valid;
	size_t chainLength = blockchain.Size();

	for (auto block: blockchain.GetBlockchain()) {
		valid = validation::validate(*block, chainLength);

		// If the blockchain has an invalid block, the whole chain is invalid
		if (!valid) {
			break;
		}
	}

	return true;
}

bool validation::validate(const Transaction& transaction) {
	// Check if the addresses are valid

	// Check if the transaction hash is valid
	bool hashValid = validation::validate(transaction.m_Hash);

	// Validate the signature

	// 1. Make sure the signature isn't empty
	bool nonEmpty = (
		transaction.m_Signature.m_Length > 0 &&
		transaction.m_Signature.m_Length == transaction.m_Signature.m_Signature.size() &&
		!transaction.m_Signature.m_Signature.empty()
	);

	// 2. Validate the sender's public key
	CryptoPP::AutoSeededRandomPool rng;
	bool pubKeyValid = transaction.m_Signature.m_PublicKey.Validate(rng, 3);

	bool signatureValid = nonEmpty && pubKeyValid;

	// Make sure the transaction is unique

	return hashValid && nonEmpty && signatureValid;
}

bool validation::validate(const Block& block, size_t chainLength) {
	bool indexValid = block.m_Index >= 0 && block.m_Index <= static_cast<int>(chainLength);
	bool nonceValid = block.m_Nonce > -1;

	// D = T_max / T_current => T_current = T_max / D
	const int256_t TARGET {validation::MAX_TARGET / block.m_Difficulty};

	bool prevHashExists = !block.m_PrevHash.empty(); // Check if the previous hash exists on the block

	bool prevHashValid = validation::validate(block.m_PrevHash, TARGET); // Check if the previous hash is valid
	bool hashValid = validation::validate(block.m_Hash, TARGET); // Check if the block hash is valid
	bool hashesValid = prevHashValid && hashValid;

	bool hashesMatch = hashing::hash(block) == block.m_Hash; // Regenerate the block hash

	bool trxnsValid = false;

	for (auto trxn: block.m_Transactions) {
		trxnsValid = validation::validate(*trxn, TARGET);

		// Once one transaction is invalid, the whole block is invalid
		if (!trxnsValid) {
			break;
		}
	}

	if (block.m_Transactions.size() < 1) {
		trxnsValid = false;
	}

	return indexValid && nonceValid && prevHashExists && hashesValid && hashesMatch && trxnsValid;
}

bool validation::validate(const std::string& hash) {
	if (hash.empty()) {
		return false;
	}

	// Check if the hash is valid SHA-256
	const std::regex SHA_256_REGEX("(?:[a-f0-9]|[A-F0-9]){64}");
	return std::regex_match(hash, SHA_256_REGEX);
}

bool validation::validate(const std::string& hash, int256_t target) {
	bool structValid = validation::validate(hash); // Check if the hash structure is valid

	// Check if the hash is below the target hash for PoW
	int256_t intHash {std::string("0x") + hash}; // Add "0x" to the hash before converting
	bool meetsTarget = intHash < target;

	return structValid && meetsTarget;
}