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

using std::string;
using std::bitset;
using std::vector;
using std::array;

#define MOD_ADD static_cast<int>(pow(2, 32))

//
// ---[ Byte rotation and shifting ]---
//

// Perform a circular right shift `n` times on a byte
bitset<8> rotateRight(bitset<8> byte, int n = 1) {
	bitset<8> modByte = byte;
	int i = 0;

	while (i < n) {
		bool b0 = modByte.test(0); // Save the bit in the first position

		modByte >>= 1; 	 // Shift everything to the right
		modByte[7] = b0; // Circle around the stored bit

		i++;
	}

	return bitset<8>(modByte.to_ulong() % MOD_ADD);
}

// Shift a byte `n` places to the right
bitset<8> shiftRight(bitset<8> byte, int n = 1) {
	return bitset<8>((byte >> n).to_ulong() % MOD_ADD);
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
// ---[ Block decomposition functions ]---
//

// Assign a 512-bit chunk of data to a message schedule array. The chunk
// will be split into 32-bit blocks (or words) across 64 elements, which
// will account for all 512 bits (32 * 16 = 512).
array<bitset<32>, 64> decompose(string data) {
	unsigned int i = 0, j = 0;
	string datacpy = data;
	array<bitset<32>, 64> blocks;

	//while (i < data.size()) {
		while (j < 63) {
			if (j < 16) { // Chunks 1-16
				// Save a 32-bit chink of data to the array
				blocks[j] = bitset<32>(datacpy.substr(0, 32));
				std::cout << datacpy.substr(0, 32);
				datacpy.erase(0, 32); // Will erase indices 0-31 (Interval notation: [0, 32))
			}
			else { // Chunks 17-63
				// Calculate the remaining chunks using the following
				// formula:
				//
				// W_i = σ_1(W_(i − 2)) + W_(i − 7) + σ_0(W_(i − 15)) + W_(i − 16)
				//
				string blockstr = "";

				// A place to store string versions of bytes from the 32-bit
				// block that is currently being processed.
				string inp1, inp2, inp3, inp4;

				// Process the 32 bits in chunks of 8 bits (1 byte) each
				for (unsigned int k = 0; k < blocks[j].size(); k += 8) {
					// std::out_of_range thrown here
					inp1 = sigma_1(bitset<8>(blocks[j - 2].to_string().substr(k, 8))).to_string();
					inp2 = blocks[j - 7].to_string().substr(k, 8);
					inp3 = sigma_0(bitset<8>(blocks[j - 15].to_string().substr(k, 8))).to_string();
					inp4 = blocks[j - 16].to_string().substr(k, 8);

					//
					// Each access of the vector will get the bytes from
					// j to j + 7 upper-bound exclusive (i.e., [j, j + 7) in
					// interval notation).
					//
					// 4 total bytes will be processed:
					// indices [0, 8), [8, 16), [16, 24), and [24, 32)
					//
					blockstr += (inp1 + inp2 + inp3 + inp4);
				}

				blocks[j] = bitset<32>(bitset<32>(blockstr).to_ulong() % MOD_ADD); // Add the string as a 32-bit bitset
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
	// Figure out how many 512-bit chunks need to be allocated
	// Formulas from: https://www.movable-type.co.uk/scripts/sha256.html
	int length = (text.size() / 4) + 2;
	int needed = ceilf(length / 16);

	vector<array<bitset<32>, 16>> chunks;
	chunks.reserve(needed); // Hopefully save some overhead

	//bitset<32> chunks[needed][16];
	//std::cout << sizeof(chunks);

	string textcpy = text;

	for (int i = 0; i < needed; i++) {
		for (unsigned int j = 0; j < chunks[i].size(); j++) {
			if (!textcpy.empty()) {
				chunks[i][j] = bitset<32>(textcpy.substr(0, 32));
				textcpy.erase(0, 32);
			}
		}
	}

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
