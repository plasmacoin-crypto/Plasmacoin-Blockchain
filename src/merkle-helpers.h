//
// FILENAME: merkle-helpers.h | Plasmacoin Cryptocurrency
// DESCRIPTION: Helper functions for constructing a Merkle Tree (a.k.a a Hash Tree)
// CREATED: 2021-07-04 @ 4:06 PM
// COPYRIGHT: Copyright (c) 2021 by Ryan Smith <rysmith2113@gmail.com>
//

#ifndef MERKLE_HELPERS_H
#define MERKLE_HELPERS_H

#include <math.h>

int mh_height(int leaves);
int mh_nodes(int height);
int mh_pads(int leaves);

#endif // MERKLE_HELPERS_H