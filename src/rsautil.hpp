//
// FILENAME: rsautil.hpp | Plasmacoin Cryptocurrency
// DESCRIPTION: RSA signing, verification, and key generation
// CREATED: 2022-03-29 @ 3:01 PM
// COPYRIGHT: Copyright (c) 2022 by Ryan Smith <rysmith2113@gmail.com>
//

#ifndef RSA_UTIL_HPP
#define RSA_UTIL_HPP

#include <tuple>

#include <cryptopp/rsa.h> 		 // Use Crypto++'s RSA functionality
#include <cryptopp/sha.h>		 // Use the SHA256 class
#include <cryptopp/cryptlib.h> 	 // Use GenerateRandomWithKeySize
#include <cryptopp/osrng.h> 	 // Use AutoSeededRandomPool
#include <cryptopp/secblock.h> 	 // Use SecByteBlock
#include <cryptopp/pkcspad.h>	 // Use the PKCS1v15 struct
#include <cryptopp/config_int.h> // Use CryptoPP::byte

using CryptoPP::RSA;
using CryptoPP::byte;

#include "transaction.hpp"
#include "receipt.hpp"

namespace rsautil {
	std::tuple<CryptoPP::InvertibleRSAFunction, RSA::PublicKey, RSA::PrivateKey> generateKeys() noexcept(false);

	void sign(Transaction& transaction, const RSA::PublicKey& publicKey, const RSA::PrivateKey& privateKey) noexcept(false);
	void sign(Receipt& transaction, const RSA::PublicKey& publicKey, const RSA::PrivateKey& privateKey) noexcept(false);

	bool verify(const Transaction& transaction, const CryptoPP::SecByteBlock& signature, size_t length, const RSA::PublicKey& publicKey);
	bool verify(const Receipt& receipt, const CryptoPP::SecByteBlock& signature, size_t length, const RSA::PublicKey& publicKey);
}

#endif // RSA_UTIL_HPP