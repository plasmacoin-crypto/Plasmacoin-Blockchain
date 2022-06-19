//
// FILENAME: pending-trxn.hpp | Plasmacoin Cryptocurrency
// DESCRIPTION: A pending transaction
// CREATED: 2022-06-16 @ 2:224 PM
// COPYRIGHT: Copyright (c) 2022 by Ryan Smith <rysmith2113@gmail.com>
//

#ifndef PENDING_TRXN_HPP
#define PENDING_TRXN_HPP

#include <string>

struct PendingTransaction {
	time_t 		m_Timestamp;
	std::string m_Hash;
	double 		m_Amount;
};

#endif // PENDING_TRXN_HPP