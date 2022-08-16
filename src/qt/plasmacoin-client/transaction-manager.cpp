//
// FILENAME: transaction-manager.cpp | Plasmacoin Cryptocurrency
// DESCRIPTION: The source file for transaction-manager.h
// CREATED: 2021-12-25 @ 1:44 PM
// COPYRIGHT: Copyright (c) 2021 by Ryan Smith <rysmith2113@gmail.com>
//

#include "transaction-manager.h"

TransactionManager::TransactionManager(Ui_MainWindow* window, QMessageBox* messageBox):
	m_Window(window),
	m_TransactionAlert(messageBox)
{
	// Add a button to calculate the transaction fees
	QPushButton* calcButton = new QPushButton("Calculate Fee");
	m_Window->btndiag_send->addButton(calcButton, QDialogButtonBox::ActionRole);

	ProhibitSend();
}

TransactionManager::~TransactionManager() {
	delete m_TransactionAlert;
}

void TransactionManager::UpdateContactsList(AddressBook* addressBook) {
	for (unsigned int i = 0; i < addressBook->Size(); i++) {
		Contact* contact = addressBook->At(i);

		m_Contacts.push_back(contact);
		m_Window->contacts->addItem(new QListWidgetItem(QString::fromStdString(contact->GetUsername())));
	}
}

bool TransactionManager::CheckFields() {
	int row = m_Window->contacts->currentRow();

	// Collect transaction data
	string recipientAddr = m_Contacts[row]->GetAddress();
	double amount = m_Window->amountSelector->value();
	double fee = m_Window->feeSelector->value();

	QString text = m_Window->messageField->text();
	string content = text.isEmpty()? "" : text.toStdString();

	return (
		(row >= 0 && row <= m_Window->contacts->count()) &&
		amount > 0 &&
		fee > 0
	);
}

void TransactionManager::AllowSend() {
	m_Window->btndiag_send->button(QDialogButtonBox::Ok)->setEnabled(true); // Enable the OK button
	m_Window->btndiag_send->button(QDialogButtonBox::Ok)->setAutoDefault(true);
}

void TransactionManager::ProhibitSend() {
	m_Window->btndiag_send->button(QDialogButtonBox::Ok)->setEnabled(false); // Disable the OK button
	m_Window->btndiag_send->button(QDialogButtonBox::Ok)->setAutoDefault(true);
}

// Ask the user to confirm the data of the transaction they're currently working on
int TransactionManager::AskForConf(Transaction* transaction) {
	m_TransactionAlert = new QMessageBox(
		QMessageBox::Information, "Plasmacoin Client",
		QString::fromStdString("Transaction created. Please review the details, then click \"OK\"."),
		QMessageBox::StandardButton::Ok | QMessageBox::StandardButton::Cancel
	);
	m_TransactionAlert->setStyleSheet("QLabel{max-width: 1000px;}");

	std::string detailedText = (
		"Sender: " 	  			+ transaction->m_SenderAddr 	 								+ "\n" +
		"Recipient: " 			+ transaction->m_RecipientAddr 		  							+ "\n" +
		"Amount: "	  			+ QString::number(transaction->m_Amount, 'f', 10).toStdString() + "\n" +
		"Fee (after signing): " + QString::number(transaction->m_Fee, 'f', 6).toStdString()		+ "\n" +
		"Content: "				+ transaction->m_Content 										+ "\n" +
		"Hash: "				+ transaction->m_Hash
	);
	m_TransactionAlert->setDetailedText(QString::fromStdString(detailedText));

	return m_TransactionAlert->exec();
}

// Warn the user about an issue with their transaction
int TransactionManager::ShowWarning(double balance, Transaction* transaction) {
	m_TransactionAlert = new QMessageBox(
		QMessageBox::Warning, "Plasmacoin Client",
		QString::fromStdString("Insufficient funds. Please review the details, then click \"OK\"."),
		QMessageBox::StandardButton::Ok
	);
	m_TransactionAlert->setStyleSheet("QLabel{max-width: 1000px;}");

	const double TRXN_TOTAL = transaction->m_Amount + transaction->m_Fee;
	const double RESULT = balance - TRXN_TOTAL;

	std::string detailedText = (
		"Account balance: "	   + QString::number(balance, 'f', 10).toStdString()   	+ "\n" +
		"Transaction amount: " + QString::number(TRXN_TOTAL, 'f', 10).toStdString() + "\n" +
		"Resulting balance: "  + QString::number(RESULT, 'f', 10).toStdString()		+ "\n"
	);
	m_TransactionAlert->setDetailedText(QString::fromStdString(detailedText));

	return m_TransactionAlert->exec();
}
