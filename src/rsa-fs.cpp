//
// FILENAME: rsa-fs.cpp | Plasmacoin Cryptocurrency
// DESCRIPTION: The source file for rsa-fs.hpp
// CREATED: 2021-08-23 @ 1:27 AM
// COPYRIGHT: Copyright (c) 2021 by Ryan Smith <rysmith2113@gmail.com>
//

#include "rsa-fs.hpp"

// Write a user's RSA keys to their filesystem, either at the default path or
// at a custom path the user provided. If the provided path doesn't exist, those
// directories and/or files are created first.
fs::path rsafs::writeKeys(CryptoPP::InvertibleRSAFunction keys, string path) {
	if (!fs::exists(rsafs::dirName(path)) || !fs::exists(path)) {
		rsafs::createRSAPath(path); // Create a path to store the keys
	}

	// Write the keys to the path on in the filesystem
	CryptoPP::FileSink output(string(path).c_str());
	keys.DEREncode(output);

	return fs::path(path);
}

// Read the user's RSA keys from the key file
pair<RSA::PublicKey, RSA::PrivateKey> rsafs::readKeys(CryptoPP::InvertibleRSAFunction keys, string path) {
	CryptoPP::FileSource input(string(path).c_str(), true);
	keys.BERDecode(input);

	return std::make_pair(RSA::PublicKey(keys), RSA::PrivateKey(keys));
}

// Create a place to store the user's RSA keys if the provided path doesn't exist.
// On Windows, this creates a file in `%HOMEDRIVE%%HOMEPATH%\\.ssh` by default.
// On Linux and macOS, the file is created in `$HOME/.ssh`. On all platforms, the
// file's name is `pc_rsa_keys`.
void rsafs::createRSAPath(string path) {
	fs::create_directory(rsafs::dirName(path));
	std::ofstream rsaKeyFile(path);
}

// Check if a given path exists and is not an empty string
bool rsafs::pathOkay(string path) {
	return fs::exists(path) && !path.empty();
}

// Split the directory path from the filename in a given path
string rsafs::dirName(const string& path) {
	size_t found = path.find_last_of("/\\");
    return path.substr(0, found);
}
