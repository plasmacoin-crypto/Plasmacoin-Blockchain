//
// FILENAME: transaction-view.cpp | Plasmacoin Cryptocurrency
// DESCRIPTION: The source file for transaction-view.cpp
// CREATED: 2022-01-26 @ 10:52 PM
// COPYRIGHT: Copyright (c) 2021 by Ryan Smith <rysmith2113@gmail.com>
//

#include "transaction-view.h"

TransactionView::TransactionView(QTableWidget* transactionView, int amountPrecision, int feePrecision):
	m_TransactionView(transactionView),
	m_AmountPrecision(amountPrecision),
	m_FeePrecision(feePrecision)
{}

TransactionView::~TransactionView() {
	delete m_TransactionView;
}

void TransactionView::Display(Transaction* transaction) {
	m_TransactionView->setRowCount(7);

	std::vector<std::pair<QTableWidgetItem, QTableWidgetItem>> table = {
		{
			QTableWidgetItem(QString("Sender")),
			QTableWidgetItem(QString::fromStdString(transaction->m_SenderAddr))
		},
		{
			QTableWidgetItem(QString("Recipient")),
			QTableWidgetItem(QString::fromStdString(transaction->m_RecipientAddr))
		},
		{
			QTableWidgetItem(QString("Created")),
			QTableWidgetItem(QString::fromStdString(utility::formatEpoch(transaction->m_CreationTime)))
		},
		{
			QTableWidgetItem(QString("Signed")),
			QTableWidgetItem(QString::fromStdString(utility::formatEpoch(transaction->m_SignTime)))
		},
		{
			QTableWidgetItem(QString("Amount")),
			QTableWidgetItem(QString::number(transaction->m_Amount, 'f', m_AmountPrecision))
		},
		{
			QTableWidgetItem(QString("Fee")),
			QTableWidgetItem(QString::number(transaction->m_Fee, 'f', m_FeePrecision))
		},
		{
			QTableWidgetItem(QString("Hash")),
			QTableWidgetItem(QString::fromStdString(transaction->m_Hash))
		},
	};

	for (auto row = table.begin(); row != table.end(); std::advance(row, 1)) {
		// Center-align all elements
		row->first.setData(Qt::TextAlignmentRole, Qt::AlignCenter);
		row->second.setData(Qt::TextAlignmentRole, Qt::AlignCenter);

		m_TransactionView->setItem(std::distance(table.begin(), row), 0, new QTableWidgetItem(row->first));
		m_TransactionView->setItem(std::distance(table.begin(), row), 1, new QTableWidgetItem(row->second));
	}
}

void TransactionView::Clear() {
	m_TransactionView->setRowCount(0);
}