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

	Node* node1 = new Node("Ryan", "ryan", "1234", "192.168.1.6");
	Node* node2 = new Node("John", "john", "4567", "192.168.1.7");

	Transaction transaction = node1->MakeTransaction(*node2, 1.0, "Here's some money");

	Block block(1, nullptr, &transaction);

	std::cout << transaction.m_Content << std::endl;

	std::cout << chain->Consensus(block) << std::endl;
	std::cout << block.m_Hash << std::endl;

	//node1->GenerateKeys();
	block = node1->Sign(block);
	block = node2->Verify(block, block.m_SSignature);

	std::cout << "Signed: " << std::hex << block.m_SSignature << std::endl;
	std::cout << "Verified: " << std::hex << block.m_RSignature << std::endl;

	std::cout << (block.m_Hash == block.m_RSignature) << std::endl;

	return 0;
}
