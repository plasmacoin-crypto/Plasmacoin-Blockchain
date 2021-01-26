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
	bitset<8> byte = std::bitset<8>(35);
	std::cout << rotateRight(byte) << std::endl;
	std::cout << choice(1, 2, 3) << std::endl;

	return 0;
}