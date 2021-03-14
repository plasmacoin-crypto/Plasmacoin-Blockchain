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
#include <cryptopp/filters.h>	// Use SignerFilter, StringSink, SignatureVerificationFilter
#include <cryptopp/cryptlib.h> 	// Use GenerateRandomWithKeySize
#include <cryptopp/pssr.h>		// Use PSSR

using CryptoPP::RSA;
using CryptoPP::Integer;

class Node {
public:
	Node(string name, string username, string passwd, string ip, bool isMaster);
	Transaction MakeTransaction(Node& recipient, float amount, string content) const;

	// Some getters
	string GetName() const, GetUsrName() const, GetIP() const;

	pair<RSA::PublicKey, RSA::PrivateKey> GenerateKeys() noexcept(false);

	Block Sign(Block& block), Verify(Block& block, string signature);

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
	//Integer n("0xbeaadb3d839f3b5f"), e("0x11"), d("0x21a5ae37b9959db9"); // Numbers used in the calculations
	CryptoPP::AutoSeededRandomPool rng; // Random number generator
	CryptoPP::InvertibleRSAFunction params;

	params.GenerateRandomWithKeySize(rng, 3072);

	// Generate some RSA keys
	RSA::PrivateKey privKey(params);
	RSA::PublicKey pubKey(params);

	// Validate the private key that was generated. If this key passes, the
	// public key does not need to be tested.
	if (!privKey.Validate(rng, 3)) {
		throw std::runtime_error("Private key validation failed. Aborting.");
	}

	return std::make_pair(pubKey, privKey);
}

// Sign a transaction (i.e., the transaction's hash) with the sender's private key
Block Node::Sign(Block& block) {
	// Integer n("0xbeaadb3d839f3b5f"), e("0x11"), d("0x21a5ae37b9959db9"); // Numbers used in the calculations

	CryptoPP::AutoSeededRandomPool rng;

	string signature;
	CryptoPP::RSASS<CryptoPP::PSSR, CryptoPP::SHA256>::Signer signer(m_PrivKey);

	// Sign the transaction
	CryptoPP::StringSource ss1(block.m_Hash, true,
		new CryptoPP::SignerFilter(rng, signer,
			new CryptoPP::StringSink(signature), true
		) // SignerFilter
	); // StringSource

	block.m_SSignature = signature;

	return block;
}

// Verify a transaction with the sender's public key
Block Node::Verify(Block& block, string signature) {
	Integer n("0xbeaadb3d839f3b5f"), e("0x11"), d("0x21a5ae37b9959db9"); // Numbers used in the calculations

	CryptoPP::AutoSeededRandomPool rng;
	CryptoPP::InvertibleRSAFunction params;

	string recovered;
	CryptoPP::RSASS<CryptoPP::PSSR, CryptoPP::SHA256>::Verifier verifier(pubKey);

	// Verify the transaction
	CryptoPP::StringSource ss2(signature, true,
		new CryptoPP::SignatureVerificationFilter(
			verifier,
			new CryptoPP::StringSink(
            	recovered
			), // StringSink
			CryptoPP::SignatureVerificationFilter::PUT_MESSAGE |
			CryptoPP::SignatureVerificationFilter::SIGNATURE_AT_END
		) // SignatureVerificationFilter
	); // StringSource

	std::cout << "Result: " << recovered << std::endl;
	block.m_RSignature = recovered;

	return block;
}

// Use Crypto++ to hash the transaction data
string Node::Hash(Transaction transaction) {
	CryptoPP::SHA256 hash;
	string digest; // The result
	string message = transaction.m_Condensed;

	// Hash the transaction data
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
