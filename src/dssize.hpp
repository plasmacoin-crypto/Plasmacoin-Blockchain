//
// FILENAME: dssize.hpp | Plasmacoin Cryptocurrency
// DESCRIPTION: Calculate the size of blockchain data structures
// CREATED: 2022-02-04 @ 9:32 PM
// COPYRIGHT: Copyright (c) 2022 by Ryan Smith <rysmith2113@gmail.com>
//

#ifndef DS_SIZE_HPP
#define DS_SIZE_HPP

#include <cryptopp/config_int.h>

#include "block.hpp"
#include "transaction.hpp"

namespace dssize {
	const int PUBLIC_KEY_SIZE = 384; // Plasmacoin uses 3072-bit (384-byte) public keys

	size_t size(const Block& block);
	size_t size(const Transaction& transaction);
	size_t size(const Signature& signature);
}

#endif // DS_SIZE_HPP