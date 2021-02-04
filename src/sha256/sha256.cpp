//
// FILENAME: sha256.cpp | Plasmacoin Cryptocurrency
// DESCRIPTION: A source file to test the SHA-256 algorithm
// CREATED: 2021-01-25 @ 9:03 PM
// COPYRIGHT: Copyright (c) 2021 by Ryan Smith <rysmith2113@gmail.com>
//

#include <bitset>
#include <iostream>
#include <string>

#include "helpers.hpp"
#include "sha256.hpp"

int main() {
	// std::cout << bits.to_string();
	//std::cout << sha256Hash("abc");
	//auto arr = decompose(preprocess("abc"));
	for (auto item: split(preprocess("abc"))[0])
		std::cout << item << std::endl;

	// for (auto item: arr) {
	// 	std::cout << item << std::endl;
	// }

	return 0;
}