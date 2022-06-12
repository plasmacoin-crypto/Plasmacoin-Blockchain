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

#include <fstream>

#include <QJsonObject>
#include <QJsonDocument>

#include "block.hpp"
#include "receipt.hpp"
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

	void createDataPath();
	void saveBlock(Block* block);
	void saveReceipt(Receipt* receipt);
}

#endif // DAT_FS_HPP