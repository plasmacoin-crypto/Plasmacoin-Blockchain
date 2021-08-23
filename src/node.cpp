//
// FILENAME: node.cpp | Plasmacoin Cryptocurrency
// DESCRIPTION: The source file for node.hpp
// CREATED: 2021-03-31 @ 11:37 PM
// COPYRIGHT: Copyright (c) 2021 by Ryan Smith <rysmith2113@gmail.com>
//

#include "node.hpp"

Node::Node(string name, string username, string passwd, string ip, bool isMaster):
	// User data
	m_Name(name),
	m_Username(username),
	m_Password(passwd),
	m_IPAddr(ip),
	isMaster(isMaster)
{
	if (!fs::exists(rsafs::RSA_PATH + "/pc_rsa_keys")) {
		std::tie(m_PubKey, m_PrivKey) = GenerateKeys(); // Generate a set of RSA keys for the user
		rsafs::writeKeys(m_Keys);
	}
	else {
		std::tie(m_PubKey, m_PrivKey) = rsafs::readKeys(m_Keys);
	}
}

Transaction Node::MakeTransaction(Node& recipient, float amount, string content) const {
	// From Transaction::m_Condensed:
	// <SENDER>: <AMOUNT> Plasmacoins to <RECIPIENT>; <NONCE>
	string condensed = this->GetUsrName() + ": " + std::to_string(amount) +
					   " Plasmacoins to " + recipient.GetUsrName() + "; 0"; // Use 0 as the starting nonce

	// A new transaction between the current user and another user in the
	// network.
	return Transaction(new Node(m_Name, m_Username, m_Password, m_IPAddr),
					   &recipient, content, amount, condensed);
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
	CryptoPP::AutoSeededRandomPool rng; // Random number generator
	CryptoPP::InvertibleRSAFunction params;

	params.GenerateRandomWithKeySize(rng, 3072);

	// Generate some RSA keys
	RSA::PrivateKey privKey(params);
	RSA::PublicKey pubKey(params);

	m_Keys = params;

	// Validate the private key that was generated. If this key passes, the
	// public key does not need to be tested.
	if (!privKey.Validate(rng, 3)) {
		throw std::runtime_error("Private key validation failed. Aborting.");
	}

	return std::make_pair(pubKey, privKey);
}

// Sign a transaction with the sender's private key. Return the signature, as well as its length.
std::tuple<byte*, size_t> Node::Sign(Transaction& transaction) noexcept(false) {
	CryptoPP::AutoSeededRandomPool rng;
	string message = transaction.m_Content;

	//string signature;
	m_Signer = CryptoPP::RSASS<CryptoPP::PKCS1v15, CryptoPP::SHA256>::Signer(m_Keys);

	byte* signature = new byte[m_Signer.MaxSignatureLength()];

	if (signature == nullptr) {
		throw std::runtime_error("Transaction signing failed. Aborting.");
	}

	size_t length = m_Signer.SignMessage(rng, (const byte*)message.c_str(), message.size(), signature);

	return std::make_tuple(signature, length);
}

// Verify a transaction using the sender's public key. Returns true if verification succeded,
// false otherwise.
bool Node::Verify(Transaction& transaction, byte* signature, size_t length, RSA::PublicKey publicKey) {
	CryptoPP::AutoSeededRandomPool rng;
	CryptoPP::InvertibleRSAFunction params;
	string message = transaction.m_Content;

	//string recovered;
	CryptoPP::RSASS<CryptoPP::PKCS1v15, CryptoPP::SHA256>::Verifier verifier(publicKey);

	bool result = verifier.VerifyMessage((const byte*)message.c_str(), message.length(), signature, length);

	delete[] signature;
	return result;
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
