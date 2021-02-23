//
// FILENAME: node.hpp | Plasmacoin Cryptocurrency
// DESCRIPTION: A computer (user) that has access to the blockchain
// CREATED: 2021-01-17 @ 9:54 PM
// COPYRIGHT: Copyright (c) 2021 by Ryan Smith <rysmith2113@gmail.com>
//

#ifndef NODE_HPP
#define NODE_HPP

#include <string>
#include <stdexcept>
#include <utility>
#include <sstream>

#include "cryptopp-sha256-libs.h"

#include "transaction.hpp"

using std::string;
using std::pair;

#include <cryptopp/rsa.h> 	// Use Crypto++'s RSA functionality
#include <cryptopp/osrng.h> // Use AutoSeededRandomPool

using CryptoPP::RSA;

class Node {
	typedef CryptoPP::RandomNumberGenerator CRYPTOPP_RNG; // Make this long name a little easier to use

public:
	Node(string name, string username, string passwd, string ip, bool isMaster);
	Transaction MakeTransaction(Node& recipient, float amount, string content) const;

	// Some getters
	string GetName() const, GetUsrName() const, GetIP() const;

	pair<RSA::PublicKey, RSA::PrivateKey> GenerateKeys() noexcept(false);
	Transaction Sign(string hash), Verify(string hash);

private:
	string m_Name, m_Username, m_Password, m_IPAddr;

	RSA::PublicKey 	m_PubKey;
	RSA::PrivateKey m_PrivKey;

	bool isMaster;

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
	std::tie(m_PubKey, m_PrivKey) = GenerateKeys(); // Generate a set of RSA keys for the user
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
	CryptoPP::Integer n("0xbeaadb3d839f3b5f"), e("0x11"), d("0x21a5ae37b9959db9"); // Numbers used in the calculations
	CRYPTOPP_RNG rng = CRYPTOPP_RNG(); // A random number generator

	// Generate some RSA keys
	RSA::PrivateKey privKey;
	privKey.Initialize(n, e, d);

	RSA::PublicKey pubKey;
	pubKey.Initialize(n, e);

	// Validate the private key that was generated. If this key passes, the
	// public key does not need to be tested.
	if (!privKey.Validate(rng, 3)) {
		throw std::runtime_error("Private key validation failed. Aborting.");
	}

	return std::make_pair(pubKey, privKey);
}

// Sign a transaction (i.e., the transaction's hash) with the sender's private key
Block Node::Sign(Block& block) {
	// Get some data needed to apply the encryption function
	CryptoPP::Integer m((const CryptoPP::byte*)hash.c_str(), hash.size());

	// Convert the CryptoPP::Integer to a std::string
	std::stringstream stream;
	stream << std::hex << m_PubKey.ApplyFunction(m);

	string signedHash = stream.str(); // Get the stringstream as a string

	block.m_Signature = signedHash;
	return block;
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

#endif // NODE_HPP
