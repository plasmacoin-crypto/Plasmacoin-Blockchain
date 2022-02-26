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

#include "transaction.hpp"
#include "node.hpp"
#include "block.hpp"
#include "packet-types.h"
#include "receipt.hpp"

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

	void Transmit(const vector<string>& data, uint8_t type);

	// Functions to store class data in a format that can be converted into
	vector<string> Format(Transaction* transaction);
	vector<string> Format(Node* node);
	vector<string> Format(Block* block);
	vector<string> Format(Receipt* receipt);

private:
	vector<string> m_KnownHosts = {"192.168.1.44"};
};

#endif // TRANSMITTER_HPP