//
// FILENAME: merkle-helpers.c | Plasmacoin Cryptocurrency
// DESCRIPTION: The source file for merkle-helpers.h
// CREATED: 2021-07-04 @ 4:06 PM
// COPYRIGHT: Copyright (c) 2021 by Ryan Smith <rysmith2113@gmail.com>
//

#include "merkle-helpers.h"

// Predict the height of a Merkle Tree based on the number of
// leaves it has.
unsigned int height(unsigned int leaves) {
	return uint(ceil(log2(leaves)) + 1);
}

// Get the number of nodes in the Merkle Tree ree based on the
// tree's height.
unsigned int nodes(unsigned int height) {
	return uint(pow(2, height) - 1);
}

// Calculate the number of times Merkle Tree nodes will need to
// be duplicated to keep the tree balanced based on the number of
// leaves it has. This algorithm runs in O(log n) time.
unsigned int pads(unsigned int leaves) {
	uint pads = 0, n = leaves;

	while (n != 1) {
		// If the number of nodes at a specific level isn't even, a
		// node will need to be duplicated, thus padding will occur.
		if (n % 2 != 0) {
			pads += 1; 	// Record the duplication
			n += 1; // Simulate padding. `n` is now even.
		}

		n /= 2; // The next higher tree level will have n/2 nodes
	}

	return pads;
}