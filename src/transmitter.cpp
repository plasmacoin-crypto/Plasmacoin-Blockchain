//
// FILENAME: transmitter.cpp | Plasmacoin Cryptocurrency
// DESCRIPTION: The source file for transmitter.h
// CREATED: 2022-01-04 @ 10:48 PM
// COPYRIGHT: Copyright (c) 2021 by Ryan Smith <rysmith2113@gmail.com>
//

#include "transmitter.hpp"

Transmitter::Transmitter() {}
Transmitter::~Transmitter() {}

void Transmitter::Transmit(const std::vector<std::string>& data, uint8_t type) {
	const size_t SIZE = data.size();
	const char* carray[SIZE];

	// Copy the vector of strings to an array of const char*
	for (unsigned int i = 0; i < SIZE; i++) {
		carray[i] = data[i].c_str();
	}

	switch (type) {
		case static_cast<uint8_t>(go::PacketTypes::NODE): {
			go::GoSlice slice = {carray, static_cast<go::GoInt>(SIZE), static_cast<go::GoInt>(SIZE)};
			future<void> dial = std::async(&go::dial, "tcp", "192.168.1.44", "14400", type, slice);
			break;
		}

		case static_cast<uint8_t>(go::PacketTypes::TRANSACTION): {
			for (auto ip: m_KnownHosts) {
				//
				// A slice is the closest thing to a dynamic list in Go, so convert the C array
				// to a Go slice. Through cgo, we can do this by creating an instance of the GoSlice
				// struct. In Go, a slice accepts an array, a size, and a capacity. We don't plan to
				// change the size, so the size will equal the capacity.
				//
				// Because we have to use cgo's "go-between" types, the sizes need to be converted to
				// type `GoInt` (a typedef for `long long`)
				//
				go::GoSlice slice = {carray, static_cast<go::GoInt>(SIZE), static_cast<go::GoInt>(SIZE)};

				// Send the data to another node
				future<void> dial = std::async(&go::dial, "tcp", ip.c_str(), "8080", type, slice);
			}

			break;
		}

		default:
			break;
	}
}

vector<string> Transmitter::Format(Transaction* transaction) {
	// Convert the signature to a std::string
	CryptoPP::SecByteBlock sig = transaction->m_Signature.m_Signature;
	string signature = string(reinterpret_cast<const char*>(&sig[0]), sig.size());

	// Convert the CryptoPP::RSA::PublicKey to a std::string
	string publicKey;
	CryptoPP::HexEncoder keyEncoder;
	keyEncoder.Attach(new CryptoPP::StringSink(publicKey));

	CryptoPP::ByteQueue queue;
	transaction->m_Signature.m_PublicKey.Save(queue);
	queue.CopyTo(keyEncoder);

    keyEncoder.MessageEnd();

	return vector<string> {
		std::to_string(static_cast<uint8_t>(go::PacketTypes::TRANSACTION)),
		transaction->m_SenderAddr,
		transaction->m_RecipientAddr,
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

vector<string> Transmitter::Format(Node* node) {
	return vector<string> {
		std::to_string(static_cast<uint8_t>(go::PacketTypes::NODE)),
		node->GetIP(),
		node->GetAddress(),
		std::to_string(static_cast<uint8_t>(node->GetType()))
	};
}

vector<string> Transmitter::Format(Block* block) {}