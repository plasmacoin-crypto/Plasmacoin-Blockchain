//
// FILENAME: transaction-view.h | Plasmacoin Cryptocurrency
// DESCRIPTION: Manage a table of transaction data
// CREATED: 2022-01-26 @ 10:52 PM
// COPYRIGHT: Copyright (c) 2021 by Ryan Smith <rysmith2113@gmail.com>
//

#ifndef TRANSACTION_VIEW_H
#define TRANSACTION_VIEW_H

#include <vector>
#include <utility>
#include <iterator>

#include <QMainWindow>
#include <QTableWidget>
#include <QTableWidgetItem>

#include "ui.h"
#include "transaction.hpp"

class TransactionView : public QMainWindow, public Ui_MainWindow {
public:
	TransactionView(QTableWidget* transactionView, int amountPrecision = 10, int feePrecision = 5);
	~TransactionView();

	void Display(Transaction* transaction);
	void Clear();

private:
	QTableWidget* m_TransactionView;
	int m_AmountPrecision, m_FeePrecision;
};

#endif // TRANSACTION_VIEW_H