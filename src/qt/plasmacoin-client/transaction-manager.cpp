//
// FILENAME: transaction-manager.cpp | Plasmacoin Cryptocurrency
// DESCRIPTION: The source file for transaction-manager.h
// CREATED: 2021-12-25 @ 1:44 PM
// COPYRIGHT: Copyright (c) 2021 by Ryan Smith <rysmith2113@gmail.com>
//

#include "transaction-manager.h"

TransactionManager::TransactionManager(QListWidget* contactsList, QListWidget* transactionLog):
	m_ContactsList(contactsList),
	m_TransactionLog(transactionLog)
{}

TransactionManager::~TransactionManager() {
	delete m_ContactsList;
	delete m_TransactionLog;
}

void TransactionManager::UpdateContactsList(AddressBook* addressBook) {
	for (unsigned int i = 0; i < addressBook->Size(); i++) {
		Contact* contact = addressBook->At(i);

		m_Contacts.push_back(contact);
		m_ContactsList->addItem(new QListWidgetItem(QString::fromStdString(contact->GetUsername())));
	}
}