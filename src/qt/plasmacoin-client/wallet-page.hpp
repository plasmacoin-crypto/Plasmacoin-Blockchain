//
// FILENAME: wallet-page.hpp | Plasmacoin Cryptocurrency
// DESCRIPTION: The the user's wallet
// CREATED: 2022-06-13 @ 3:40 PM
// COPYRIGHT: Copyright (c) 2022 by Ryan Smith <rysmith2113@gmail.com>
//

#ifndef WALLET_PAGE_HPP
#define WALLET_PAGE_HPP

#include <QMainWindow>
#include <QTableWidget>
#include <QTableWidgetItem>

#include <vector>

#include "ui.h"
#include "receipt.hpp"
#include "dat-fs.hpp"

class WalletPage : public QMainWindow, public Ui_MainWindow {
public:
	WalletPage(QTableWidget* receiptList);
	~WalletPage();

	void AddReceipt(Receipt* receipt);

private:
	QTableWidget* m_ReceiptList;
	std::vector<Receipt*> m_Receipts;
};

#endif // WALLET_PAGE_HPP