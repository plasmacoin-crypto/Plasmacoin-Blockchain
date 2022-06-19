//
// FILENAME: wallet-page.cpp | Plasmacoin Cryptocurrency
// DESCRIPTION: The source file for wallet-page.hpp
// CREATED: 2022-06-13 @ 3:40 PM
// COPYRIGHT: Copyright (c) 2022 by Ryan Smith <rysmith2113@gmail.com>
//

#include "wallet-page.h"

WalletPage::WalletPage(QTableWidget* receiptList, QTableWidget* pendingList):
	m_ReceiptList(receiptList),
	m_PendingList(pendingList)
{}

WalletPage::~WalletPage() {
	delete m_ReceiptList;
	delete m_PendingList;
}

void WalletPage::AddReceipt(Receipt* receipt) {
	m_ReceiptList->setRowCount(m_ReceiptList->rowCount() + 1);

	auto column1 = QTableWidgetItem(QString::fromStdString(utility::formatEpoch(receipt->m_TransactionTime)));
	auto column2 = QTableWidgetItem(QString::fromStdString(receipt->m_Hash));
	auto column3 = QTableWidgetItem(QString::number(receipt->m_Amount, 'f', 10));

	column1.setData(Qt::TextAlignmentRole, Qt::AlignCenter);
	column2.setData(Qt::TextAlignmentRole, Qt::AlignCenter);
	column3.setData(Qt::TextAlignmentRole, Qt::AlignCenter);

	m_ReceiptList->setItem(m_ReceiptList->rowCount() - 1, 0, new QTableWidgetItem(column1));
	m_ReceiptList->setItem(m_ReceiptList->rowCount() - 1, 1, new QTableWidgetItem(column2));
	m_ReceiptList->setItem(m_ReceiptList->rowCount() - 1, 2, new QTableWidgetItem(column3));

	m_ReceiptList->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
	datfs::saveReceipt(receipt);

	// Remove the corresponding pending transaction
	auto iter = std::find_if(m_PendingTrxns.begin(), m_PendingTrxns.end(), [&receipt](PendingTransaction* ptrxn) {
		return ptrxn->m_Hash == receipt->m_Hash;
	});

	if (iter != m_PendingTrxns.end()) {
		m_PendingTrxns.erase(iter);
		m_PendingList->removeRow(std::distance(m_PendingTrxns.begin(), iter));
	}
}

void WalletPage::AddPending(PendingTransaction* pendingTrxn) {
	m_PendingTrxns.push_back(pendingTrxn);
	m_PendingList->setRowCount(m_PendingList->rowCount() + 1);

	auto column1 = QTableWidgetItem(QString::fromStdString(utility::formatEpoch(pendingTrxn->m_Timestamp)));
	auto column2 = QTableWidgetItem(QString::fromStdString(pendingTrxn->m_Hash));
	auto column3 = QTableWidgetItem(QString::number(pendingTrxn->m_Amount, 'f', 10));

	column1.setData(Qt::TextAlignmentRole, Qt::AlignCenter);
	column2.setData(Qt::TextAlignmentRole, Qt::AlignCenter);
	column2.setData(Qt::TextAlignmentRole, Qt::AlignCenter);

	m_PendingList->setItem(m_PendingList->rowCount() - 1, 0, new QTableWidgetItem(column1));
	m_PendingList->setItem(m_PendingList->rowCount() - 1, 1, new QTableWidgetItem(column2));
	m_PendingList->setItem(m_PendingList->rowCount() - 1, 2, new QTableWidgetItem(column3));

	m_PendingList->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
}
