//
// FILENAME: transaction-manager.h | Plasmacoin Cryptocurrency
// DESCRIPTION: Manage interactions with transactions on the blockchain
// CREATED: 2021-12-25 @ 1:44 PM
// COPYRIGHT: Copyright (c) 2021 by Ryan Smith <rysmith2113@gmail.com>
//

#ifndef TRANSACTION_MANAGER_H
#define TRANSACTION_MANAGER_H

#include <vector>

#include <QListWidget>
#include <QListWidgetItem>
#include <QString>
#include <QDialogButtonBox>
#include <QDoubleSpinBox>
#include <QPushButton>
#include <QLineEdit>
#include <QMessageBox>

#include "ui.h"

#include "address-book.h"
#include "contact.h"
#include "transaction.hpp"

class TransactionManager : public QMainWindow, public Ui_MainWindow {
public:
	TransactionManager(
		QListWidget* contactsList, QListWidget* transactionLog, QLineEdit* lineEdit,
		QDoubleSpinBox* amountSelector, QDoubleSpinBox* feeSelector, QDialogButtonBox* dialog,
		QMessageBox* messageBox
	);
	~TransactionManager();

	void UpdateContactsList(AddressBook* addressBook);
	bool CheckFields();

	void AllowSend();
	void ProhibitSend();

	int AskForConf(Transaction* transaction);
	int ShowWarning(double totalBalance, Transaction* transaction);

private:
	QListWidget *m_ContactsList, *m_TransactionLog;
	QLineEdit* m_MessageField;
	QDoubleSpinBox *m_AmountSelector, *m_FeeSelector;
	QDialogButtonBox* m_Dialog;
	QMessageBox* m_TransactionAlert;

	std::vector<Contact*> m_Contacts;
};

#endif // TRANSACTION_MANAGER_H