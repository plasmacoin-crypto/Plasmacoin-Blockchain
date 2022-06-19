//
// FILENAME: wallet.hpp | Plasmacoin Cryptocurrency
// DESCRIPTION: The source file for wallet.cpp
// CREATED: 2022-06-16 @ 9:13 PM
// COPYRIGHT: Copyright (c) 2022 by Ryan Smith <rysmith2113@gmail.com>
//

#include "wallet.h"

void Wallet::UpdateWorkingBal(const WalletActions& action, double amount) {
	if (action == WalletActions::WITHDRAW) {
		m_WorkingBalance -= amount;
	}
	else if (action == WalletActions::DEPOSIT) {
		m_WorkingBalance += amount;
	}
}

void Wallet::UpdateBalance(const WalletActions& action, double amount) {
	if (action == WalletActions::WITHDRAW) {
		m_Balance -= amount;
	}
	else if (action == WalletActions::DEPOSIT) {
		m_Balance += amount;
	}
}

bool Wallet::IsPossible(Transaction* transaction) const {
	return m_Balance - transaction->m_Amount - transaction->m_Fee >= 0;
}

double Wallet::GetBalance() const {
	return m_Balance;
}