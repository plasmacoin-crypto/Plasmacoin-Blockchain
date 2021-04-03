//
// FILENAME: main.cpp | Plasmacoin Cryptocurrency
// DESCRIPTION: The source file for the blockchain
// CREATED: 2021-01-17 @ 9:37 PM
// COPYRIGHT: Copyright (c) 2021 by Ryan Smith <rysmith2113@gmail.com>
//

#include <iostream>

#include "node.hpp"
#include "blockchain.hpp"

int main() {
	Blockchain* chain = new Blockchain();

	Node* node1 = new Node("Ryan", "ryan", "1234", "192.168.1.6", false);
	Node* node2 = new Node("John", "john", "4567", "192.168.1.7", false);

	Transaction transaction = node1->MakeTransaction(*node2, 1.0, "Here's some money");

	transaction = node1->Sign(transaction);
	transaction = node2->Verify(transaction, transaction.m_SSignature);

	std::cout << "Signed: " << std::hex << transaction.m_SSignature << std::endl;
	std::cout << "Verified: " << std::hex << transaction.m_RSignature << std::endl;

	chain->AddToLedger(&transaction);

	std::cout << transaction.m_Content << std::endl;

	std::cout << chain->Mine() << std::endl;

	return 0;
}
