//
// FILENAME: connections.cpp | Plasmacoin Cryptocurrency
// DESCRIPTION: The source file for connections.hpp
// CREATED: 2022-02-06 @ 10:57 PM
// COPYRIGHT: Copyright (c) 2022 by Ryan Smith <rysmith2113@gmail.com>
//

#include "connections.hpp"

// Allow the user to mine their block
void connections::minePage(MainWindow& window) {
	//window.m_Status->m_Heading->setVisible(true); // Show the status heading

	// Mine a block when the correct button is clicked
	window.connect(window.btn_mine, &QPushButton::released, &window, [&window]() {
		window.m_Status->SetHeading("Mining Block #" + std::to_string(window.m_User->m_BlockchainCopy->Size()));

		std::thread mineThread(&MainWindow::StartMining, &window);
		mineThread.detach();
	});

	// Display information about a transaction when a user selects it
	window.connect(window.transactionList, &QListWidget::itemSelectionChanged, &window, [&window]() {
		int row = window.transactionList->currentRow();
		window.m_TransactionView->Display(window.m_TransactionList->At(row));
	});
}

// Allow the user to type information in forms (QLineEdits) and be authenticated to
// the app through the Firebase REST API
void connections::accountPages(MainWindow& window) {
	#ifdef BETA_RELEASE
		window.btn_continue->setEnabled(false);

		// Take a user from the beta key entry screen to the sign up screen
		window.connect(window.btn_continue, &QPushButton::released, &window, [&window]() {
			window.m_AccPgs->DisplayPage(2);
		});

		window.connect(window.betaKeyField, &QLineEdit::textEdited, &window, [&window](const QString& text) {
			if (text.size() > 4 && !text.isEmpty()) {
				window.btn_continue->setEnabled(true);
			}
			else {
				window.btn_continue->setEnabled(false);
			}

			window.betaKeyField->setText(text.toUpper());
		});
	#endif

	// Take a user from the sign in screen to the sign up screen
	window.connect(window.btn_create, &QPushButton::released, &window, [&window]() {
		window.m_AccPgs->DisplayPage(2);
	});

	// Take a user from the sign up screen back to the sign in screen
	window.connect(window.btn_back, &QPushButton::released, &window, [&window]() {
		window.m_AccPgs->DisplayPage(1);
	});

	// Sign a user into their account
	window.connect(window.btn_signIn, &QPushButton::released, &window, [&window]() {
		QString email, username, password;
		std::tie(email, username, password) = window.m_AccPgs->ReadText(); // Get the user's entries

		// Cache the user's credentials if they checked "Remember Me"
		if (window.s_RememberMe->isChecked()) {
			window.m_AccPgs->CacheCredentials(email.toStdString(), password.toStdString());
		}

		window.m_Authenticator->SignIn(email, password);
	});

	// Sign a user up for their account
	window.connect(window.btn_signUp, &QPushButton::released, &window, [&window]() {
		QString email, username, password;
		std::tie(email, username, password) = window.m_AccPgs->ReadText(); // Get the user's entries

		// Cache the user's credentials if they checked "Remember Me"
		if (window.c_RememberMe->isChecked()) {
			window.m_AccPgs->CacheCredentials(email.toStdString(), password.toStdString());
		}

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
					case static_cast<uint8_t>(Auth::ErrorCodes::INVALID_PASSWORD):
						detailedText += "Invalid username or password\n";
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

	window.connect(window.m_Authenticator, &Auth::Authenticated, &window, [&window]() {
		window.m_AccPgs->DisplayPage(3);
	});
}

void connections::addressBook(MainWindow& window) {
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

void connections::transactionPage(MainWindow& window) {
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
			window.m_TransactionManager->ProhibitSend();
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
			window.m_TransactionManager->ProhibitSend();
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
			window.m_TransactionManager->ProhibitSend();
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

		if (!window.m_Wallet->IsPossible(finalTransaction)) {
			window.m_TransactionManager->ShowWarning(window.m_Wallet->GetAvailableBal(), finalTransaction);
			return;
		}

		int result = window.m_TransactionManager->AskForConf(finalTransaction);

		// If the OK button is pressed, sign and broadcast the transaction
		if (result == QMessageBox::Ok) {
			window.m_User->Sign(*finalTransaction);

			Transmitter* transmitter = new Transmitter();
			auto data = transmitter->Format(finalTransaction);

			transmitter->Transmit(data, std::stoi(data[0]), window.m_User->GetKnownHosts());

			window.m_TransactionList->Add(finalTransaction);

			std::this_thread::sleep_for(std::chrono::milliseconds(300));

			string result = shared_mem::readMemory(true);
			std::cout << "Result: " << result << std::endl;

			window.m_Wallet->UpdatePendingBal(Wallet::WalletActions::WITHDRAW, finalTransaction->m_Amount + finalTransaction->m_Fee);
			window.UpdateAmounts();

			// Send a pending transaction notification to the recipient
			PendingTransaction pendingTrxn {
				finalTransaction->m_CreationTime,
				finalTransaction->m_Hash,
				QString::number(finalTransaction->m_Amount, 'f', 10).toDouble()
			};
			data = transmitter->Format(&pendingTrxn);
			transmitter->Transmit(data, std::stoi(data[0]), {"192.168.1.58"});

			delete transmitter;
		}
	});

	// Calculate transaction fees for the user when the button is clicked
	window.connect(window.btndiag_send, &QDialogButtonBox::clicked, &window, [&window](QAbstractButton* button) {
		QDialogButtonBox::ButtonRole role = window.btndiag_send->buttonRole(button);

		// The fee calculation button
		if (role == QDialogButtonBox::ActionRole) {
			window.feeSelector->setValue(connections::calculateFee(window));
		}
	});
}

void connections::blockchainPage(MainWindow& window) {
	window.UpdateButtons();

	window.connect(window.btn_first, &QToolButton::released, &window, [&window]() {
		window.m_BlockchainViewer->Genesis();
		window.UpdateButtons();
	});

	window.connect(window.btn_previous, &QToolButton::released, &window, [&window]() {
		window.m_BlockchainViewer->Previous();
		window.UpdateButtons();
	});

	window.connect(window.btn_next, &QToolButton::released, &window, [&window]() {
		window.m_BlockchainViewer->Next();
		window.UpdateButtons();
	});

	window.connect(window.btn_last, &QToolButton::released, &window, [&window]() {
		window.m_BlockchainViewer->Latest();
		window.UpdateButtons();
	});

	window.connect(window.blockView, &QTableWidget::itemSelectionChanged, &window, [&window]() {
		int row = window.blockView->currentRow(), rows = window.blockView->rowCount();
		QTableWidgetItem* field = window.blockView->item(row, 0); // Get the field name of the selected row

		// Get the block currently being displayed
		int index = window.m_BlockchainViewer->GetIndex();
		Block* block = window.m_User->m_BlockchainCopy->Get(index);

		// Display transaction data for the displayed block if the user clicks on a transaction
		if (field->text() == "Transaction") {
			Transaction* transaction = block->m_Transactions[rows - row - 1];
			window.m_BlockchainViewer->ShowTransaction(transaction);
		}
		else {
			window.blockTrxnView->setRowCount(0);
		}
	});

	window.connect(window.btn_sync, &QToolButton::released, &window, [&window]() {
		window.SyncBlockchain();
		window.ManageSyncedData();
	});
}

void connections::settingsPage(MainWindow& window) {
	window.m_SettingsManager->PopulateComboBoxes();
	uint8_t settings;
	constexpr double exampleValue = 123.456l;

	auto notifClickEvent = [&window, &settings](int state) mutable {
		settings = window.m_SettingsManager->GetNotificationSettings();

		if (
			settings == NotificationSettings::CHILDREN_CHECKED ||
			settings == NotificationSettings::ALL_CHECKED
		) {
			window.enableNotifs->setCheckState(Qt::CheckState::Checked);
		}
		else if (
			settings == NotificationSettings::CHILDREN_UNCHEKED ||
			settings == NotificationSettings::NONE_CHECKED
		) {
			window.enableNotifs->setCheckState(Qt::CheckState::Unchecked);
		}
		else if (
			state == Qt::Unchecked && (settings & static_cast<uint8_t>(NotificationSettings::Notifications::ENABLED)) &&
			(settings < NotificationSettings::CHILDREN_CHECKED && settings > NotificationSettings::CHILDREN_UNCHEKED)
		) {
			window.enableNotifs->setCheckState(Qt::CheckState::PartiallyChecked);
		}
	};

	window.connect(window.portMapSelector, &QComboBox::currentIndexChanged, &window, [&window](int index) {
		switch (index) {
			case enums::PortMappingProtocol::UPNP:
				window.portfSubmenu->setVisible(false);
				window.upnpSubmenu->setVisible(true);
				break;

			case enums::PortMappingProtocol::PORT_FORWARDING:
				window.upnpSubmenu->setVisible(false);
				window.portfSubmenu->setVisible(true);
				break;
		}
	});

	window.connect(window.padTypeSelector, &QComboBox::currentIndexChanged, &window, [&window](int index) {
		switch (index) {
			case enums::PaddingType::MAXIMUM:
				window.customPrecision->setVisible(false);
				window.exampleBalance->setText(QString("Example: %1").arg(QString::number(exampleValue, 'f', 10)));
				break;

			case enums::PaddingType::NONE:
				window.customPrecision->setVisible(false);
				window.exampleBalance->setText(QString("Example: %1").arg(QString::number(exampleValue, 'f', utility::getDecimals(exampleValue))));
				break;

			case enums::PaddingType::CUSTOM:
				window.customPrecision->setVisible(true);
				break;

			default:
				break;
		}
	});

	window.connect(window.paddingSelector, &QSpinBox::valueChanged, &window, [&window](int padding) {
		int decimals = utility::getDecimals(exampleValue);
		int zeros = (decimals < 10 && decimals + padding <= 10)? decimals + padding : 10;

		window.exampleBalance->setText(QString("Example: %1").arg(QString::number(exampleValue, 'f', zeros)));
	});

	window.connect(window.btn_autoctz, &QToolButton::released, &window, [&window]() {
		window.m_SettingsManager->DetectLocale();
	});

	window.connect(window.enableNotifs, &QCheckBox::stateChanged, &window, [&window, &settings](int state) mutable {
		switch (state) {
			case Qt::CheckState::Unchecked:
				window.enableNotifs->setTristate(false);

				// When notifications are disabled, hide the specific notification settings
				connections::uncheckAll(window);
				connections::hideNotifChildren(window);

				break;

			case Qt::CheckState::Checked:
				window.enableNotifs->setTristate(false);

				// When notifications are enabled, show the specific notification settings
				connections::checkAll(window);
				connections::showNotifChildren(window);

				break;

			default:
				break;
		}

		settings = window.m_SettingsManager->GetNotificationSettings();
	});

	window.connect(window.pendingTrxnNotifs, &QCheckBox::stateChanged, &window, notifClickEvent);
	window.connect(window.receiptNotifs, &QCheckBox::stateChanged, &window, notifClickEvent);
	window.connect(window.miningNotifs, &QCheckBox::stateChanged, &window, notifClickEvent);
	window.connect(window.syncNotifs, &QCheckBox::stateChanged, &window, notifClickEvent);
}

void connections::aboutPage(MainWindow& window) {
	connections::updateTitles(window);

	// Open a link in the user's web browser
	auto openLink = [](const QString& link) {
		QDesktopServices::openUrl(QUrl(link));
	};

	window.connect(window.licenseInfo, &QLabel::linkActivated, &window, openLink);
	window.connect(window.qtLink, &QLabel::linkActivated, &window, openLink);
	window.connect(window.boostLink, &QLabel::linkActivated, &window, openLink);
	window.connect(window.cryptoppLink, &QLabel::linkActivated, &window, openLink);
}

void connections::updateWalletAmounts(MainWindow& window) {
	window.connect(&window, &MainWindow::UpdateWalletAmounts, &window, [&window] {
		window.UpdateAmounts();
	});
}

// Allow the user to add transactions to their block
void connections::addToBlock(MainWindow& window) {
	window.connect(window.plusSign, &QToolButton::released, &window, [&window]() {
		auto selected = window.transactionList->selectedItems();
		int row = window.transactionList->currentRow();

		// A user will only be able to add a transaction if:
		//
		// 1) They have selected a transaction from the list on the right (no blank selections)
		// 2) They have not added that transaction previously (no adding duplicate elements)
		//
		if ((selected.size() != 0) && (window.blockContents->findItems(selected.front()->text(), Qt::MatchFixedString).size() == 0)) {
			QListWidgetItem* item = window.transactionList->item(row); // Get the item at the currently selected row

			window.m_BlockContents.push_back(window.m_TransactionList->At(row)); // Record the selected item
			window.blockContents->addItem(item->text());
		}
	});
}

// Allow the user to remove transactions from their block
void connections::removeFromBlock(MainWindow& window) {
	window.connect(window.minusSign, &QToolButton::released, &window, [&window]() {
		// To remove a transaction, the only requirement is that it's been selected on
		// the list of transactions in user's block
		if (window.blockContents->selectedItems().size() != 0) {
			int row = window.blockContents->currentRow();
			QListWidgetItem* item = window.blockContents->item(row); // get the item at the currently selected row

			window.m_BlockContents.erase(window.m_BlockContents.begin() + row); // Remove the selected item
			window.blockContents->takeItem(row);
		}
	});
}

double connections::calculateFee(MainWindow& window) {
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
	double predictedFee = std::pow(10, -5) * dssize::size(*transaction);

	delete transaction;
	return predictedFee;
}

void connections::showNotifChildren(MainWindow& window) {
	window.pendingTrxnNotifs->setVisible(true);
	window.receiptNotifs->setVisible(true);
	window.miningNotifs->setVisible(true);
	window.syncNotifs->setVisible(true);
}

void connections::hideNotifChildren(MainWindow& window) {
	window.pendingTrxnNotifs->setVisible(false);
	window.receiptNotifs->setVisible(false);
	window.miningNotifs->setVisible(false);
	window.syncNotifs->setVisible(false);
}

void connections::checkAll(MainWindow& window) {
	window.pendingTrxnNotifs->setChecked(true);
	window.receiptNotifs->setChecked(true);
	window.miningNotifs->setChecked(true);
	window.syncNotifs->setChecked(true);
}

void connections::uncheckAll(MainWindow& window) {
	window.pendingTrxnNotifs->setChecked(false);
	window.receiptNotifs->setChecked(false);
	window.miningNotifs->setChecked(false);
	window.syncNotifs->setChecked(false);
}

void connections::updateTitles(MainWindow& window) {
	string year = utility::formatEpoch(utility::getUnixEpoch(), "%Y");
	string releaseYear = std::to_string(INITIAL_RELEASE_YEAR);
	string dateRange = (std::stoi(year) > INITIAL_RELEASE_YEAR)? releaseYear + "-" + year : releaseYear;

	// Set the about page titles from the version info macros
	window.versionInfo->setText(
		QString(
			"<html><head/><body><p align=\"center\"><span style=\"font-size:24pt;\">"
			"Plasmacoin Client (%1)"
			"</span></p></body></html>"
		).arg("v" + QCoreApplication::applicationVersion())
	);

	window.copyrightNotice->setText(
		QString(
			"<html><head/><body><p align=\"center\"><span style=\"font-size:24pt;\">Copyright</span>"
			"<span style=\"font-size:18pt; vertical-align:super;\">©</span>"
			"<span style=\"font-size:24pt;\"> %1 Ryan Smith</span></p></body></html>"
		).arg(QString::fromStdString(dateRange))
	);
}