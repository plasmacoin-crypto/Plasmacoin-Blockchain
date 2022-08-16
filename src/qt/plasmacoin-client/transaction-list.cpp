//
// FILENAME: transaction-list.cpp | Plasmacoin Cryptocurrency
// DESCRIPTION: The source file for transaction-list.h
// CREATED: 2021-03-31 @ 8:04 PM
// COPYRIGHT: Copyright (c) 2021 by Ryan Smith <rysmith2113@gmail.com>
//

#include "transaction-list.h"
#include <iostream>

TransactionList::TransactionList(Ui_MainWindow* window):
	m_Window(window)
{}

TransactionList::~TransactionList() {
	for (auto trxn: m_List) {
		delete trxn;
	}
}

void TransactionList::Add(Transaction* transaction) {
	m_List.push_back(transaction);

	QListWidgetItem item(QString::fromStdString(transaction->m_Hash), m_Window->transactionList);
	item.setData(Qt::UserRole, m_Window->transactionList->count() + 1);
	m_Window->transactionList->addItem(new QListWidgetItem(item));
}

void TransactionList::Delete(int row) {
	m_Window->transactionList->takeItem(row);
}

Transaction* TransactionList::At(int row) {
	return m_List[row];
}

bool TransactionList::ConfirmToMempool(Transaction* transaction) {
	bool valid = validation::validate(*transaction);

	if (valid) {
		Add(transaction);
	}

	return valid;
}