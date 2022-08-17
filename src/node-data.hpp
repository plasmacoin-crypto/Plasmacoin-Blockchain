//
// FILENAME: node-data.hpp | Plasmacoin Cryptocurrency
// DESCRIPTION: Basic node data
// CREATED: 2022-08-16 @ 2:24 PM
// COPYRIGHT: Copyright (c) 2022 by Ryan Smith <rysmith2113@gmail.com>
//

#include <string>

#include "enums.h"

struct NodeData {
	std::string 	m_IPAddress;
	uint16_t 		m_Port;
	std::string 	m_Address;
	enums::NodeType m_NodeType;
};