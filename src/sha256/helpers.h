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

string strconcat(bitset<8> b1, bitset<8> b2) {
	return ((b1 << 8) | b2).to_string();
}

#endif // SHA256_HELPERS_H

