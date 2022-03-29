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
fs::path rsafs::writeKeys(const CryptoPP::InvertibleRSAFunction& keys, const string& path) {
	if (
		!fs::exists(path) ||
		!fs::exists(path + rsafs::PUB_FILENAME) ||
		!fs::exists(path + rsafs::PRIV_FILENAME)
	) {
		rsafs::createRSAPath(path); // Create a path to store the keys
	}

	RSA::PublicKey publicKey = RSA::PublicKey(keys);
	RSA::PrivateKey privateKey = RSA::PrivateKey(keys);

	CryptoPP::ByteQueue queue;

	publicKey.Save(queue);
	rsafs::saveBase64(path + rsafs::PUB_FILENAME, queue);

	queue.Clear();

	privateKey.Save(queue);
	rsafs::saveBase64(path + rsafs::PRIV_FILENAME, queue);

	return fs::path(path);
}

// Read the user's RSA keys from the key file
void rsafs::readKeys(RSA::PublicKey& pubKey, RSA::PrivateKey& privKey, const string& path) {
	string pubKeyPath = path + rsafs::PUB_FILENAME;
	string privKeyPath = path + rsafs::PRIV_FILENAME;

	CryptoPP::ByteQueue queue;

	// Load the public key
    rsafs::loadBase64(pubKeyPath, queue);
    pubKey.Load(queue);

	queue.Clear();

	// Load the private key
	rsafs::loadBase64(privKeyPath, queue);
    privKey.Load(queue);
}

// Save data to a file using Crypto++'s FileSink class
void rsafs::saveToFile(const string& filename, const CryptoPP::BufferedTransformation& bt) {
	CryptoPP::FileSink fileSink(filename.c_str());
    bt.CopyTo(fileSink);
    fileSink.MessageEnd();
}

// Hex encode a raw RSA key and save it to the filesystem
void rsafs::saveHex(const string& filename, const CryptoPP::BufferedTransformation& bt) {
	CryptoPP::HexEncoder encoder;

	bt.CopyTo(encoder);
    encoder.MessageEnd();

    rsafs::saveToFile(filename, encoder);
}

// Load a hex-encoded RSA key from the filesystem and decode it
void rsafs::loadHex(const string& filename, CryptoPP::BufferedTransformation& bt) {
	std::string encoded, decoded;

	CryptoPP::FileSource file(filename.c_str(), true, new CryptoPP::StringSink(encoded));
    file.TransferTo(bt);
    bt.MessageEnd();

	CryptoPP::HexDecoder decoder;
	std::cout << encoded << std::endl;

	decoder.Attach(new CryptoPP::Redirector(bt));
	decoder.Put(reinterpret_cast<CryptoPP::byte*>(encoded.data()), encoded.size());
	decoder.MessageEnd();
}

// Base64 encode a raw RSA key and save it to the filesystem
void rsafs::saveBase64(const string& filename, const CryptoPP::BufferedTransformation& bt) {
	CryptoPP::Base64Encoder encoder;

	bt.CopyTo(encoder);
	encoder.MessageEnd();

	rsafs::saveToFile(filename, encoder);
}

// Load a Base64-encoded RSA key from the filesystem and decode it
void rsafs::loadBase64(const string& filename, CryptoPP::BufferedTransformation& bt) {
	std::string encoded;

	CryptoPP::FileSource file(filename.c_str(), true, new CryptoPP::StringSink(encoded));
    file.TransferTo(bt);
    bt.MessageEnd();

	CryptoPP::Base64Decoder decoder;

	decoder.Attach(new CryptoPP::Redirector(bt));
	decoder.Put(reinterpret_cast<CryptoPP::byte*>(encoded.data()), encoded.size());
	decoder.MessageEnd();
}

// Read a Base64-encoded key from the filesystem as a string
string rsafs::readBase64(const string& filename, CryptoPP::BufferedTransformation& bt) {
	std::string base64;

	CryptoPP::FileSource file(filename.c_str(), true, new CryptoPP::StringSink(base64));
    file.TransferTo(bt);
    bt.MessageEnd();

	return base64;
}

// Create a place to store the user's RSA keys if the provided path doesn't exist.
//
// If the default path is used, behavior is as follows:
// * On Windows, this creates a file in `%USERPROFILE%\\.ssh`
// * On Linux and macOS, the file is created in `$HOME/.ssh`
// * On all platforms, the filenames are `pc_priv.key` and `pc_pub.key`.
//
void rsafs::createRSAPath(const string& path) {
	fs::create_directory(path);
	std::ofstream rsaPubKeyFile(path + rsafs::PUB_FILENAME);
	std::ofstream rsaPrivKeyFile(path + rsafs::PRIV_FILENAME);
}

// Check if a given path exists and is not an empty string
bool rsafs::pathOkay(const string& path) {
	return fs::exists(path) && !path.empty();
}

// Split the directory path from the filename in a given path
string rsafs::dirName(const string& path) {
	size_t found = path.find_last_of("/\\");
    return path.substr(0, found);
}
