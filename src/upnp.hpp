//
// FILENAME: upnp.hpp | Plasmacoin Cryptocurrency
// DESCRIPTION: Universal Plug-and-Play (UPnP) support for Plasmacoin
// CREATED: 2022-08-10 @ 7:44 PM
// COPYRIGHT: Copyright (c) 2022 by Ryan Smith <rysmith2113@gmail.com>
//

#include <string>
#include <vector>

namespace go {
	#include "pcnetworkd.h"
}

using std::string;

namespace upnp {
	void openPort(const char* serviceID, const char* protocol, uint16_t port, const char* host);
	std::vector<string> getServiceIDs();
}