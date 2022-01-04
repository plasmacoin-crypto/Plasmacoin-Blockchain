//
// FILENAME: transaction-list.h | Plasmacoin Cryptocurrency
// DESCRIPTION: Manage the transaction list in the mining menu
// CREATED: 2021-03-31 @ 8:04 PM
// COPYRIGHT: Copyright (c) 2021 by Ryan Smith <rysmith2113@gmail.com>
//

#ifndef TRANSACTION_LIST_H
#define TRANSACTION_LIST_H

#include <vector>
#include <string>

#include "transaction.hpp"

#include <QtWidgets/QMainWindow>
#include <QList>

#include "ui_mainwindow.h"

using std::vector;

class TransactionList : public QMainWindow, public Ui_MainWindow {
public:
	TransactionList(QListWidget*& list);
	~TransactionList();

	void Add(Transaction*& transaction);
	void Pop();

	vector<Transaction*> m_List; // The corresponding transactions

private:
	QListWidget*& m_TransactionList; // The QListWidget
};

#endif // TRANSACTION_LIST_H