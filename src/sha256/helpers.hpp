//
// FILENAME: helpers.h | Plasmacoin Cryptocurrency
// DESCRIPTION: Functions to aid the SHA-256 algorithm
// CREATED: 2021-01-23 @ 11:56 PM
// COPYRIGHT: Copyright (c) 2021 by Ryan Smith <rysmith2113@gmail.com>
//

#ifndef SHA256_HELPERS_H
#define SHA256_HELPERS_H

#include <string>
#include <bitset>
#include <vector>
#include <iostream>

using std::string;
using std::bitset;
using std::vector;

// Perform a circular right shift on a byte
bitset<8> rotateRight(bitset<8>& byte) {
	auto b0 = byte[0]; // Save the bit in the first position
	byte >>= 1; // Shift everything to the right
	byte[7] = b0; // Circle around the first bit

	return byte;
}

// Concatenate two bytes
int concat(int b1, int b2) {
    return (b1 << 8) | b2;
};

// Concatenate two 8-bit (1 byte) bitsets and return the
// result as a string
string strconcat(bitset<8> b1, bitset<8> b2) {
    uint64_t combined = (b1.to_ulong() << 8) | b2.to_ulong(); // Get the integer representation of the two bytes
	return bitset<16>(combined).to_string();
}

// Convert a byte array represented as a vector if 8-bit bitsets to a string
string stringify(vector<bitset<8>> bytearray) {
    vector<bitset<8>>::iterator iter;
    string bytestr = "";

    for (iter = bytearray.begin(); iter != bytearray.end(); iter++) {
        bytestr += strconcat(*iter, *(iter + 1));
    }

    return bytestr;
}



#endif // SHA256_HELPERS_H

