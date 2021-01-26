//
// FILENAME: sha256.cpp | Plasmacoin Cryptocurrency
// DESCRIPTION: A source file to test the SHA-256 algorithm
// CREATED: 2021-01-25 @ 9:03 PM
// COPYRIGHT: Copyright (c) 2021 by Ryan Smith <rysmith2113@gmail.com>
//

#include <bitset>
#include <iostream>

#include "helpers.hpp"

int main() {
	bitset<8> byte = std::bitset<8>(12);
	std::cout << byte << std::endl;
	std::cout << "\n" << rotateRight(byte, 3) << std::endl;
	//std::cout << choice(bitset<8>(2), bitset<8>(2), bitset<8>(3)) << std::endl;

	return 0;
}