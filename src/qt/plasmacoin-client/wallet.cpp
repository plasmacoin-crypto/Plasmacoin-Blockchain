//
// FILENAME: wallet.hpp | Plasmacoin Cryptocurrency
// DESCRIPTION: The source file for wallet.cpp
// CREATED: 2022-06-16 @ 9:13 PM
// COPYRIGHT: Copyright (c) 2022 by Ryan Smith <rysmith2113@gmail.com>
//

#include "wallet.h"

void Wallet::UpdateBalance(const WalletActions& action, double amount) {
	if (action == WalletActions::WITHDRAW) {
		m_Balance -= amount;
	}
	else if (action == WalletActions::DEPOSIT) {
		m_Balance += amount;
	}
}

void Wallet::UpdatePendingBal(const WalletActions& action, double amount) {
	if (action == WalletActions::WITHDRAW) {
		m_PendingBalance -= amount;
	}
	else if (action == WalletActions::DEPOSIT) {
		m_PendingBalance += amount;
	}
}

bool Wallet::IsPossible(Transaction* transaction) const {
	return m_Balance - transaction->m_Amount - transaction->m_Fee >= 0;
}

double Wallet::GetBalance() const {
	return m_Balance;
}

double Wallet::GetPendingBal() const {
	return m_PendingBalance;
}

double Wallet::GetTotalBal() const {
	// If you spent money, you can't respend it. If you're receiving money, you
	// can't spend it until you actually receive it.
	return (m_PendingBalance >= 0)? m_Balance : m_Balance + m_PendingBalance;
}