//
// FILENAME: transaction-list.cpp | Plasmacoin Cryptocurrency
// DESCRIPTION: The source file for transaction-list.h
// CREATED: 2021-03-31 @ 8:04 PM
// COPYRIGHT: Copyright (c) 2021 by Ryan Smith <rysmith2113@gmail.com>
//

#include "transaction-list.h"
#include <iostream>

TransactionList::TransactionList(QListWidget*& list):
	m_TransactionList(list)
{}

TransactionList::~TransactionList() {
	for (auto trxn: m_List) {
		delete trxn;
	}

	delete m_TransactionList;
}

void TransactionList::Add(Transaction* transaction) {
	m_List.push_back(transaction);

	QListWidgetItem* item = new QListWidgetItem(QString::fromStdString(transaction->m_Hash), m_TransactionList);
	item->setData(Qt::UserRole, m_TransactionList->count() + 1);
	m_TransactionList->addItem(item);
}

void TransactionList::Delete(int row) {
	m_TransactionList->takeItem(row);
}

Transaction* TransactionList::At(int row) {
	return m_List[row];
}

bool TransactionList::ConfirmToMempool(Transaction* transaction, int256_t target) {
	bool valid = validation::validate(*transaction, target);

	if (valid) {
		Add(transaction);
	}

	return valid;
}