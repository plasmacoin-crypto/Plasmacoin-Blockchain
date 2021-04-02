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

void TransactionList::Populate() {
	QStringList list;
	list << "Item1" << "Item2" << "Item3";

	m_TransactionList->addItems(list); // Poplate from the QStringList
}

void TransactionList::Pop() {
	// Transaction* front = m_List.front();
	// m_List.pop();

	// return front;
	m_TransactionList->takeItem(0);
}