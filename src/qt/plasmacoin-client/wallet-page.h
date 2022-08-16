//
// FILENAME: wallet-page.h | Plasmacoin Cryptocurrency
// DESCRIPTION: The wallet page of the app
// CREATED: 2022-06-13 @ 3:40 PM
// COPYRIGHT: Copyright (c) 2022 by Ryan Smith <rysmith2113@gmail.com>
//

#ifndef WALLET_PAGE_H
#define WALLET_PAGE_H

#include <vector>
#include <string>

#include <QMainWindow>
#include <QTableWidget>
#include <QTableWidgetItem>

#include "ui.h"
#include "receipt.hpp"
#include "dat-fs.hpp"
#include "wallet.h"

class WalletPage : public QMainWindow, public Ui_MainWindow {
public:
	WalletPage(Ui_MainWindow* window, Wallet* wallet);
	~WalletPage();

	void AddReceipt(Receipt* receipt);
	void AddPending(PendingTransaction* pendingTrxn);

private:
	Ui_MainWindow* m_Window;
	Wallet* m_WalletCopy;

	std::vector<PendingTransaction*> m_PendingTrxns;
};

#endif // WALLET_PAGE_H