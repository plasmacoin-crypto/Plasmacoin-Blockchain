//
// FILENAME: utility.hpp | Plasmacoin Cryptocurrency
// DESCRIPTION: Plasmacoin utility functions
// CREATED: 2021-02-06 @ 7:37 PM
// COPYRIGHT: Copyright (c) 2022 by Ryan Smith <rysmith2113@gmail.com>
//

#ifndef UTILITY_HPP
#define UTILITY_HPP

// We aren't allowed to have a using directive for `std::filesystem`, so
// I'll create an alias for the namespace called `fs`.
#if __cplusplus >= 201703L /* C++17 or later (recommended) */
	#include <filesystem>
	namespace fs = std::filesystem;
#elif __cplusplus == 201402L /* C++14 (experimental usage) */
	#include <experimental/filesystem>
	namespace fs = std::experimental::filesystem; // This way, `filesystem::exists()` (`fs::exists()`) always works
#endif

#include <string>
#include <ctime>
#include <chrono>
#include <cstdio>

using std::string;

#include <cryptopp/rsa.h> 	   	 // Use Crypto++'s RSA functionality
#include <cryptopp/files.h>    	 // Use FileSink
#include <cryptopp/queue.h>    	 // Use ByteQueue
#include <cryptopp/base64.h>	 // Use Base64Encoder/Base64Decoder
#include <cryptopp/filters.h> 	 // Use StringSink
#include <cryptopp/config_int.h> // Use CryptoPP::byte
#include <cryptopp/secblock.h> 	 // Use SecByteBlock

using CryptoPP::RSA;

#include "rsa-fs.hpp"

namespace utility {
	const static int IPv4_MAX_LENGTH = 15;
	const static int IPv4_PORT_MAX_LENGTH = 5;

	string getUTCTime();

	string pubKeyToBase64(const CryptoPP::RSAFunction& rsaKey);
	CryptoPP::RSAFunction pubKeyFromBase64(const string& base64key);

	string sigToBase64(const CryptoPP::SecByteBlock& signature);
	CryptoPP::SecByteBlock sigFromBase64(const string& base64sig);

	string sbbToString(const CryptoPP::SecByteBlock& sbb);
	CryptoPP::SecByteBlock sbbFromString(const string& strSbb);

	string IPv4(uint8_t o1, uint8_t o2, uint8_t o3, uint8_t o4);
	string IPv4(uint8_t o1, uint8_t o2, uint8_t o3, uint8_t o4, uint16_t port);
}

#endif // UTILITY_HPP