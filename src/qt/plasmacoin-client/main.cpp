
#include <QApplication>
#include <QPushButton>
#include <QListWidget>
#include <QListWidgetItem>
#include <QSplashScreen>
#include <QDialogButtonBox>
#include <QSignalBlocker>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "firebase-auth.h"

// Allow the user to mine their block
void minePage(MainWindow& window) {
	window.m_Status->m_Heading->setVisible(true); // Show the status heading

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
		// Hide all the warning labels
		window.m_AccPgs->m_EmailSignInWarning->setVisible(false);
		window.m_AccPgs->m_PasswordSignInWarning->setVisible(false);
		window.m_AccPgs->m_EmailSignUpWarning->setVisible(false);
		window.m_AccPgs->m_UsernameWarning->setVisible(false);
		window.m_AccPgs->m_PasswordSignUpWarning->setVisible(false);

		// Use bit masking to warn about certain errors
		for (uint8_t code = Auth::EMAIL_EXISTS, i = 0; i < Auth::LAST; code = 1 << ++i) {
			if (window.m_Authenticator->m_Errors & code) {
				switch (code) {
					case Auth::EMAIL_EXISTS:
						emit window.m_Authenticator->EmailExists();
						break;

					case Auth::USERNAME_TAKEN:
						emit window.m_Authenticator->UsernameTaken();
						break;

					case Auth::INVALID_EMAIL:
						emit window.m_Authenticator->InvalidEmail();
						break;

					case Auth::INVALID_USERNAME:
						emit window.m_Authenticator->InvalidUsername();
						break;

					case Auth::INVALID_PASSWORD:
						emit window.m_Authenticator->InvalidPassword();
						break;

					default:
						break;
				}
			}
		}
	});

	// Take the user to the logged in view if Firebase successfully logged them in
	window.connect(window.m_Authenticator, &Auth::FinishedRequest, &window, [&window]() {
		if (!window.m_Authenticator->SearchFor("error") && window.m_Authenticator->m_Errors == 0) {
			window.m_AccPgs->DisplayPage(2);
		}
	});

	// Display a warning when a user tries to create an account with an email that's in use
	window.connect(window.m_Authenticator, &Auth::EmailExists, &window, [&window]() {
		window.m_AccPgs->m_EmailSignUpWarning->setText("Email in use");
		window.m_AccPgs->m_EmailSignUpWarning->setVisible(true);
	});

	// Display a warning when a user tries to create an account with an invalid email
	window.connect(window.m_Authenticator, &Auth::InvalidEmail, &window, [&window]() {
		if (window.accountView->currentIndex() == 0) {
			window.m_AccPgs->m_EmailSignInWarning->setText("Invalid Email");
			window.m_AccPgs->m_EmailSignInWarning->setVisible(true);
		}
		else {
			window.m_AccPgs->m_EmailSignUpWarning->setText("Invalid email");
			window.m_AccPgs->m_EmailSignUpWarning->setVisible(true);
		}
	});

	// Display a warning when a user tries to create an account with an email that's in use
	window.connect(window.m_Authenticator, &Auth::UsernameTaken, &window, [&window]() {
		window.m_AccPgs->m_UsernameWarning->setText("Username already in use");
		window.m_AccPgs->m_UsernameWarning->setVisible(true);
	});

	// Display a warning when a user tries to create an account with an invalid username
	window.connect(window.m_Authenticator, &Auth::InvalidUsername, &window, [&window]() {
		window.m_AccPgs->m_UsernameWarning->setText("Username invalid");
		window.m_AccPgs->m_UsernameWarning->setVisible(true);
	});

	// Display a warning when a user tries to create an account with an invalid password
	window.connect(window.m_Authenticator, &Auth::InvalidPassword, &window, [&window]() {
		if (window.accountView->currentIndex() == 0) {
			window.m_AccPgs->m_PasswordSignInWarning->setText("Password invalid");
			window.m_AccPgs->m_PasswordSignInWarning->setVisible(true);
		}
		else {
			window.m_AccPgs->m_PasswordSignUpWarning->setText("Password invalid");
			window.m_AccPgs->m_PasswordSignUpWarning->setVisible(true);
		}
	});
}

void addressBook(MainWindow& window) {
	window.btndiag_confirm->setVisible(false);

	// Display contact info when the corresponding table object is selected
	window.connect(window.contactsList, &QTableWidget::itemSelectionChanged, &window, [&window]() {
		int row = window.contactsList->currentRow();
		window.ShowContact(window.m_AddressBook->At(row));
	});

	// Allow the user to add a contact
	window.connect(window.btn_addContact, &QToolButton::released, &window, [&window]() {
		Contact* contact = new Contact("New Contact", "", "", QDate());
		window.m_AddressBook->Add(contact);

		window.contactsList->selectRow(window.m_AddressBook->GetRowOf(contact));
		window.m_AddressBook->SetEditing(true);

		emit window.btn_edit->released();
		window.m_AddressBook->SetInsertion(true);
	});

	// Allow the user to delete a contact
	window.connect(window.btn_delete, &QPushButton::released, &window, [&window]() {
		int row = window.contactsList->currentRow();
		window.m_AddressBook->Delete(row);
	});

	// Allow the user to edit a contact
	window.connect(window.btn_edit, &QPushButton::released, &window, [&window]() {
		window.btn_edit->setVisible(false);
		window.btndiag_confirm->setVisible(true);
		window.btn_delete->move(930, 520);

		int row = window.contactsList->currentRow();
		window.m_AddressBook->SetEditing(true);
	});

	// Allow the user to apply changes to contacts
	window.connect(window.btndiag_confirm, &QDialogButtonBox::accepted, &window, [&window]() {
		window.btndiag_confirm->setVisible(false);
		window.btn_edit->setVisible(true);
		window.btn_delete->move(900, 520);

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
		window.btndiag_confirm->setVisible(false);
		window.btn_edit->setVisible(true);
		window.btn_delete->move(900, 520);

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

			window.m_BlockContents.push_back(window.m_TList->m_List[row]); // Record the selected item
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
	addToBlock(window);
	removeFromBlock(window);

	return app.exec();
}
