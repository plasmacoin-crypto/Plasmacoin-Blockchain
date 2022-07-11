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
#include <vector>
#include <iterator>

using std::string;

#include <QJsonObject>

#include "cryptopp-sha256-libs.h"

#include "transaction.hpp"
#include "block.hpp"
#include "blockchain.hpp"
#include "rsa-fs.hpp"
#include "dat-fs.hpp"
#include "packet-types.h"
#include "transmitter.hpp"
#include "shared-mem.hpp"
#include "utility.hpp"
#include "rsautil.hpp"
#include "hashing.hpp"
#include "enums.h"

using enums::NodeType;

namespace go {
	#include "pcnetworkd.h"
}

class Node {
public:
	Node(
		const string& name, const string& username, const string& password, const string& ip,
		const string& keyPath = rsafs::RSA_KEY_PATH, NodeType type = NodeType::LIGHT
	);
	Node(const string& ip, const string& address);
	~Node();

	Transaction* MakeTransaction(const string& recipientAddr, double amount, double fee, const string& content);
	void Distribute(Transaction* transaction);

	// Some getters
	string GetName() const, GetUsrName() const, GetIP() const, GetAddress() const;
	NodeType GetType() const;

	void SetType(NodeType type);

	std::vector<string> GetKnownHosts() const;
	void SetKnownHosts(std::vector<string>& hosts);

	void Sign(Transaction& transaction);
	void Sign(Receipt& receipt);

	Blockchain* m_BlockchainCopy = new Blockchain(); // The node's copy of the blockchain

	RSA::PublicKey m_PublicKey;

private:
	string CreateAddress(const RSA::PublicKey& pubKey);
	void SyncFromNetwork(const string& ip);

	string m_Name, m_Username, m_Password, m_IPAddr, m_KeyPath, m_Address;

	RSA::PrivateKey m_PrivateKey;
	NodeType m_NodeType;

	CryptoPP::RSASSA_PKCS1v15_SHA_Signer m_Signer;
	CryptoPP::InvertibleRSAFunction m_Keys;

	std::vector<string> m_KnownHosts;
};

#endif // NODE_HPP
