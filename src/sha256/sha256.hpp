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
#include <cmath>

#include "constants.h"
#include "helpers.hpp"

using std::string;
using std::bitset;
using std::vector;
using std::array;

string preprocess(string text) {
	// The padded string to return. The resulting length will be some multiple of
	// 512, or in the case of a multi-block result, some length `l` where `l % 512 = 0`.
	string padded = "";

	const int SIZE_IN_BITS = text.size() * 8; // The size of the input string in bits
	const char EXTRA_BIT = '1';

	// Use a larger, non-constant final padding size instead of 448 when the input
    // requires
	const int BLOCK_NUM = (SIZE_IN_BITS == 448)? 2 : static_cast<int>(ceilf(SIZE_IN_BITS / 448.0F));
	const int K = ((SIZE_IN_BITS >= 448)? ((512 * BLOCK_NUM) - UINT64_SIZE) : 448 /* 448 mod 512 */) - (SIZE_IN_BITS + 1);

	//
	// The equation L + 1 + K + 64 is used to find the correct total number of bits to append,
	// where:
	// * L is the length in bits of the text to encrypt
	// * K is the smallest number >= 0 that makes the equation a multiple of 512
	// * 1 is an extra bit that is always appended
	// * 64 is the set size in bits of the number L
	//
    //const uint64_t TARGET = SIZE_IN_BITS + 1 + K + UINT64_SIZE;

    // Store the string to binary
    for (char c: text) {
        padded += bitset<8>(c).to_string();
    }

	// Pad the byte array
    padded += EXTRA_BIT; // Append a single bit

    padded.insert(padded.end(), K, '0'); // Append K empty (0) bits

    // Only single-block inputs (or the last of a multi-block input)
    // will have the final 64 bits on the end.
    padded += bitset<UINT64_SIZE>(static_cast<uint64_t>(SIZE_IN_BITS)).to_string(); // Append the data size

    //assert(padded.size() == TARGET); // Make sure everything was padded correctly
    //assert(512 % padded.size() == 0); // Make sure the padded word's size in bits is a multiple of 512

    return padded;
}

string sha256Hash(string text) {
    string padded = preprocess(text);

    array<bitset<32>, 64> schedule;

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

    std::cout << padded << std::endl;
    auto chunks = split(padded);

    // for (unsigned int i = 0; i < chunks.size(); i++) {
    //     for (unsigned int j = 0; j < chunks[i].size(); j++) {
    //         std::cout << chunks[i][j] << std::endl;
    //     }
    // }

    std::cout << chunks.size() << std::endl;
    //exit(0); // For testing purposes
    for (unsigned int i = 0; i < chunks.size(); i++) {
        schedule = decompose(chunks[i]);

        for (auto block: schedule) {
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
        
        int j = 0;
        unsigned long temp1, temp2;

        // Compression functionality
        while (j < 1) {
            temp1 = (h + Sigma_1(e) + choice(e, f, g) + CUBES_OF_PRIMES[j] + schedule[j].to_ulong()) % MOD_ADD;
            temp2 = (Sigma_0(a) + majority(a, b, c)) % MOD_ADD;

            // Reassign the working variables
            h = g;
            g = f;
            f = e;
            e = (d + temp1) % MOD_ADD;
            d = c;
            c = b;
            b = a;
            a = (temp1 + temp2) % MOD_ADD;

            j++;
            std::cout << a << std::endl;
            std::cout << b << std::endl;
            std::cout << c << std::endl;
            std::cout << d << std::endl;
            std::cout << e << std::endl;
            std::cout << f << std::endl;
            std::cout << g << std::endl;
            std::cout << h << std::endl;
            exit(0);
        }

        // Add the compressed chunk to the current hashes
        // hashes[0] += a;
        // hashes[1] += b;
        // hashes[2] += c;
        // hashes[3] += d;
        // hashes[4] += e;
        // hashes[5] += f;
        // hashes[6] += g;
        // hashes[7] += h;
    }

    string hash = "";

    // Compute the hash by concatenating all of the root hashes
    for (unsigned long i = 0; i < sizeof(hashes); i += 2) {
        hash += concat(hashes[i], hashes[i + 1]).to_string();
    }

    return hash;
}

#endif // SHA256_HPP
