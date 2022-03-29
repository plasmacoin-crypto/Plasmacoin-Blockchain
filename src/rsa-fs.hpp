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

#include <cryptopp/rsa.h> 	   	 // Use Crypto++'s RSA functionality
#include <cryptopp/files.h>    	 // Use FileSink
#include <cryptopp/queue.h>    	 // Use ByteQueue
#include <cryptopp/cryptlib.h> 	 // Use BufferedTransformation
#include <cryptopp/hex.h>		 // Use HexEncoder/HexDecoder
#include <cryptopp/base64.h>	 // Use Base64Encoder/Base64Decoder
#include <cryptopp/filters.h> 	 // Use StringSink
#include <cryptopp/config_int.h> // Use CryptoPP::byte

using CryptoPP::RSA;

namespace rsafs {
	const string PUB_FILENAME  = "pc_pub.key";
	const string PRIV_FILENAME = "pc_priv.key";
	const string TMP_KEY_NAME = "key.txt";

	const string TMP_DIR = fs::temp_directory_path();

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
	const string TMP_PATH = (TMP_DIR.back() == DELIM)? TMP_DIR + TMP_KEY_NAME : TMP_DIR + DELIM + TMP_KEY_NAME;
	//const string RSA_PATH = /*C:\ ?*/ DIR_PATH + FILENAME;

	fs::path writeKeys(const CryptoPP::InvertibleRSAFunction& keys, const string& path = DIR_PATH);
	void readKeys(RSA::PublicKey& pubKey, RSA::PrivateKey& privKey, const string& path = DIR_PATH);

	void saveToFile(const string& filename, const CryptoPP::BufferedTransformation& bt);

	void saveHex(const string& filename, const CryptoPP::BufferedTransformation& bt);
	void loadHex(const string& filename, CryptoPP::BufferedTransformation& bt);

	void saveBase64(const string& filename, const CryptoPP::BufferedTransformation& bt);
	void loadBase64(const string& filename, CryptoPP::BufferedTransformation& bt);
	string readBase64(const string& filename, CryptoPP::BufferedTransformation& bt);

	string toBase64String(const CryptoPP::RSAFunction& rsaKey);
	CryptoPP::RSAFunction fromBase64String(const string& strKey);

	void createRSAPath(const string& dirpath = DIR_PATH);
	bool pathOkay(const string& path);
	string dirName(const string& path);
}

#endif // RSA_FS_HPP
