//
// FILENAME: bcdata.hpp | Plasmacoin Cryptocurrency
// DESCRIPTION: Blockchain data to send to another node
// CREATED: 2022-04-10 @ 10:03 PM
// COPYRIGHT: Copyright (c) 2022 by Ryan Smith <rysmith2113@gmail.com>
//

#ifndef BC_DATA_HPP
#define BC_DATA_HPP

#include <vector>

template<typename T> struct BlockchainData {
	int m_DataType;
	std::vector<T> m_Data;
};

#endif // BC_DATA_HPP
