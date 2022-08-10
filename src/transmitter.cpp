//
// FILENAME: transmitter.cpp | Plasmacoin Cryptocurrency
// DESCRIPTION: The source file for transmitter.h
// CREATED: 2022-01-04 @ 10:48 PM
// COPYRIGHT: Copyright (c) 2021 by Ryan Smith <rysmith2113@gmail.com>
//

#include "transmitter.hpp"

Transmitter::Transmitter() {}
Transmitter::~Transmitter() {}

void Transmitter::Transmit(const vector<string>& data, uint8_t type, const vector<string>& hosts) {
	const size_t SIZE = data.size();
	const char* carray[SIZE];

	// Copy the vector of strings to an array of const char*
	for (unsigned int i = 0; i < SIZE; i++) {
		carray[i] = data[i].c_str();
	}

	//
	// A slice is the closest thing to a dynamic list in Go, so convert the C array
	// to a Go slice. Through cgo, we can do this by creating an instance of the GoSlice
	// struct. In Go, a slice accepts an array, a size, and a capacity. We don't plan to
	// change the size, so the size will equal the capacity.
	//
	// Because we have to use cgo's "go-between" types, the sizes need to be converted to
	// type `GoInt` (`long long`)
	//

	switch (type) {
		case static_cast<uint8_t>(go::PacketTypes::TRANSACTION):
		case static_cast<uint8_t>(go::PacketTypes::BLOCK): {
			for (const std::string& ip: hosts) {
				go::GoSlice slice = {carray, static_cast<go::GoInt>(SIZE), static_cast<go::GoInt>(SIZE)};

				// Send the data to another node
				std::cout << "Sending to " << ip << std::endl;
				future<void> dial = std::async(&go::dial, "tcp", ip.c_str(), "8080", type, slice);
			}

			break;
		}

		case static_cast<uint8_t>(go::PacketTypes::NODE):
		case static_cast<uint8_t>(go::PacketTypes::USER_QUERY):
		case static_cast<uint8_t>(go::PacketTypes::REMOVAL_REQUEST): {
			go::GoSlice slice = {carray, static_cast<go::GoInt>(SIZE), static_cast<go::GoInt>(SIZE)};
			future<void> dial = std::async(&go::dial, "tcp", "192.168.1.44", "14400", type, slice);
			break;
		}

		case static_cast<uint8_t>(go::PacketTypes::RECEIPT): {
			go::GoSlice slice = {carray, static_cast<go::GoInt>(SIZE), static_cast<go::GoInt>(SIZE)};
			future<void> dial = std::async(&go::dial, "tcp", go::getLocalIP(), "8080", type, slice);
			break;
		}

		case static_cast<uint8_t>(go::PacketTypes::SYNC_REQUEST):
		case static_cast<uint8_t>(go::PacketTypes::PENDING_TRXN): {
			string ip = hosts[0];

			go::GoSlice slice = {carray, static_cast<go::GoInt>(SIZE), static_cast<go::GoInt>(SIZE)};
			future<void> dial = std::async(&go::dial, "tcp", ip.c_str(), "8080", type, slice);
			break;
		}

		default:
			break;
	}
}

vector<string> Transmitter::Format(IDCode* idCode) {
	return vector<string> {
		std::to_string(static_cast<uint8_t>(go::PacketTypes::ID_CODE)),
		std::to_string(idCode->m_Code)
	};
}

vector<string> Transmitter::Format(Transaction* transaction) {
	// Convert the signature to Base64
	string signature = utility::sbbToBase64(transaction->m_Signature.m_Signature);

	// Convert the CryptoPP::RSA::PublicKey to Base64
	string publicKey = utility::pubKeyToBase64(transaction->m_Signature.m_PublicKey);

	return vector<string> {
		std::to_string(static_cast<uint8_t>(go::PacketTypes::TRANSACTION)),
		transaction->m_SenderAddr,
		transaction->m_RecipientAddr,
		std::to_string(transaction->m_CreationTime),
		std::to_string(transaction->m_SignTime),
		std::to_string(transaction->m_Amount),
		std::to_string(transaction->m_Fee),
		transaction->m_Content,

		// Signature field
		signature,
		publicKey,
		std::to_string(transaction->m_Signature.m_Length),

		transaction->m_Hash
	};
}

vector<string> Transmitter::Format(Node* node, const string& senderIP, int16_t senderPort, bool shouldRegister) {
	return vector<string> {
		std::to_string(static_cast<uint8_t>(go::PacketTypes::NODE)),
		senderIP,
		std::to_string(senderPort),
		node->GetIP(),
		std::to_string(node->GetPort()),
		node->GetAddress(),
		std::to_string(static_cast<uint8_t>(node->GetType())),
		std::to_string(shouldRegister)
	};
}

vector<string> Transmitter::Format(Block* block) {
	vector<string> returnVec {
		std::to_string(static_cast<uint8_t>(go::PacketTypes::BLOCK)),
		std::to_string(block->m_Index),
		std::to_string(block->m_Difficulty),
		std::to_string(block->m_Nonce),
		block->m_Hash,
		block->m_PrevHash,
		block->m_MinerAddr,
		std::to_string(block->m_CreationTime),
		std::to_string(block->m_MineTime),
		std::to_string(block->m_IsGenesis)
	};

	for (auto trxn: block->m_Transactions) {
		auto trxnData = Format(trxn);
		std::copy(trxnData.begin(), trxnData.end(), std::back_inserter(returnVec));
	}

	return returnVec;
}

vector<string> Transmitter::Format(Receipt* receipt) {
	// Convert the signature to Base64
	string signature = utility::sbbToBase64(receipt->m_Signature.m_Signature);

	// Convert the CryptoPP::RSA::PublicKey to Base64
	string publicKey = utility::pubKeyToBase64(receipt->m_Signature.m_PublicKey);

	return vector<string> {
		std::to_string(static_cast<uint8_t>(go::PacketTypes::RECEIPT)),
		receipt->m_SenderAddr,
		receipt->m_RecipientAddr,
		std::to_string(receipt->m_TransactionTime),
		std::to_string(receipt->m_SignTime),
		std::to_string(receipt->m_Amount),
		std::to_string(receipt->m_Fee),

		// Signature field
		signature,
		publicKey,
		std::to_string(receipt->m_Signature.m_Length),

		receipt->m_Hash
	};
}

vector<string> Transmitter::Format(UserQuery* query) {
	return vector<string> {
		std::to_string(static_cast<uint8_t>(go::PacketTypes::USER_QUERY)),
		query->m_IPAddr,
		query->m_NodeType
	};
}

vector<string> Transmitter::Format(SyncRequest* request) {
	return vector<string> {
		std::to_string(static_cast<uint8_t>(go::PacketTypes::SYNC_REQUEST)),
		std::to_string(request->m_SyncType),
		request->m_Host
	};
}

vector<string> Transmitter::Format(PendingTransaction* pendingTrxn) {
	return vector<string> {
		std::to_string(static_cast<uint8_t>(go::PacketTypes::PENDING_TRXN)),
		std::to_string(pendingTrxn->m_Timestamp),
		pendingTrxn->m_Hash,
		std::to_string(pendingTrxn->m_Amount)
	};
}

vector<string> Transmitter::Format(RemovalRequest* remRequest) {
	return vector<string> {
		std::to_string(static_cast<uint8_t>(go::PacketTypes::REMOVAL_REQUEST)),
		remRequest->m_SenderIP
	};
}