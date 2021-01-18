//
// FILENAME: transaction.hpp | Plasmacoin Cryptocurrency
// DESCRIPTION: A transaction between nodes
// CREATED: 2020-01-18 @ 10:01 PM
// COPYRIGHT: Copyright (c) 2021 by Ryan Smith <rysmith2113@gmail.com>
//

#ifndef TRANSACTION_HPP
#define TRANSACTION_HPP

#include "node.hpp"

class Transaction {
public:
	Node m_Sender, m_Recipient;
};

#endif // TRANSACTION_HPP
