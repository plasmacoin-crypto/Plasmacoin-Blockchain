//
// FILENAME: node.cpp | Plasmacoin Cryptocurrency
// DESCRIPTION: The source file for node.hpp
// CREATED: 2021-03-31 @ 11:37 PM
// COPYRIGHT: Copyright (c) 2021 by Ryan Smith <rysmith2113@gmail.com>
//

#include "node.hpp"

Node::Node(
	const string& name, const string& username, const string& password, const string& ip,
	const string& keyPath, NodeType type
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
		std::tie(m_Keys, m_PublicKey, m_PrivateKey) = rsautil::generateKeys(); // Generate a set of RSA keys for the user
		rsafs::writeKeys(m_Keys, m_KeyPath);
	}
	else {
		rsafs::readKeys(m_PublicKey, m_PrivateKey, m_KeyPath);
	}

	datfs::createDataPath(); // Create a place to store blockchain data
	m_Address = CreateAddress(m_PublicKey); // Create the user's Plasmacoin address
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
Transaction* Node::MakeTransaction(const string& recipientAddr, double amount, double fee, const string& content) {
	Transaction* transaction = new Transaction(GetAddress(), recipientAddr, amount, fee, content);
	transaction->m_Hash = hashing::hash(*transaction);

	return transaction;
}

void Node::Distribute(Transaction* transaction) {
	// Node* recipient = new Node("", transaction->m_RecipientAddr);

	// Transmitter* transmitter = new Transmitter();
	// auto data = transmitter->Format(recipient, false);
	// transmitter->Transmit(data, std::stoi(data[0]));
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

NodeType Node::GetType() const {
	return m_NodeType;
}

void Node::SetType(NodeType type) {
	m_NodeType = type;
}

void Node::AddKnownHost(const string& host) {
	if (std::find(m_KnownHosts.begin(), m_KnownHosts.end(), host) != m_KnownHosts.end()) {
		m_KnownHosts.push_back(host);
	}
}

void Node::AddKnownHosts(std::vector<string>& hosts) {
	std::copy_if(hosts.begin(), hosts.end(), std::back_inserter(m_KnownHosts), [&hosts](const string& host) {
		return std::find(hosts.begin(), hosts.end(), host) == hosts.end();
	});
}

std::vector<string> Node::GetKnownHosts() const {
	return m_KnownHosts;
}

// A wrapper around rsautil::sign to sign transactions
void Node::Sign(Transaction& transaction) {
	rsautil::sign(transaction, m_PublicKey, m_PrivateKey);
}

// A wrapper around rsautil::sign to sign transaction receipts
void Node::Sign(Receipt& receipt) {
	rsautil::sign(receipt, m_PublicKey, m_PrivateKey);
}

string Node::CreateAddress(const RSA::PublicKey& pubKey) {
	string strPubKey;
	pubKey.Save(CryptoPP::StringSink(strPubKey).Ref());

	return hashing::RIPEMD160(hashing::hash(strPubKey));
}

void Node::SyncFromNetwork(const string& ip) {
	// Get a list of high-committment nodes' IP addresses
	Transmitter* transmitter = new Transmitter();
	UserQuery* query = new UserQuery{go::getLocalIP(), "full"};

	auto data = transmitter->Format(query);
	transmitter->Transmit(data, std::stoi(data[0]));

	string result = shared_mem::readMemory(true); // Read the shared memory
	std::cout << "Node Result: " << result << std::endl;

	delete transmitter;
	delete query;
}
