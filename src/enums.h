//
// FILENAME: enums.h | Plasmacoin Cryptocurrency
// DESCRIPTION: Global enums needed by the application that aren't categorized elsewhere
// CREATED: 2022-08-8 @ 11:43 PM
// COPYRIGHT: Copyright (c) 2022 by Ryan Smith <rysmith2113@gmail.com>
//

#ifndef ENUMS_H
#define ENUMS_H

namespace enums {
	enum NodeType {LIGHT = 0, FULL, MINING};
	enum MiningMethod {CPU = 0, GPU};
}

#endif // ENUMS_H