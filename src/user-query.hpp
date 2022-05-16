//
// FILENAME: user-query.cpp | Plasmacoin Cryptocurrency
// DESCRIPTION: A way for a node to request information about other nodes
// CREATED: 2022-04-09 @ 11:38 PM
// COPYRIGHT: Copyright (c) 2022 by Ryan Smith <rysmith2113@gmail.com>
//

#ifndef USER_QUERY_HPP
#define USER_QUERY_HPP

#include <string>

struct UserQuery {
	std::string m_IPAddr;
	std::string m_NodeType;
};

#endif // USER_QUERY_HPP