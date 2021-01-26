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

//
// ---[ Byte rotation and shifting ]---
//

// Perform a circular right shift `n` times on a byte
bitset<8> rotateRight(bitset<8> byte, int n = 1) {
	bitset<8> modByte = byte;
	auto b0 = bitset<8>()[0]; // Give an initial value
	int i = 0;

	while (i < n) {
		b0 = modByte[0]; // Save the bit in the first position

		modByte >>= 1; 	 // Shift everything to the right
		modByte[7] = b0; // Circle around the first bit

		i++;
	}

	return modByte;
}

// Shift a byte `n` places to the right
bitset<8> shiftRight(bitset<8>& byte, int n = 1) {
	return byte >> n;
}

//
// ---[ Byte concatenation ]---
//

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

//
// ---[ Functions needed to help calculate the SHA-256 hash ]---
//

//
// For definitions of the following functions, see the PDF available from craft-crypto.com.
//
// Article (contains download link):
// https://craft-crypto.com/how-does-sha-256-work/
//
// Download Link:
// https://www.researchgate.net/file.PostFileLoader.html?id=534b393ad3df3e04508b45ad&assetKey=AS%3A273514844622849%401442222429260
//

// Implement Ch(X, Y, Z)
bitset<8> choice(bitset<8> x, bitset<8> y, bitset<8> z) {
	return ((x & y) ^ (~x & z));
}

// Implement Maj(X, Y, Z)
bitset<8> majority(bitset<8> x, bitset<8> y, bitset<8> z) {
	return ((x & y) | (x & z) | (y & z));
}

// Implement Σ_0(X)
bitset<8> Sigma_0(bitset<8> x) {
	return (rotateRight(x, 2) | rotateRight(x, 13) | rotateRight(x, 22));
}

// Implement Σ_1(X)
bitset<8> Sigma_1(bitset<8> x) {
	return (rotateRight(x, 6) | rotateRight(x, 11) | rotateRight(x, 25));
}

// Implement σ_0(X)
bitset<8> sigma_0(bitset<8> x) {
	return (rotateRight(x, 7) | rotateRight(x, 18) | shiftRight(x, 3));
}

// Implement σ_1(X)
bitset<8> sigma_1(bitset<8> x) {
	return (rotateRight(x, 17) | rotateRight(x, 19) | shiftRight(x, 10));
}

//
// ---[ Other ]---
//

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

