//
// FILENAME: dssize.cpp | Plasmacoin Cryptocurrency
// DESCRIPTION: The source file for dssize.hpp
// CREATED: 2022-02-04 @ 9:32 PM
// COPYRIGHT: Copyright (c) 2022 by Ryan Smith <rysmith2113@gmail.com>
//

#include "dssize.hpp"

size_t dssize::size(const Block& block) {
	size_t headerSize = (
		sizeof(block.m_Index) +
		sizeof(block.m_Nonce) +
		sizeof(block.m_Difficulty) +
		block.m_Hash.size() +
		block.m_PrevHash.size() +
		block.m_MinerAddr.size() +
		block.m_CreationTime.size() +
		block.m_MineTime.size() +
		sizeof(block.m_IsGenesis)
	);

	size_t trxnSizes = 0;

	for (auto trxn: block.m_Transactions) {
		trxnSizes += dssize::size(*trxn);
	}

	return headerSize + trxnSizes;
}

size_t dssize::size(const Transaction& transaction) {
	return (
		sizeof(transaction.m_Amount) +
		sizeof(transaction.m_Fee) +
		transaction.m_SenderAddr.size() +
		transaction.m_RecipientAddr.size() +
		transaction.m_Content.size() +
		dssize::size(transaction.m_Signature)
	);
}

size_t dssize::size(const Signature& signature) {
	return (
		signature.m_Signature.size() * sizeof(CryptoPP::byte) +
		dssize::PUBLIC_KEY_SIZE +
		sizeof(signature.m_Length)
	);
}