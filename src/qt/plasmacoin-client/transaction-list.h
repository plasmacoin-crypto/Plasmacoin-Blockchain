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

#include <QtWidgets/QMainWindow>
#include <QList>

#include <boost/multiprecision/cpp_int.hpp>

#include "ui.h"
#include "transaction.hpp"
#include "validation.hpp"

using std::vector;

using boost::multiprecision::int256_t;

class TransactionList : public QMainWindow, public Ui_MainWindow {
public:
	TransactionList(Ui_MainWindow* window);
	~TransactionList();

	void Add(Transaction* transaction);
	void Delete(int row);
	Transaction* At(int row);

	bool ConfirmToMempool(Transaction* transaction);

private:
	Ui_MainWindow* m_Window;
	vector<Transaction*> m_List; // The corresponding transactions
};

#endif // TRANSACTION_LIST_H