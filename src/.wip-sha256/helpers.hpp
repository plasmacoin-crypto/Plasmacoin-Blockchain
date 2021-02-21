//
// FILENAME: helpers.hpp | Plasmacoin Cryptocurrency
// DESCRIPTION: Functions to aid the SHA-256 algorithm
// CREATED: 2021-01-23 @ 11:56 PM
// COPYRIGHT: Copyright (c) 2021 by Ryan Smith <rysmith2113@gmail.com>
//

#ifndef SHA256_HELPERS_H
#define SHA256_HELPERS_H

#include <string>
#include <bitset>
#include <vector>
#include <array>
#include <cmath>
#include <iostream>

#include "constants.h"

using std::string;
using std::bitset;
using std::vector;
using std::array;

//
// ---[ Byte rotation and shifting ]---
//

// Perform a circular right shift `n` times on a byte
uint rotateRight(int byte, int n = 1) {
	// bitset<8> modByte = byte;
	// int i = 0;

	// while (i < n) {
	// 	bool b0 = modByte.test(0); // Save the bit in the first position

	// 	modByte >>= 1; 	 // Shift everything to the right
	// 	modByte[7] = b0; // Circle around the stored bit

	// 	i++;
	// }

	// return static_cast<int32_t>((modByte.to_ulong() & MOD);
	return ((byte >> n) | (byte << (32 - n)));
}

// Shift a byte `n` places to the right
int shiftRight(int byte, int n = 1) {
	return (byte >> n);
}

//
// ---[ Byte concatenation ]---
//

// Concatenate two bytes
bitset<8> concat(bitset<8> b1, bitset<8> b2) {
	return (b1 << 8) | b2;
}

// Concatenate two 8-bit (1 byte) bitsets and return the
// result as a string
string strconcat(bitset<8> b1, bitset<8> b2) {
	uint64_t combined = (b1.to_ulong() << 8) | b2.to_ulong(); // Get the integer representation of the two bytes
	return bitset<16>(combined).to_string();
}

//
// ---[ SHA-256 Logical Functions ]---
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
int choice(int x, int y, int z) {
	return ((x & y) ^ (~x & z));
}

// Implement Maj(X, Y, Z)
int majority(int x, int y, int z) {
	return ((x & y) ^ (x & z) ^ (y & z));
}

// Implement Σ_0(X)
int Sigma_0(int x) {
	return (rotateRight(x, 2) ^ rotateRight(x, 13) ^ rotateRight(x, 22));
}

// Implement Σ_1(X)
int Sigma_1(int x) {
	return (rotateRight(x, 6) ^ rotateRight(x, 11) ^ rotateRight(x, 25));
}

// Implement σ_0(X)
int sigma_0(int x) {
	return (rotateRight(x, 7) ^ rotateRight(x, 18) ^ shiftRight(x, 3));
}

// Implement σ_1(X)
int sigma_1(int x) {
	return (rotateRight(x, 17) ^ rotateRight(x, 19) ^ shiftRight(x, 10));
}

//
// ---[ Block decomposition functions ]---
//

// Assign a 512-bit chunk of data to a message schedule array. The chunk
// will contain 64 32-bit words.
array<int, 64> decompose(array<int, 16> data) {
	unsigned int i = 0, j = 0;
	array<int, 64> blocks;

	//while (i < data.size()) {
		while (j < blocks.size()) {
			if (j < 16) { // Blocks 1-16
				// Save the input to the array
				blocks[j] = data[j];
			}
			else { // Blocks 17-64
				// Calculate the remaining blocks using the following
				// formula:
				//
				//				1			   2			  3				 4
				// ---------------------------------------------------------------
				// W_i = σ_1(W_(i − 2)) + W_(i − 7) + σ_0(W_(i − 15)) + W_(i − 16)
				//
				// Where:
				// W is the new block being created
				// i is the index of the block
				// σ_0 and σ_1 are predefined functions to manipulate a block

				// A place to store string versions of bytes from the 32-bit
				// block that is currently being processed.
				int inp1, inp2, inp3, inp4;

				inp1 = sigma_1(blocks[j - 2]); 	// 1
				inp2 = blocks[j - 7];		  	// 2
				inp3 = sigma_0(blocks[j - 15]);	// 3
				inp4 = blocks[j - 16];			// 4

				blocks[j] = (inp1 + inp2 + inp3 + inp4) & MOD; // Add the next block
			}

			j++;
		}

		//i++;
	//}

	return blocks;
}

// Split a bytestring into 512-bit chunks. The data will be returned as
// a vector of 16-element arrays containing 32-bit bitsets.
auto split(string text) {
	int needed = ceilf(text.size() / 512.0); // Figure out how many 512-bit chunks need to be allocated

	vector<array<int, 16>> chunks;
	chunks.reserve(needed); // Avoid some overhead

	string textcpy = text;

	array<int, 16> chunk;

	for (int i = 0; i < needed; i++) {
		for (unsigned int j = 0; j < chunk.size(); j++) {
			if (!textcpy.empty()) {
				// Assign a 32-bit section of the input to the array
				chunk[j] = std::stoi(textcpy.substr(0, 32), nullptr, 2);
				textcpy.erase(0, 32);
			}
		}

		chunks.push_back(chunk); // Add the 512-bit chunk
	}

	std::cout << chunks.size() << std::endl;
	return chunks;
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