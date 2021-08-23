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
#include <ostream>
#include <cstdlib>

using std::string;
using std::pair;

#include <cryptopp/rsa.h> 	// Use Crypto++'s RSA functionality
#include <cryptopp/files.h> // Use FileSink

using CryptoPP::RSA;

namespace rsafs {
	// Separate Unix-style paths from Windows paths
	#ifdef _WIN32
		// On Windows, `getenv()` is deprecated
		const string HOME_DIR = getenv_s(R"(%HOMEDRIVE%%HOMEPATH%)") != nullptr? string(getenv_s(R"(%HOMEDRIVE%%HOMEPATH%)")) : "";
		const string RSA_PATH = /*"C:\\" +*/ HOME_DIR + "\\.ssh";
	#elif __APPLE__ || __linux__
		const string HOME_DIR = getenv("HOME") != nullptr? string(getenv("HOME")) : "";
		const string RSA_PATH = HOME_DIR + "/.ssh";
	#endif

	fs::path writeKeys(CryptoPP::InvertibleRSAFunction keys, string path = RSA_PATH);
	pair<RSA::PublicKey, RSA::PrivateKey> readKeys(CryptoPP::InvertibleRSAFunction keys, string path = RSA_PATH);

	void createRSAPath(string path);
}

#endif // RSA_FS_HPP
