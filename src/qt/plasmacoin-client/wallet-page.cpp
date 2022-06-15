//
// FILENAME: wallet-page.cpp | Plasmacoin Cryptocurrency
// DESCRIPTION: The source file for wallet-page.hpp
// CREATED: 2022-06-13 @ 3:40 PM
// COPYRIGHT: Copyright (c) 2022 by Ryan Smith <rysmith2113@gmail.com>
//

#include "wallet-page.hpp"

WalletPage::WalletPage(QTableWidget* receiptList):
	m_ReceiptList(receiptList)
{}

WalletPage::~WalletPage() {
	delete m_ReceiptList;
}

void WalletPage::AddReceipt(Receipt* receipt) {
	m_Receipts.push_back(receipt);
	m_ReceiptList->setRowCount(m_ReceiptList->rowCount() + 1);

	std::pair<QTableWidgetItem, QTableWidgetItem> row = {
		QTableWidgetItem(QString::fromStdString(utility::formatEpoch(receipt->m_TransactionTime))),
		QTableWidgetItem(QString::fromStdString(receipt->m_Hash))
	};

	row.first.setData(Qt::TextAlignmentRole, Qt::AlignCenter);
	row.second.setData(Qt::TextAlignmentRole, Qt::AlignCenter);

	m_ReceiptList->setItem(m_ReceiptList->rowCount() - 1, 0, new QTableWidgetItem(row.first));
	m_ReceiptList->setItem(m_ReceiptList->rowCount() - 1, 1, new QTableWidgetItem(row.second));

	datfs::saveReceipt(receipt);
}