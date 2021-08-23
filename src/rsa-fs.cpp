//
// FILENAME: rsa-fs.cpp | Plasmacoin Cryptocurrency
// DESCRIPTION: The source file for rsa-fs.hpp
// CREATED: 2021-08-23 @ 1:27 AM
// COPYRIGHT: Copyright (c) 2021 by Ryan Smith <rysmith2113@gmail.com>
//

#include "rsa-fs.hpp"

// Write a user's RSA keys to their filesystem
fs::path rsafs::writeKeys(CryptoPP::InvertibleRSAFunction keys, string path) {
	if (!fs::exists(path + "/pc_rsa_keys")) {
		rsafs::createRSAPath(path);
	}

	CryptoPP::FileSink output(string(path + "/pc_rsa_keys").c_str());
	keys.DEREncode(output);

	return fs::path(path);
}

// Read the user's RSA keys from the key file
pair<RSA::PublicKey, RSA::PrivateKey> rsafs::readKeys(CryptoPP::InvertibleRSAFunction keys, string path) {
	CryptoPP::FileSource input(string(path + "/pc_rsa_keys").c_str(), true);
	keys.BERDecode(input);

	return std::make_pair(RSA::PublicKey(keys), RSA::PrivateKey(keys));
}

void rsafs::createRSAPath(string path) {
	fs::create_directory(path);
	std::ofstream rsaKeyFile(path + "/pc_rsa_keys");
}
