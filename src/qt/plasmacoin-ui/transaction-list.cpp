//
// FILENAME: transaction-list.cpp | Plasmacoin Cryptocurrency
// DESCRIPTION: The source file for transaction-list.h
// CREATED: 2021-03-31 @ 8:04 PM
// COPYRIGHT: Copyright (c) 2021 by Ryan Smith <rysmith2113@gmail.com>
//

#include "transaction-list.h"
#include <iostream>

TransactionList::TransactionList(QListWidget*& list):
	//QMainWindow(parent)
	m_TransactionList(list)
{}

TransactionList::~TransactionList() {}

void TransactionList::Add(Transaction* transaction) {
	m_List.push_back(transaction);

	QListWidgetItem* item = new QListWidgetItem(QString(transaction->m_Condensed.c_str()), m_TransactionList);
	item->setData(Qt::UserRole, m_TransactionList->count() + 1);
	m_TransactionList->addItem(item);
}

void TransactionList::Pop() {
	// Transaction* front = m_List.front();
	// m_List.pop();

	// return front;
	m_TransactionList->takeItem(0);
}