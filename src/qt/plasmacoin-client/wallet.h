//
// FILENAME: wallet.h | Plasmacoin Cryptocurrency
// DESCRIPTION: The the user's wallet
// CREATED: 2022-06-16 @ 9:13 PM
// COPYRIGHT: Copyright (c) 2022 by Ryan Smith <rysmith2113@gmail.com>
//

#ifndef WALLET_H
#define WALLET_H

#include "transaction.hpp"

class Wallet {
public:
	enum class WalletActions: uint8_t {WITHDRAW, DEPOSIT};

	void UpdateBalance(const WalletActions& action, double amount);
	void UpdatePendingBal(const WalletActions& action, double amount);
	void UpdateAvailableBal(const WalletActions& action, double amount);

	bool IsPossible(Transaction* transaction) const;

	double GetBalance() const;
	double GetPendingBal() const;
	double GetAvailableBal() const;
	double GetFutureBal() const;

private:
	double m_Balance = 2;
	double m_PendingBalance = 0;
	double m_AvailableBalance = m_Balance;
};

#endif // WALLET_H