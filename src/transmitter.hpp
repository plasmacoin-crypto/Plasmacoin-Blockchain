//
// FILENAME: transmitter.hpp | Plasmacoin Cryptocurrency
// DESCRIPTION: Transmit packets to propogate changes/updates throughout the network
// CREATED: 2022-01-04 @ 10:48 PM
// COPYRIGHT: Copyright (c) 2021 by Ryan Smith <rysmith2113@gmail.com>
//

#ifndef TRANSMITTER_HPP
#define TRANSMITTER_HPP

#include <string>
#include <vector>
#include <iterator>

#include <cryptopp/filters.h>	 	// Use StringSink
#include <cryptopp/queue.h>    	 	// Use ByteQueue
#include <cryptopp/cryptlib.h> 	 	// Use BufferedTransformation
#include <cryptopp/hex.h>		 	// Use HexEncoder
#include <cryptopp/secblock.h>	 	// Use CryptoPP::SecByteBlock

#include "packet-types.h"
#include "transaction.hpp"
#include "node.hpp"
#include "block.hpp"
#include "receipt.hpp"
#include "user-query.hpp"
#include "sync-request.hpp"
#include "bcdata.hpp"
#include "utility.hpp"
#include "idcode.hpp"
#include "removal-request.hpp"

namespace go {
	#include "pcnetworkd.h"
}

using std::vector;
using std::string;

class Node;

class Transmitter {
public:
	Transmitter();
	~Transmitter();

	void Transmit(const vector<string>& data, uint8_t type, const vector<string>& hosts = {});
	void Multicast(const vector<string>& data, uint8_t type, const string& host, uint16_t port);

	// Functions to store class data in a format that can be converted into
	vector<string> Format(IDCode* idCode);
	vector<string> Format(Transaction* transaction);
	vector<string> Format(Node* node, const string& senderIP, int16_t senderPort, bool shouldRegister = true);
	vector<string> Format(Block* block);
	vector<string> Format(Receipt* receipt);
	vector<string> Format(UserQuery* query);
	vector<string> Format(SyncRequest* request);
	vector<string> Format(PendingTransaction* pendingTrxn);
	vector<string> Format(RemovalRequest* remRequest);
};

#endif // TRANSMITTER_HPP