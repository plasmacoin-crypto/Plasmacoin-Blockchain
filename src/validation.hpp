//
// FILENAME: validation.hpp | Plasmacoin Cryptocurrency
// DESCRIPTION: Validate transactions, blocks, and the blockchain
// CREATED: 2022-01-21 @ 12:57 PM
// COPYRIGHT: Copyright (c) 2022 by Ryan Smith <rysmith2113@gmail.com>
//

#ifndef VALIDATION_HPP
#define VALIDATION_HPP

#include <string>
#include <regex>
#include <cmath>
#include <iostream>

#include <boost/multiprecision/cpp_int.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/multiprecision/cpp_dec_float.hpp>

#include <cryptopp/rsa.h> 		// Use Crypto++'s RSA functionality
#include <cryptopp/osrng.h> 	// Use AutoSeededRandomPool

#include "blockchain.hpp"
#include "transaction.hpp"
#include "block.hpp"
#include "hashing.hpp"
#include "rsautil.hpp"

using boost::multiprecision::int256_t;
using boost::multiprecision::cpp_dec_float_50;

class Blockchain;

namespace validation {
	const int256_t MAX_TARGET {"0x00000fffffffffffffffffffffffffffffffffffffffffffffffffffffffffff"};

	bool validate(const Blockchain& blockchain);

	bool validate(const Transaction& transaction);
	bool validate(const Transaction& transaction, cpp_dec_float_50 target);

	bool validate(const Block& block, size_t chainLength);

	bool validate(const std::string& hash);
	bool validate(const std::string& hash, cpp_dec_float_50 target);
}

#endif // VALIDATION_HPP