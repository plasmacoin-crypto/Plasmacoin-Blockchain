//
// FILENAME: transmitter.hpp | Plasmacoin Cryptocurrency
// DESCRIPTION: Transmit packets to propogate changes/updates throughout the network
// CREATED: 2022-01-04 @ 10:48 PM
// COPYRIGHT: Copyright (c) 2021 by Ryan Smith <rysmith2113@gmail.com>
//

#include <string>
#include <vector>

#include <cryptopp/filters.h>	 	// Use StringSink
#include <cryptopp/queue.h>    	 	// Use ByteQueue
#include <cryptopp/cryptlib.h> 	 	// Use BufferedTransformation
#include <cryptopp/hex.h>		 	// Use HexEncoder
#include <cryptopp/secblock.h>	 	// Use CryptoPP::SecByteBlock

#include "address-book.h"
#include "transaction.hpp"
#include "node.hpp"
#include "block.hpp"

namespace go {
	#include "pcnetworkd.h"
}

using std::vector;
using std::string;

class Transmitter {
public:
	Transmitter(AddressBook* addressBook);
	~Transmitter();

	void Transmit(const vector<string>& data, uint8_t type);

	// Functions to store class data in a format that can be converted into
	vector<string> Format(Transaction* transaction);
	vector<string> Format(Node* node);
	vector<string> Format(Block* block);

private:
	AddressBook* m_AddressBook;

	vector<string> m_KnownHosts = {"192.168.1.44"};
};