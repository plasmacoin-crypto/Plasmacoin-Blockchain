//
// FILENAME: main.cpp | Plasmacoin Cryptocurrency
// DESCRIPTION: The source file for the blockchain
// CREATED: 2020-01-18 @ 9:37 PM
// COPYRIGHT: Copyright (c) 2021 by Ryan Smith <rysmith2113@gmail.com>
//

#include <iostream>

#include "node.hpp"

int main() {
	Node* node1 = new Node("Ryan", "ryan", "1234", "192.168.1.6");
	Node* node2 = new Node("John", "john", "4567", "192.168.1.7");

	Transaction transaction = node1->MakeTransaction(*node2, 1.0, "Here's some money");

	std::cout << transaction.m_Content << std::endl;

	return 0;
}
