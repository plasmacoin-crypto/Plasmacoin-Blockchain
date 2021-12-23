//
// FILENAME: node.cpp | Plasmacoin Cryptocurrency
// DESCRIPTION: The source file for node.hpp
// CREATED: 2021-03-31 @ 11:37 PM
// COPYRIGHT: Copyright (c) 2021 by Ryan Smith <rysmith2113@gmail.com>
//

#include "node.hpp"

Node::Node(
	const string& name, const string& username, const string& password,
	const string& ip, const string& keyPath, bool isMaster
):
	// User data
	m_Name(name),
	m_Username(username),
	m_Password(password),
	m_IPAddr(ip),
	m_KeyPath(keyPath),
	isMaster(isMaster)
{
	if (!rsafs::pathOkay(m_KeyPath + rsafs::PUB_FILENAME) && !rsafs::pathOkay(m_KeyPath + rsafs::PRIV_FILENAME)) {
		std::tie(m_PubKey, m_PrivKey) = GenerateKeys(); // Generate a set of RSA keys for the user
		rsafs::writeKeys(m_Keys, m_KeyPath);
	}
	else {
		rsafs::readKeys(m_PubKey, m_PrivKey, m_KeyPath);
	}

	datfs::createDataPath(); // Create a place to store blockchain data

	m_Address = CreateAddress(m_PubKey);
}

Node::~Node() {
	delete m_BlockchainCopy;
}

// Create a new transaction to a recipient on the blockchain network
Transaction* Node::MakeTransaction(const Node& recipient, float amount, const string& content) const {
	// From Transaction::m_Condensed:
	// <SENDER_ADDR> -> <RECIEVER_ADDR> : <AMOUNT>
	string condensed = this->GetAddress() + " -> " + recipient.GetAddress() + " : " + std::to_string(amount);

	// A new transaction between the current user and another user in the
	// network.
	return new Transaction(this, &recipient, content, amount, condensed);
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

string Node::GetAddress() const {
	return m_Address;
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
pair<byte*, size_t> Node::Sign(const Transaction& transaction) noexcept(false) {
	CryptoPP::AutoSeededRandomPool rng;
	string message = transaction.m_Content;

	//string signature;
	m_Signer = CryptoPP::RSASS<CryptoPP::PKCS1v15, CryptoPP::SHA256>::Signer(m_PrivKey);

	byte* signature = new byte[m_Signer.MaxSignatureLength()];

	if (signature == nullptr) {
		throw std::runtime_error("Transaction signing failed. Aborting.");
	}

	size_t length = m_Signer.SignMessage(rng, (const byte*)message.c_str(), message.size(), signature);

	return std::make_pair(signature, length);
}

// Verify a transaction using the sender's public key. Returns true if verification succeded,
// false otherwise.
bool Node::Verify(const Transaction& transaction, byte* signature, size_t length, const RSA::PublicKey& publicKey) {
	CryptoPP::AutoSeededRandomPool rng;
	CryptoPP::InvertibleRSAFunction params;
	string message = transaction.m_Content;

	//string recovered;
	CryptoPP::RSASS<CryptoPP::PKCS1v15, CryptoPP::SHA256>::Verifier verifier(publicKey);

	bool result = verifier.VerifyMessage((const byte*)message.c_str(), message.length(), signature, length);

	delete[] signature;
	return result;
}

// Use Crypto++ to hash a string
string Node::Hash(const string& input) {
	CryptoPP::SHA256 hash;
	string digest; // The result

	// Use the library
	//
	// No objects have to be freed because of Crypto++'s pipelining
	// functionality
	//
	CryptoPP::StringSource ssource(input, true,
		new CryptoPP::HashFilter(hash,
			new CryptoPP::HexEncoder(
				new CryptoPP::StringSink(digest)
			)
		)
	);

	return digest;
}

// Use Crypto++ to hash the transaction data
string Node::Hash(const Transaction& transaction) {
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

string Node::RIPEMD160(const string& input) {
	CryptoPP::RIPEMD160 hash;
	string digest; // The result

	// Hash the transaction data
	//
	// No objects have to be freed because of Crypto++'s pipelining
	// functionality
	//
	CryptoPP::StringSource ssource(input, true,
		new CryptoPP::HashFilter(hash,
			new CryptoPP::HexEncoder(
				new CryptoPP::StringSink(digest)
			)
		)
	);

	return digest;
}

string Node::CreateAddress(const RSA::PublicKey& pubKey) {
	string strPubKey;
	pubKey.Save(CryptoPP::StringSink(strPubKey).Ref());

	return RIPEMD160(Hash(strPubKey));
}
