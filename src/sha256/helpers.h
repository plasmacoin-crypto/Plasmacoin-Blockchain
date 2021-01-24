//
// FILENAME: helpers.h | Plasmacoin Cryptocurrency
// DESCRIPTION: Functions to aid the SHA-256 algorithm
// CREATED: 2021-01-23 @ 11:56 PM
// COPYRIGHT: Copyright (c) 2021 by Ryan Smith <rysmith2113@gmail.com>
//

#ifndef SHA256_HELPERS_H
#define SHA256_HELPERS_H

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

// Convert a decimal number (i.e., and integer) to its Big Endian
// hexadecimal equivalent.
uint32_t tohex(int dec) {
	char* str[10000]; // Arbitrarily allocate 10000 characters
	sprintf(*str, "%d", dec); // Convert the decimal to a string

	for (int i = 0; str[i] != "\0"; i += 1) {

	}
}

#endif // SHA256_HELPERS_H

