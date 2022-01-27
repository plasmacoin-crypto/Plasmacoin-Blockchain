//
// FILENAME: hashing.hpp | Plasmacoin Cryptocurrency
// DESCRIPTION: Provide function wrappers around Crypto++ hashing
// CREATED: 2022-01-21 @ 1:23 PM
// COPYRIGHT: Copyright (c) 2021 by Ryan Smith <rysmith2113@gmail.com>
//

#ifndef HASHING_HPP
#define HASHING_HPP

#include <string>

// This header file groups three Crypto++ headers to save space
// and also provide them with a descriptive, overall name.
#include "cryptopp-sha256-libs.h"

#include "transaction.hpp"
#include "block.hpp"
#include "merkle-helpers.h"

using std::string;

namespace hashing {
	string hash(const string& input);
	string hash(const Transaction& transaction);
	string hash(const Block& block);
}

#endif // HASHING_HPP