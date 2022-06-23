//
// FILENAME: removalRequest.hpp | Plasmacoin Cryptocurrency
// DESCRIPTION: Request to be removed from an Address Lookup database
// CREATED: 2021-06-19 @ 10:24 PM
// COPYRIGHT: Copyright (c) 2022 by Ryan Smith <rysmith2113@gmail.com>
//

#ifndef REMOVAL_REQUEST_HPP
#define REMOVAL_REQUEST_HPP

#include <string>

struct RemovalRequest {
	std::string m_SenderIP;
};

#endif // REMOVAL_REQUEST_HPP