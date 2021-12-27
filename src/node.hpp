//
// FILENAME: node.hpp | Plasmacoin Cryptocurrency
// DESCRIPTION: A computer (user) that has access to the blockchain
// CREATED: 2021-01-17 @ 9:54 PM
// COPYRIGHT: Copyright (c) 2021 by Ryan Smith <rysmith2113@gmail.com>
//

#ifndef NODE_HPP
#define NODE_HPP

#include <iostream>
#include <string>
#include <utility>
#include <sstream>
#include <functional>

#include "cryptopp-sha256-libs.h"

#include "transaction.hpp"
#include "block.hpp"
#include "blockchain.hpp"
#include "rsa-fs.hpp"
#include "dat-fs.hpp"

using std::string;
using std::pair;

#include <cryptopp/rsa.h> 		// Use Crypto++'s RSA functionality
#include <cryptopp/osrng.h> 	// Use AutoSeededRandomPool
#include <cryptopp/filters.h>	// Use SignerFilter, StringSink, SignatureVerificationFilter
#include <cryptopp/cryptlib.h> 	// Use GenerateRandomWithKeySize
#include <cryptopp/pssr.h>		// Use PSSR
#include <cryptopp/ripemd.h>	// Use the RIPEMD hash function

using CryptoPP::RSA;
using CryptoPP::Integer;
using CryptoPP::byte;

class Node {
public:
	enum class NodeType: uint8_t {LIGHT = 0, FULL, MINING};

	Node(
		const string& name, const string& username, const string& password,
		const string& ip, const string& keyPath = rsafs::DIR_PATH, Node::NodeType type = NodeType::LIGHT
	);
	~Node();

	Transaction* MakeTransaction(const string& recipientAddr, float amount, float fee, const string& content) const;

	// Some getters
	string GetName() const, GetUsrName() const, GetIP() const, GetAddress() const;

	pair<RSA::PublicKey, RSA::PrivateKey> GenerateKeys() noexcept(false);

	// Sign and verify transactions with RSA
	void Sign(Transaction& transaction) noexcept(false);
	bool Verify(const Transaction& transaction, byte* signature, size_t length, const RSA::PublicKey& publicKey);

	Blockchain* m_BlockchainCopy = new Blockchain(); // The node's copy of the blockchain

	RSA::PublicKey m_PubKey;

private:
	string Hash(const string& input) const;
	string Hash(const Transaction& transaction) const;
	string RIPEMD160(const string& input) const;

	string CreateAddress(const RSA::PublicKey& pubKey);

	string m_Name, m_Username, m_Password, m_IPAddr, m_KeyPath, m_Address;
	RSA::PrivateKey m_PrivKey;
	NodeType m_NodeType;

	CryptoPP::RSASS<CryptoPP::PKCS1v15, CryptoPP::SHA256>::Signer m_Signer;
	CryptoPP::InvertibleRSAFunction m_Keys;
};

#endif // NODE_HPP
