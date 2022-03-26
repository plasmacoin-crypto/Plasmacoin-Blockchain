//
// FILENAME: node.cpp | Plasmacoin Cryptocurrency
// DESCRIPTION: The source file for node.hpp
// CREATED: 2021-03-31 @ 11:37 PM
// COPYRIGHT: Copyright (c) 2021 by Ryan Smith <rysmith2113@gmail.com>
//

#include "node.hpp"

Node::Node(
	const string& name, const string& username, const string& password,
	const string& ip, const string& keyPath, Node::NodeType type
):
	// User data
	m_Name(name),
	m_Username(username),
	m_Password(password),
	m_IPAddr(ip),
	m_KeyPath(keyPath),
	m_NodeType(type)
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

	// Register that the node is online
	Transmitter* transmitter = new Transmitter();
	auto data = transmitter->Format(this);
	std::cout << data[0] << std::endl;
	transmitter->Transmit(data, std::stoi(data[0]));

	string result = shared_mem::readMemory(true); // Read the shared memory
	std::cout << "Node Result: " << result << std::endl;

	// Parse the JSON string
	QJsonObject object = json::parse(result);
	std::vector<string> m_KnownHosts = json::parseArray(object, "nodes");
	SetKnownHosts(m_KnownHosts);
}

Node::Node(const string& ip, const string& address):
	m_IPAddr(ip),
	m_Address(address)
{
	if (ip.empty()) {
		m_IPAddr = "";
	}

	if (address.empty()) {
		m_Address = "";
	}
}

Node::~Node() {
	delete m_BlockchainCopy;
}

// Create a new transaction to a recipient on the blockchain network
Transaction* Node::MakeTransaction(const string& recipientAddr, float amount, float fee, const string& content) {
	Transaction* transaction = new Transaction(GetAddress(), recipientAddr, amount, fee, content);
	transaction->m_Hash = Hash(*transaction);

	return transaction;
}

void Node::Distribute(Transaction* transaction) {
	Node* recipient = new Node("", transaction->m_RecipientAddr);

	Transmitter* transmitter = new Transmitter();
	auto data = transmitter->Format(recipient, false);
	transmitter->Transmit(data, std::stoi(data[0]));
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

Node::NodeType Node::GetType() const {
	return m_NodeType;
}

void Node::SetKnownHosts(std::vector<string>& hosts) {
	std::copy(m_KnownHosts.begin(), m_KnownHosts.end(), std::back_inserter(hosts));
}

std::vector<string> Node::GetKnownHosts() const {
	return m_KnownHosts;
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

// Sign a transaction with the sender's private key.
void Node::Sign(Transaction& transaction) noexcept(false) {
	CryptoPP::AutoSeededRandomPool rng;
	string message = transaction.m_Content;

	//string signature;
	m_Signer = CryptoPP::RSASSA_PKCS1v15_SHA_Signer(m_PrivKey);

	size_t length = m_Signer.MaxSignatureLength();
	CryptoPP::SecByteBlock signature(length);

	// if (signature == nullptr) {
	// 	throw std::runtime_error("Transaction signing failed. Aborting.");
	// }

	length = m_Signer.SignMessage(rng, (const byte*)message.c_str(), message.size(), signature);
	signature.resize(length);

	transaction.m_Signature = Signature {signature, m_PubKey, length};
	transaction.m_SignTime = utility::getUTCTime();
}

void Node::Sign(Receipt& receipt) noexcept(false) {
	CryptoPP::AutoSeededRandomPool rng;
	string message = receipt.m_Hash;

	//string signature;
	m_Signer = CryptoPP::RSASSA_PKCS1v15_SHA_Signer(m_PrivKey);

	size_t length = m_Signer.MaxSignatureLength();
	CryptoPP::SecByteBlock signature(length);

	// if (signature == nullptr) {
	// 	throw std::runtime_error("Transaction signing failed. Aborting.");
	// }

	length = m_Signer.SignMessage(rng, (const byte*)message.c_str(), message.size(), signature);
	signature.resize(length);

	receipt.m_Signature = Signature {signature, m_PubKey, length};
	receipt.m_SignTime = utility::getUTCTime();
}

// Verify a transaction using the sender's public key. Returns true if verification succeded,
// false otherwise.
bool Node::Verify(const Transaction& transaction, const SecByteBlock& signature, size_t length, const RSA::PublicKey& publicKey) {
	CryptoPP::AutoSeededRandomPool rng;
	CryptoPP::InvertibleRSAFunction params;
	string message = transaction.m_Content;

	//string recovered;
	CryptoPP::RSASS<CryptoPP::PKCS1v15, CryptoPP::SHA256>::Verifier verifier(publicKey);

	bool result = verifier.VerifyMessage((const byte*)message.c_str(), message.length(), signature, length);
	return result;
}

// Use Crypto++ to hash a string
string Node::Hash(const string& input) const {
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
string Node::Hash(const Transaction& transaction) const {
	string message = transaction.m_SenderAddr + transaction.m_RecipientAddr + \
					 std::to_string(transaction.m_Amount + transaction.m_Fee) + \
					 transaction.m_Content;

	return Hash(message);
}

string Node::RIPEMD160(const string& input) const {
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
