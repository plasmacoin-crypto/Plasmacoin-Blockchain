//
// FILENAME: transaction-list.h | Plasmacoin Cryptocurrency
// DESCRIPTION: Manage the transaction list in the mining menu
// CREATED: 2021-03-31 @ 8:04 PM
// COPYRIGHT: Copyright (c) 2021 by Ryan Smith <rysmith2113@gmail.com>
//

#ifndef TRANSACTION_LIST_H
#define TRANSACTION_LIST_H

#include <queue>

#include "../../transaction.hpp"
//#include "../../blockchain.hpp"

#include <QtWidgets/QMainWindow>
#include <QList>

#include "ui_mainwindow.h"

using std::queue;

class TransactionList : public QMainWindow, public Ui_MainWindow {
	Q_OBJECT

public:
	TransactionList(QListWidget*& list);
	~TransactionList();

	void Populate();
	void Pop();

private:
	queue<Transaction*> m_List;
	QListWidget*& m_TransactionList;
};

#endif // TRANSACTION_LIST_H