//
// FILENAME: net-constants.cpp | Plasmacoin Cryptocurrency
// DESCRIPTION: Networking constants
// CREATED: 2021-08-13 @ 2:48 AM
// COPYRIGHT: Copyright (c) 2022 by Ryan Smith <rysmith2113@gmail.com>
//

#ifndef NET_CONSTANTS_H
#define NET_CONSTANTS_H

namespace go {
	#include "pcnetworkd.h"
}

namespace netconsts {
	const char* const TCP = "tcp";
	const char* const UDP = "udp";

	const char* const LOCAL_IP = go::getLocalIP();
	const char* const PUBLIC_IP = go::getPublicIP();

	const uint16_t TEST_PORT = 8080;
	const uint16_t CLIENT_PORT = 14400;
	const uint16_t ADDR_LOOKUP_PORT = 34300;
}


#endif // NET_CONSTANTS_H