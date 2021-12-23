//
// FILENAME: rsa-fs.hpp | Plasmacoin Cryptocurrency
// DESCRIPTION: Use the filesystem to save and retrieve a user's RSA keys
// CREATED: 2021-08-23 @ 1:27 AM
// COPYRIGHT: Copyright (c) 2021 by Ryan Smith <rysmith2113@gmail.com>
//

#ifndef RSA_FS_HPP
#define RSA_FS_HPP

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
#include <utility>
#include <fstream>
#include <cstdlib>

using std::string;
using std::pair;

#include <cryptopp/rsa.h> 	   	// Use Crypto++'s RSA functionality
#include <cryptopp/files.h>    	// Use FileSink
#include <cryptopp/queue.h>    	// Use ByteQueue
#include <cryptopp/cryptlib.h> 	// Use BufferedTransformation
#include <cryptopp/hex.h>		// Use HexEncoder

using CryptoPP::RSA;

namespace rsafs {
	const string PUB_FILENAME  = "pc_pub.key";
	const string PRIV_FILENAME = "pc_priv.key";

	// Separate Unix-style paths from Windows paths
	#ifdef _WIN32
		// On Windows, `getenv()` is deprecated
		const string HOME_DIR = getenv_s(R"(%USERPROFILE%)") != nullptr? string(getenv_s(R"(%USERPROFILE%)")) : "";
		const char DELIM	  = '\\';
	#elif __APPLE__ || __linux__
		const string HOME_DIR = getenv("HOME") != nullptr? string(getenv("HOME")) : "";
		const char DELIM	  = '/';
	#endif

	const string DIR_PATH = HOME_DIR + DELIM + ".ssh" + DELIM;
	//const string RSA_PATH = /*C:\ ?*/ DIR_PATH + FILENAME;

	fs::path writeKeys(const CryptoPP::InvertibleRSAFunction& keys, const string& path = DIR_PATH);
	void readKeys(RSA::PublicKey& pubKey, RSA::PrivateKey& privKey, const string& path = DIR_PATH);

	void saveHex(const string& filename, const CryptoPP::BufferedTransformation& bt);
	void loadHex(const string& filename, CryptoPP::BufferedTransformation& bt);

	void createRSAPath(const string& dirpath = DIR_PATH);
	bool pathOkay(const string& path);
	string dirName(const string& path);
}

#endif // RSA_FS_HPP
