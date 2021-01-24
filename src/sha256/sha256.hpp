//
// FILENAME: sha256.h | Plasmacoin Cryptocurrency
// DESCRIPTION: Implement the SHA-256 hashing algorithm
// CREATED: 2021-01-23 @ 8:18 PM
// COPYRIGHT: Copyright (c) 2021 by Ryan Smith <rysmith2113@gmail.com>
//

#ifndef SHA256_HPP
#define SHA256_HPP

#include <string>
#include <ios>
#include <bitset>
#include <vector>

using std::string;
using std::bitset;
using std::vector;

#include "constants.h"

using std::string;

bitset<8> preprocessor(string text) {
	vector<bitset<8>> bytearray; // The byte array to return

	const int SIZE_IN_BITS = text.size() * 8;
	const int EXTRA_BIT = 1;

	//
    // The equation L + 1 + K + 64 is used to find the correct number of bits to append,
	// where:
	// * L is the length in bits of the text to encrypt
	// * K is the smallest number >= 0 that makes the equation a multiple of 512
	// * 1 is an extra bit that is always appended
	// * 64 is the set size in bits of appending L
	//
	int target = SIZE_IN_BITS + 1 + /* K */ + UINT64_WIDTH; // K must be solved for

    // Solve for K
    int k = 0;
    while (512 % (target + k) != 0) {
        k++;
    }

    target += k;

    bytearray.reserve(target); // Try to avoid some overhead

    // Convert the string to binary
    for (char c: text) {
        bytearray.push_back(bitset<8>(c));
    }

	// Pad the byte array
    bytearray.push_back(EXTRA_BIT); // Append a single bit
    bytearray.insert(bytearray.end(), k, 0); // Append K empty bits

    bytearray.push_back(static_cast<uint64_t>(text.size() * 8));
}

string sha256Encrypt(string text) {

}

#endif // SHA256_HPP