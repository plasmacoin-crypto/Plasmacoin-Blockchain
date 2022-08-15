//
// FILENAME: upnp.cpp | Plasmacoin Cryptocurrency
// DESCRIPTION: Universal Plug-and-Play (UPnP) support for Plasmacoin
// CREATED: 2022-08-10 @ 7:44 PM
// COPYRIGHT: Copyright (c) 2022 by Ryan Smith <rysmith2113@gmail.com>
//

#include "upnp.hpp"

void upnp::openPort(const char* serviceID, const char* protocol, uint16_t port, const char* host) {
	go::openUPnPPort(serviceID, protocol, static_cast<go::GoUint16>(port), host);
}

std::vector<string> upnp::getServiceIDs() {
	// Get the list of  available service IDs on the user's router
	const char** slice = const_cast<const char**>(go::getServiceIDs());
	size_t numItems = sizeof(slice) / sizeof(char*);

	std::vector<string> serviceIDs;

	// Convert the Go slice (as a C pointer to an array) to a vector
	for (unsigned int i = 0; i < numItems; i++, slice++) {
		serviceIDs.push_back(*slice);
	}

	return serviceIDs;
}