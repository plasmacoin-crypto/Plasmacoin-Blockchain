
#include <string>

#include <QApplication>
#include <QPushButton>
#include <QListWidget>
#include <QListWidgetItem>
#include <QSplashScreen>
#include <QDialogButtonBox>
#include <QSignalBlocker>
#include <QDialogButtonBox>
#include <QLineEdit>
#include <QAbstractButton>
#include <QMessageBox>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "firebase-auth.h"
#include "transmitter.hpp"
#include "shared-mem.hpp"
#include "packet-types.h"
#include "parse-json.hpp"
#include "dssize.hpp"

using std::string;

double calculateFee(MainWindow& window);

// Allow the user to mine their block
void minePage(MainWindow& window) {
	//window.m_Status->m_Heading->setVisible(true); // Show the status heading

	// Mine a block when the correct button is clicked
	window.connect(window.btn_mine, &QPushButton::released, &window, [&window]() {
		window.m_Status->SetHeading("Mining Block #" + std::to_string(window.m_User->m_BlockchainCopy->Size()));

		std::thread mineThread(&MainWindow::StartMining, &window);
		mineThread.detach();
	});

	// Update the mining status on success
	window.connect(&window, &MainWindow::MiningSuccess, &window, [&window]() {
		window.ResetBlock();
		window.UpdateStatus(*window.m_User->m_BlockchainCopy->GetLatest(), window.m_LastMiningDur);

		Transmitter* transmitter = new Transmitter();
		auto data = transmitter->Format(window.m_User->m_BlockchainCopy->GetLatest());
		transmitter->Transmit(data, std::stoi(data[0]));

		delete transmitter;
	});

	// Display information about a transaction when a user selects it
	window.connect(window.transactionList, &QListWidget::itemSelectionChanged, &window, [&window]() {
		int row = window.transactionList->currentRow();
		window.m_TransactionView->Display(window.m_TransactionList->At(row));
	});
}

// Allow the user to type information in forms (QLineEdits) and be authenticated to
// the app through the Firebase REST API
void accountPages(MainWindow& window) {
	// Take a user from the sign in screen to the sign up screen
	window.connect(window.btn_create, &QPushButton::released, &window, [&window]() {
		window.m_AccPgs->DisplayPage(1);
	});

	// Take a user from the sign up screen back to the sign in screen
	window.connect(window.btn_back, &QPushButton::released, &window, [&window]() {
		window.m_AccPgs->DisplayPage(0);
	});

	// Sign a user into their account
	window.connect(window.btn_signIn, &QPushButton::released, &window, [&window]() {
		QString email, username, password;
		std::tie(email, username, password) = window.m_AccPgs->ReadText(); // Get the user's entries

		window.m_Authenticator->SignIn(email, password);
	});

	// Sign a user up for their account
	window.connect(window.btn_signUp, &QPushButton::released, &window, [&window]() {
		QString email, username, password;
		std::tie(email, username, password) = window.m_AccPgs->ReadText(); // Get the user's entries

		window.m_Authenticator->SignUp(email, username, password);
	});

	// Check the current form for authentication errors
	window.connect(window.m_Authenticator, &Auth::FoundAuthErrors, &window, [&window]() {
		std::cout << "Found auth errors" << std::endl;

		AccountPages::PageType page = static_cast<AccountPages::PageType>(window.accountView->currentIndex());
		string detailedText = ""; // Store explaination strings for all auth errors

		// Use bit masking to warn about certain errors
		for (uint8_t code = static_cast<uint8_t>(Auth::ErrorCodes::EMAIL_EXISTS), i = 0; i < static_cast<uint8_t>(Auth::ErrorCodes::LAST); code = 1 << ++i) {
			if (window.m_Authenticator->GetErrors() & code) {
				switch (code) {
					case static_cast<uint8_t>(Auth::ErrorCodes::EMAIL_EXISTS):
						detailedText += "Email already in use\n";
						break;

					case static_cast<uint8_t>(Auth::ErrorCodes::USERNAME_TAKEN):
						detailedText += "Username already in use\n";
						break;

					case static_cast<uint8_t>(Auth::ErrorCodes::INVALID_EMAIL):
						detailedText += "Invalid email\n";
						break;

					case static_cast<uint8_t>(Auth::ErrorCodes::INVALID_USERNAME):
						detailedText += "Invalid username\n";
						break;

					case static_cast<uint8_t>(Auth::ErrorCodes::INVALID_PASSWORD):
						detailedText += "Invalid password\n";
						break;

					case static_cast<uint8_t>(Auth::ErrorCodes::EMPTY_FIELD):
						detailedText += "One or more fields are empty\n";
						break;

					default:
						break;
				}
			}
		}

		window.m_AccPgs->DisplayErrorMsg(detailedText, page);
	});
}

void addressBook(MainWindow& window) {
	// Display contact info when the corresponding table object is selected
	window.connect(window.contactsList, &QTableWidget::itemSelectionChanged, &window, [&window]() {
		int row = window.contactsList->currentRow();
		window.ShowContact(window.m_AddressBook->At(row));
	});

	window.contactsList->selectRow(0);

	// Allow the user to add a contact
	window.connect(window.btn_addContact, &QToolButton::released, &window, [&window]() {
		Contact* contact = new Contact("New Contact", "", "", QDate());
		window.m_AddressBook->Add(contact);

		window.contactsList->selectRow(window.m_AddressBook->GetRowOf(contact));
		window.m_AddressBook->SetEditing(true);

		//emit window.btndiag_confirm->released();
		window.m_AddressBook->SetInsertion(true);
	});

	// Allow the user to edit or delete a contact, depending on what button is clicked
	window.connect(window.btndiag_confirm, &QDialogButtonBox::clicked, &window, [&window](QAbstractButton* button) {
		QDialogButtonBox::ButtonRole role = window.btndiag_confirm->buttonRole(button);

		switch (role) {
			case QDialogButtonBox::ActionRole: // The edit button
				window.m_AddressBook->SetEditing(true);
				break;
			case QDialogButtonBox::DestructiveRole: // The delete button
				window.m_AddressBook->Delete(window.contactsList->currentRow());
				break;
			default:
				break;
		}
	});

	// Allow the user to apply changes to contacts
	window.connect(window.btndiag_confirm, &QDialogButtonBox::accepted, &window, [&window]() {
		int row = window.contactsList->currentRow();
		Contact* contact = window.m_AddressBook->At(row);

		contact->Update(
			window.nameField->text().toStdString(), window.usernameField->text().toStdString(),
			window.addressField->text().toStdString(), window.birthday->date()
		);
		window.m_AddressBook->Update(contact, row);

		window.m_AddressBook->SetEditing(false);
		window.contactsList->selectRow(window.m_AddressBook->GetRowOf(contact));

		window.m_AddressBook->SetInsertion(false);
	});

	// Allow the user to cancel changes to contacts
	window.connect(window.btndiag_confirm, &QDialogButtonBox::rejected, &window, [&window]() {
		int row = window.contactsList->currentRow();
		Contact* contact = window.m_AddressBook->At(row);

		window.m_AddressBook->SetEditing(false);
		window.ShowContact(contact); // Ensure all changes have been reset, then reshow the contact info

		if (window.m_AddressBook->IsInserting()) {
			window.m_AddressBook->Delete(row);
		}

		window.m_AddressBook->SetInsertion(false);
	});

}

void transactionPage(MainWindow& window) {
	// Set an initial value for the total
	double amount = window.amountSelector->value();
	double fee = window.feeSelector->value();
	int precision = window.amountSelector->decimals();
	Transaction* finalTransaction = nullptr;

	window.total->setText(QString::number(amount + fee, 'f', precision));

	// Allow a user to select a recipient for the transaction
	window.connect(window.contacts, &QListWidget::itemSelectionChanged, &window, [&window]() {
		int row = window.contacts->currentRow();
		window.selectedContact->setText(window.contacts->item(row)->text());

		if (window.m_TransactionManager->CheckFields()) {
			window.m_TransactionManager->AllowSend();
		}
		else {
			window.m_TransactionManager->DisallowSend();
		}
	});

	// Update the total when the transaction amount changes
	window.connect(window.amountSelector, QOverload<double>::of(&QDoubleSpinBox::valueChanged), &window, [&window](double amount) {
		double fee = window.feeSelector->value();
		int precision = window.amountSelector->decimals();

		window.total->setText(QString::number(amount + fee, 'f', precision));

		if (window.m_TransactionManager->CheckFields()) {
			window.m_TransactionManager->AllowSend();
		}
		else {
			window.m_TransactionManager->DisallowSend();
		}
	});

	// Update the total when the transaction fee changes
	window.connect(window.feeSelector, QOverload<double>::of(&QDoubleSpinBox::valueChanged), &window, [&window](double fee) {
		double amount = window.amountSelector->value();
		int precision = window.amountSelector->decimals();

		window.total->setText(QString::number(amount + fee, 'f', precision));

		if (window.m_TransactionManager->CheckFields()) {
			window.m_TransactionManager->AllowSend();
		}
		else {
			window.m_TransactionManager->DisallowSend();
		}
	});

	// Update the character count while typing a message to the recipient
	window.connect(window.messageField, &QLineEdit::textChanged, &window, [&window](const QString& text) {
		window.charCount->setText(
			"<html><head/><body><p align=\"right\"><span style=\"font-size:8pt;\">" + \
			QString::number(text.size()) + "/200</span></p></body></html>"
		);
	});

	// Create a new transaction
	window.connect(window.btndiag_send, &QDialogButtonBox::accepted, &window, [&window, finalTransaction]() mutable {
		int row = window.contacts->currentRow();

		// Collect transaction data
		string recipientAddr = window.m_AddressBook->At(row)->GetAddress();
		double amount = window.amountSelector->value();
		double fee = window.feeSelector->value();

		QString text = window.messageField->text();
		string content = text.isEmpty()? "" : text.toStdString();

		// Create a new transaction
		finalTransaction = window.m_User->MakeTransaction(recipientAddr, amount, fee, content);

		int result = window.m_TransactionManager->ConfirmTrxn(finalTransaction);

		// If the OK button is pressed, sign and broadcast the transaction
		if (result == QMessageBox::Ok) {
			window.m_User->Sign(*finalTransaction);

			Transmitter* transmitter = new Transmitter();
			auto data = transmitter->Format(finalTransaction);
			transmitter->Transmit(data, std::stoi(data[0]));

			window.m_TransactionList->Add(finalTransaction);

			string result = shared_mem::readMemory();
			std::cout << "Result: " << result << std::endl;

			delete transmitter;
		}
	});

	// Calculate transaction fees for the user when the button is clicked
	window.connect(window.btndiag_send, &QDialogButtonBox::clicked, &window, [&window](QAbstractButton* button) {
		QDialogButtonBox::ButtonRole role = window.btndiag_send->buttonRole(button);

		// The fee calculation button
		if (role == QDialogButtonBox::ActionRole) {
			window.feeSelector->setValue(calculateFee(window));
		}
	});
}

// Allow the user to add transactions to their block
void addToBlock(MainWindow& window) {
	window.connect(window.plusSign, &QToolButton::released, &window, [&window]() {
		auto selected = window.transactionList->selectedItems();
		int row = window.transactionList->currentRow();

		// A user will only be able to add a transaction if:
		//
		// 1) They have selected a transaction from the list on the right (no blank selections)
		// 2) They have not added that transaction previously (no adding duplicate elements)
		//
		if ((selected.size() != 0) && (window.blockTransactionList->findItems(selected.front()->text(), Qt::MatchFixedString).size() == 0)) {
			QListWidgetItem* item = window.transactionList->item(row); // Get the item at the currently selected row

			window.m_BlockContents.push_back(window.m_TransactionList->At(row)); // Record the selected item
			window.blockTransactionList->addItem(item->text());
		}
	});
}

// Allow the user to remove transactions from their block
void removeFromBlock(MainWindow& window) {
	window.connect(window.minusSign, &QToolButton::released, &window, [&window]() {
		// To remove a transaction, the only requirement is that it's been selected on
		// the list of transactions in user's block
		if (window.blockTransactionList->selectedItems().size() != 0) {
			int row = window.blockTransactionList->currentRow();
			QListWidgetItem* item = window.blockTransactionList->item(row); // get the item at the currently selected row

			window.m_BlockContents.erase(window.m_BlockContents.begin() + row); // Remove the selected item
			window.blockTransactionList->takeItem(row);
		}
	});
}

void manageSharedMem() {
	constexpr bool immediate = true;

	string data = shared_mem::readMemory(immediate);
	QJsonObject object = json::parse(data);

	uint8_t packetType = json::getPacketType(object);

	switch (packetType) {
		case static_cast<uint8_t>(go::PacketTypes::TRANSACTION):
			break;
	}
}

double calculateFee(MainWindow& window) {
	int row = window.contacts->currentRow();

	// Collect transaction data
	string recipientAddr = window.m_AddressBook->At(row)->GetAddress();
	double amount = window.amountSelector->value();
	double fee = window.feeSelector->value();

	QString text = window.messageField->text();
	string content = text.isEmpty()? "" : text.toStdString();

	// Create a new transaction. This transaction's size will be calulated using the current working
	// transaction data to give the user an idea of how much they will pay in transaction fees.
	Transaction* transaction = window.m_User->MakeTransaction(recipientAddr, amount, fee, content);
	window.m_User->Sign(*transaction); // Simulate signing the transaction

	// The transaction fee is 0.00001 Plasmacoins per byte of transaction data
	double predictedFee = pow(10, -5) * dssize::size(*transaction);

	delete transaction;
	return predictedFee;
}

// Run the application
int main(int argc, char* argv[]) {
	QApplication app(argc, argv);

	QPixmap pixmap("../assets/plasmacoin-banner.png");
    QSplashScreen splashScreen(pixmap);
    splashScreen.show();

	MainWindow window;
	window.show();

	window.plusSign->setIcon(QIcon("../assets/plus.png"));
	window.minusSign->setIcon(QIcon("../assets/minus.png"));

	window.btn_reset->setIcon(QIcon("../assets/reset.png"));

	window.addressCopy->setIcon(QIcon("../assets/clipboard.png"));
	window.pubKeyCopy->setIcon(QIcon("../assets/clipboard.png"));
	window.privKeyCopy->setIcon(QIcon("../assets/clipboard.png"));

	window.pubKeyShow->setIcon(QIcon("../assets/view.png"));
	window.privKeyShow->setIcon(QIcon("../assets/view.png"));

	window.bannerText1->setText("<html><head/><body><p align=\"center\"><span style=\"font-size:24pt; color:#000000;\">Welcome Back!</span></p><p align=\"center\"><span style=\"font-size:24pt; color:#000000;\">Please sign in to continue.</span><span style=\"color:#000000;\"><br/></span></p><p align=\"center\"><br/></p><p align=\"center\"><br/></p><p align=\"center\"><br/></p><p align=\"center\"><br/></p><p align=\"center\"><br/></p><p align=\"center\"><br/></p><p align=\"center\"><br/></p><p align=\"center\"><br/><br/></p><p align=\"center\"><img src=\"../assets/plasmacoin-banner.png\" width=\"550\" height=\"150\"/></p></body></html>");

	window.contactImage->setPixmap(QPixmap("../assets/contact-default.png"));
	window.btn_addContact->setIcon(QIcon("../assets/plus.png"));

	splashScreen.finish(&window);

	// Connect everything
	minePage(window);
	accountPages(window);
	addressBook(window);
	transactionPage(window);
	addToBlock(window);
	removeFromBlock(window);

	return app.exec();
}
