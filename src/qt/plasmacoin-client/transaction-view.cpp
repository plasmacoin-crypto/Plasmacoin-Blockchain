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
	m_TransactionView->setRowCount(5);
	int rowNum = m_TransactionView->rowCount();

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

	auto row = table.begin(); // Iterate over the map

	for (int i = 0; i < rowNum; i++) {
		// Center-align all elements
		row->first.setData(Qt::TextAlignmentRole, Qt::AlignCenter);
		row->second.setData(Qt::TextAlignmentRole, Qt::AlignCenter);

		m_TransactionView->setItem(i, 0, new QTableWidgetItem(row->first));
		m_TransactionView->setItem(i, 1, new QTableWidgetItem(row->second));

		std::advance(row, 1); // Move to the next set of QTableWidgetItems
	}
}

void TransactionView::Clear() {

}