//
// FILENAME: dat-fs.hpp | Plasmacoin Cryptocurrency
// DESCRIPTION: Use the filesystem to save blockchain data on a user's computer
// CREATED: 2021-09-19 @ 10:00 PM
// COPYRIGHT: Copyright (c) 2021 by Ryan Smith <rysmith2113@gmail.com>
//

#ifndef DAT_FS_HPP
#define DAT_FS_HPP

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
#include <fstream>
#include <tuple>
#include <utility>
#include <vector>

using std::string;

#include <QJsonObject>
#include <QJsonDocument>
#include <QFile>

#include <cryptopp/cryptlib.h>
#include <cryptopp/rijndael.h>
#include <cryptopp/modes.h>
#include <cryptopp/files.h>
#include <cryptopp/osrng.h>
#include <cryptopp/hex.h>
#include <cryptopp/config_int.h>
#include <cryptopp/secblock.h>

using CryptoPP::AES;
using CryptoPP::byte;

#include "block.hpp"
#include "receipt.hpp"
#include "parse-json.hpp"
#include "utility.hpp"
#include "parse-json.hpp"

namespace datfs {
	#ifdef _WIN32
		// On Windows, `getenv()` is deprecated
		const string APP_DATA = getenv_s(R"(%APPDATA%)") != nullptr? string(getenv_s(R"(%APPDATA%)")) + "\\Plasmacoin" : "";
		const char DELIM	  = '\\';
	#elif __APPLE__
		const string APP_DATA = getenv("HOME") != nullptr? string(getenv("HOME")) + "/Library/Application Support/Plasmacoin" : "";
		const char DELIM	  = '/';
	#elif __linux__
		const string APP_DATA = getenv("HOME") != nullptr? string(getenv("HOME")) + "/.plasmacoin" : "";
		const char DELIM	  = '/';
	#endif

	const string BLOCKS_LOC = APP_DATA + DELIM + "blocks";
	const string WALLET_LOC = APP_DATA + DELIM + "wallet";
	const string CREDS_LOC  = APP_DATA + DELIM + "credentials";

	void createDataPath();
	void saveBlock(Block* block);
	void saveReceipt(Receipt* receipt);

	void saveLoginInfo(const string& email, const string& password);
	std::pair<string, string> loadLoginInfo();
	bool hasCredCache();

	void saveAESData(const CryptoPP::SecByteBlock& key, const CryptoPP::SecByteBlock& iv);
	std::pair<CryptoPP::SecByteBlock, CryptoPP::SecByteBlock> loadAESData();

	std::tuple<string, CryptoPP::SecByteBlock, CryptoPP::SecByteBlock> AESEncrypt(const string& message);
	string AESDecrypt(const string& cipher, const CryptoPP::SecByteBlock& key, const CryptoPP::SecByteBlock& iv);
}

#endif // DAT_FS_HPP