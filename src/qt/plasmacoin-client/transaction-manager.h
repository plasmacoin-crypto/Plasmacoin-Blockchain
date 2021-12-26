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

#include "ui_mainwindow.h"

#include "address-book.h"
#include "contact.h"

class TransactionManager : public QMainWindow, public Ui_MainWindow {
public:
	TransactionManager(QListWidget* contactsList, QListWidget* transactionLog);
	~TransactionManager();

	void UpdateContactsList(AddressBook* addressBook);

private:
	QListWidget *m_ContactsList, *m_TransactionLog;

	std::vector<Contact*> m_Contacts;
};

#endif // TRANSACTION_MANAGER_H