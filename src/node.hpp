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
#include <tuple>

#include "cryptopp-sha256-libs.h"

#include "transaction.hpp"
#include "block.hpp"
#include "blockchain.hpp"
#include "rsa-fs.hpp"

using std::string;
using std::pair;

#include <cryptopp/rsa.h> 		// Use Crypto++'s RSA functionality
#include <cryptopp/osrng.h> 	// Use AutoSeededRandomPool
#include <cryptopp/filters.h>	// Use SignerFilter, StringSink, SignatureVerificationFilter
#include <cryptopp/cryptlib.h> 	// Use GenerateRandomWithKeySize
#include <cryptopp/pssr.h>		// Use PSSR

using CryptoPP::RSA;
using CryptoPP::Integer;
using CryptoPP::byte;

class Node {
public:
	Node(string name, string username, string passwd, string ip, bool isMaster = false);
	Transaction MakeTransaction(Node& recipient, float amount, string content) const;

	// Some getters
	string GetName() const, GetUsrName() const, GetIP() const;

	pair<RSA::PublicKey, RSA::PrivateKey> GenerateKeys() noexcept(false);

	// Sign and verify transactions with RSA
	std::tuple<byte*, size_t> Sign(Transaction& transaction) noexcept(false);
	bool Verify(Transaction& transaction, byte* signature, size_t length, RSA::PublicKey publicKey);

	Blockchain* m_BlockchainCopy = new Blockchain(); // The node's copy of the blockchain

	RSA::PublicKey m_PubKey;

private:
	string Hash(Transaction transaction);

	string m_Name, m_Username, m_Password, m_IPAddr;
	RSA::PrivateKey m_PrivKey;

	CryptoPP::RSASS<CryptoPP::PKCS1v15, CryptoPP::SHA256>::Signer m_Signer;
	CryptoPP::InvertibleRSAFunction m_Keys;

	bool isMaster;
};

#endif // NODE_HPP
