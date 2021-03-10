//
// FILENAME: node.hpp | Plasmacoin Cryptocurrency
// DESCRIPTION: A computer (user) that has access to the blockchain
// CREATED: 2021-01-17 @ 9:54 PM
// COPYRIGHT: Copyright (c) 2021 by Ryan Smith <rysmith2113@gmail.com>
//

#ifndef NODE_HPP
#define NODE_HPP

#include <string>
#include <utility>
#include <sstream>
#include <functional>

#include "cryptopp-sha256-libs.h"

#include "transaction.hpp"
#include "block.hpp"

using std::string;
using std::pair;

#include <cryptopp/rsa.h> 		// Use Crypto++'s RSA functionality
#include <cryptopp/osrng.h> 	// Use AutoSeededRandomPool
#include <cryptopp/oaep.h>		// Use RSAES_OAEP_SHA_Encryptor
#include <cryptopp/filters.h>	// Use PK_EncryptorFilter
#include <cryptopp/cryptlib.h> 	// Use GenerateRandomWithKeySize

using CryptoPP::RSA;
using CryptoPP::Integer;

Integer pop(Integer n);

class Node {
	typedef CryptoPP::RandomNumberGenerator CRYPTOPP_RNG; // Make this long name a little easier to use

public:
	Node(string name, string username, string passwd, string ip, bool isMaster);
	Transaction MakeTransaction(Node& recipient, float amount, string content) const;

	// Some getters
	string GetName() const, GetUsrName() const, GetIP() const;

	pair<RSA::PublicKey, RSA::PrivateKey> GenerateKeys() noexcept(false);
	Block Sign(Block& block), Verify(Block& block);

private:
	string m_Name, m_Username, m_Password, m_IPAddr;

	RSA::PublicKey 	m_PubKey;
	RSA::PrivateKey m_PrivKey;

	bool isMaster;

	// Set some values Crypto++ needs to calculate the inverse of
	// the RSA encryption
	CryptoPP::InvertibleRSAFunction SetValues();

	string Hash(Transaction transaction);
};

Node::Node(string name, string username, string passwd, string ip, bool isMaster = false):
	// User data
	m_Name(name),
	m_Username(username),
	m_Password(passwd),
	m_IPAddr(ip),
	isMaster(isMaster)
{
	//std::tie(m_PubKey, m_PrivKey) = GenerateKeys(); // Generate a set of RSA keys for the user
}

Transaction Node::MakeTransaction(Node& recipient, float amount, string content) const {
	// From Transaction::m_Condensed:
	// <SENDER>: <AMOUNT> Plasmacoins to <RECIPIENT>; <NONCE>
	string condensed = recipient.GetUsrName() + ": " + std::to_string(amount) +
					   " Plasmacoins to " + recipient.GetUsrName() + "; 0"; // Use 0 as the starting nonce

	// A new transaction between the current user and another user in the
	// network.
	return Transaction(Node(m_Name, m_Username, m_Password, m_IPAddr),
					   recipient, content, amount, condensed);
}

// Get the user's name
string Node::GetName() const {
	return m_Name;
}

// Get the user's username
string Node::GetUsrName() const {
	return m_Username;
}

// Get the user's global IP address
string Node::GetIP() const {
	return m_IPAddr;
}

// Generate public and private RSA keys for signing transactions
pair<RSA::PublicKey, RSA::PrivateKey> Node::GenerateKeys() noexcept(false) {
	Integer n("0xbeaadb3d839f3b5f"), e("0x11"), d("0x21a5ae37b9959db9"); // Numbers used in the calculations
	CRYPTOPP_RNG randnum = CRYPTOPP_RNG(); // Use Crypto++'s random number generator

	// Generate some RSA keys
	RSA::PrivateKey privKey;
	privKey.Initialize(n, e, d);

	RSA::PublicKey pubKey;
	pubKey.Initialize(n, e);

	// Validate the private key that was generated. If this key passes, the
	// public key does not need to be tested.
	// if (!privKey.Validate(randnum, 3)) {
	// 	throw std::runtime_error("Private key validation failed. Aborting.");
	// }

	return std::make_pair(pubKey, privKey);
}

// Sign a transaction (i.e., the transaction's hash) with the sender's private key
Block Node::Sign(Block& block) {
	Integer n("0xbeaadb3d839f3b5f"), e("0x11"), d("0x21a5ae37b9959db9"); // Numbers used in the calculations

	CryptoPP::AutoSeededRandomPool rng;
	CryptoPP::InvertibleRSAFunction params;

	// Generate the RSA key
	RSA::PrivateKey privKey(params);
	privKey.GenerateRandomWithKeySize(rng, 3072);

	string cipher;

	// Sign the hash
	CryptoPP::RSAES_OAEP_SHA_Encryptor encryptor(privKey);
	CryptoPP::StringSource ss1(block.m_Hash.c_str(), true,
		new CryptoPP::PK_EncryptorFilter(rng, encryptor,
			new CryptoPP::StringSink(cipher)
		) // PK_EncryptorFilter
	); // StringSource

	privKey.Initialize(n, e, d);

	// Get some data needed to apply the encryption function
	Integer m((const CryptoPP::byte*)block.m_Hash.c_str(), block.m_Hash.size());

	// Convert the Integer to a std::string
	std::stringstream stream;
	stream << std::hex << privKey.ApplyFunction(m);

	string signedHash = stream.str(); // Get the stringstream as a string

	block.m_SSignature = signedHash;

	return block;
}

// Verify a transaction with the sender's public key
Block Node::Verify(Block& block) {
	Integer n("0xbeaadb3d839f3b5f"), e("0x11"), d("0x21a5ae37b9959db9"); // Numbers used in the calculations
	CRYPTOPP_RNG rng = CRYPTOPP_RNG(); // Use Crypto++'s random number generator

	// Generate the RSA key
	RSA::PrivateKey privKey;
	privKey.Initialize(n, e, d);

	// Get the encrypted message
	Integer encrmsg((const CryptoPP::byte*)block.m_SSignature.c_str(), block.m_SSignature.size());
	// std::cout << encrmsg << std::endl;
	// encrmsg = pop(encrmsg);
	// std::cout << encrmsg << std::endl;

	//SetValues();

	//Integer recovered(privKey.CalculateInverse(rng, encrmsg)); // Reverse the encryption

	// Round trip the message
	//size_t req = recovered.MinEncodedSize();
	//block.m_RSignature.resize(req);
	//recovered.Encode((CryptoPP::byte*)block.m_RSignature.data(), block.m_RSignature.size());

	return block;
}

CryptoPP::InvertibleRSAFunction Node::SetValues() {
	CRYPTOPP_RNG rng = CRYPTOPP_RNG();
	CryptoPP::InvertibleRSAFunction rsa;

	rsa.GenerateRandomWithKeySize(rng, 3072);

	// Do the calculations
	const Integer& n = rsa.GetModulus();
	const Integer& p = rsa.GetPrime1();
	const Integer& q = rsa.GetPrime2();
	const Integer& d = rsa.GetPrivateExponent();
	const Integer& e = rsa.GetPublicExponent();

	return rsa;
}

// Use Crypto++ to hash the transaction data
string Node::Hash(Transaction transaction) {
	CryptoPP::SHA256 hash;
	string digest; // The result
	string message = transaction.m_Condensed;

	// Use the library
	//
	// No objects have to be freed because of Crypto++'s pipelining
	// functionality
	//
	CryptoPP::StringSource ssource(message, true,
		new CryptoPP::HashFilter(hash,
			new CryptoPP::HexEncoder(
				new CryptoPP::StringSink(digest)
			)
		)
	);

	return digest;
}

// Remove the last digit in a CryptoPP::Integer
Integer pop(Integer n) {
	// Convert the Integer to a std::string
	std::stringstream stream;
	stream << n;

	string str_stream = stream.str(); // Get the stringstream as an std::string
	str_stream.pop_back(); // Remove the last character
	std::cout << str_stream << std::endl;

	// Convert back to a CryptoPP::Integer and return
	return Integer((const CryptoPP::byte*)str_stream.c_str(), str_stream.size());
}

#endif // NODE_HPP
