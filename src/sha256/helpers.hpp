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

using std::string;
using std::bitset;

// Concatenate two bytes
int concat(int b1, int b2) {
    return (b1 << 8) | b2;
};

// Concatenate two 8-bit (1 byte) bitsets and return the
// result as a string
string strconcat(bitset<8> b1, bitset<8> b2) {
    ulong combo = (b1.to_ulong() << 8) | b2.to_ulong();
	return bitset<16>(combo).to_string();
}

#endif // SHA256_HELPERS_H

