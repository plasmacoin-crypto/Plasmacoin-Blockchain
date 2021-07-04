//
// FILENAME: merkle-helpers.h | Plasmacoin Cryptocurrency
// DESCRIPTION: Helper functions for constructing a Merkle Tree (a.k.a a Hash Tree)
// CREATED: 2021-07-04 @ 4:06 PM
// COPYRIGHT: Copyright (c) 2021 by Ryan Smith <rysmith2113@gmail.com>
//

#ifndef MERKLE_HELPERS_HPP
#define MERKLE_HELPERS_HPP

#include <math.h>

unsigned int height(unsigned int leaves);
unsigned int nodes(unsigned int height);
unsigned int pads(unsigned int leaves);

#endif // MERKLE_HELPERS_HPP