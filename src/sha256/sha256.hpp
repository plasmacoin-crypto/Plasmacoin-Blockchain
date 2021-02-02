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
#include <array>
#include <cassert>
#include <cstring>

#include "constants.h"
#include "helpers.hpp"

using std::string;
using std::bitset;
using std::vector;
using std::array;

// This will ensure the name is the same on all compilers
#define UINT64_SIZE 64

string preprocess(string text) {
	// The padded string to return. The size will be some multiple of 512.
	string padded = "";

	const int SIZE_IN_BITS = text.size() * 8;
	const char EXTRA_BIT = '1';

	//
    // The equation L + 1 + K + 64 is used to find the correct number of bits to append,
	// where:
	// * L is the length in bits of the text to encrypt
	// * K is the smallest number >= 0 that makes the equation a multiple of 512
	// * 1 is an extra bit that is always appended
	// * 64 is the set size in bits of appending L
	//
	uint64_t target = SIZE_IN_BITS + 1 + /* K */ + UINT64_SIZE; // K must be solved for

    // Solve for K
    int k = 0;
    while (512 % (target + k) != 0) {
        ++k;
    }

    target += k;


    // Store the string to binary
    for (char c: text) {
        padded += bitset<8>(c).to_string();
    }

	// Pad the byte array
    padded += EXTRA_BIT; // Append a single bit
    padded.insert(padded.end(), k, '0'); // Append K empty bits
    padded += bitset<UINT64_SIZE>(static_cast<uint64_t>(SIZE_IN_BITS)).to_string(); // Append the data size

    assert(padded.size() == target); // Make sure everything was padded correctly
    assert(512 % padded.size() == 0); // Make sure the padded word's size in bits is a multiple of 512

    return padded;
}

string sha256Encrypt(string text) {
    string data = preprocess(text);

    vector<bitset<512>> chunks;
    array<bitset<32>, 64> blocks;

    // Make a mutable copy of the root hashes
    uint32_t hashes[8];
    std::memcpy(hashes, ROOT_HASHES, sizeof(ROOT_HASHES));

    // Initialize working varibales
    uint32_t a = hashes[0],
             b = hashes[1],
             c = hashes[2],
             d = hashes[3],
             e = hashes[4],
             f = hashes[5],
             g = hashes[6],
             h = hashes[7];

    int i = 0;
    bitset<8> temp1, temp2;

    chunks = split(data);

    for (auto chunk: chunks) {
        blocks = decompose(chunk.to_string()); // Block decomposition

        for (auto block: blocks) {
            std::cout << block << std::endl;
        }

        // Set the working variables to the current hash value
        a = hashes[0],
        b = hashes[1],
        c = hashes[2],
        d = hashes[3],
        e = hashes[4],
        f = hashes[5],
        g = hashes[6],
        h = hashes[7];

        // Compression functionality
        while (i < 63) {
            temp1 = bitset<8>((h + Sigma_1(e).to_ulong() + choice(e, f, g).to_ulong() + CUBES_OF_PRIMES[i] + blocks[i].to_ulong()) % MOD_ADD);
            temp2 = bitset<8>((Sigma_0(a).to_ulong() + majority(a, b, c).to_ulong()) % MOD_ADD);

            // Reassign the working variables
            h = g;
            g = f;
            f = e;
            e = (d + temp1.to_ulong()) % MOD_ADD;
            d = c;
            c = b;
            b = a;
            a = (temp1.to_ulong() + temp2.to_ulong()) % MOD_ADD;

            i++;
        }

        // Add the compressed chunk to the current hashes
        hashes[0] += a;
        hashes[1] += b;
        hashes[2] += c;
        hashes[3] += d;
        hashes[4] += e;
        hashes[5] += f;
        hashes[6] += g;
        hashes[7] += h;
    }

    string hash = "";

    // Compute the hash by concatenating all of the root hashes
    for (ulong i = 0; i < sizeof(ROOT_HASHES); i += 2) {
        hash += concat(ROOT_HASHES[i], ROOT_HASHES[i + 1]).to_string();
    }

    return hash;
}

#endif // SHA256_HPP
