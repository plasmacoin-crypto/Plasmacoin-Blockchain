//
// FILENAME: mainwindow.cpp | Plasmacoin Cryptocurrency
// DESCRIPTION: The source file for mainwindow.h
// CREATED: 2021-03-21 @ 3:47 PM
// COPYRIGHT: Copyright (c) 2021 by Ryan Smith <rysmith2113@gmail.com>
//

#include "mainwindow.h"

MainWindow::MainWindow(QWidget* parent):
	QMainWindow(parent),
	parent(parent),
	m_Authenticator(new Auth()),
	//m_SettingsManager(new SettingsManager()),
	m_TList(new TransactionList(Ui::MainWindow::transactionList))
{
	setupUi(this);
	tabWidget->setCurrentIndex(0);

	m_FormErrorAlert = new QMessageBox();

	m_Status = CreateMiningVisuals();
	m_AccPgs = CreatePages();
	m_AddressBook = new AddressBook(
						Ui::MainWindow::contactsList, m_NameDisplay, Ui::MainWindow::nameField, m_UsernameDisplay,
						Ui::MainWindow::usernameField, m_AddressDisplay, Ui::MainWindow::addressField,
						Ui::MainWindow::birthday, Ui::MainWindow::btndiag_confirm, Ui::MainWindow::field1,
						Ui::MainWindow::field2, Ui::MainWindow::field3, Ui::MainWindow::field4
					);
	m_TransactionManager = new TransactionManager(Ui::MainWindow::contacts, Ui::MainWindow::transactionLog);

	// Create some temporary nodes to make transactions between
	// Node* node1 = new Node("Ryan", "ryan", "1234", "192.168.1.6");
	// Node* node2 = new Node("John", "john", "4567", "192.168.1.7", string(getenv("HOME")) + "/.ssh/node2keys/");
	// Node* node3 = new Node("Bill", "bill", "8901", "192.168.1.8", string(getenv("HOME")) + "/.ssh/node3keys/");

	// Transaction* transaction1 = node1->MakeTransaction(node2->GetAddress(), 1.0, 0.1, "Here's some money");
	// Transaction* transaction2 = node2->MakeTransaction(node3->GetAddress(), 5.7, 0.1, "Here's some money");
	// Transaction* transaction3 = node3->MakeTransaction(node1->GetAddress(), 2.1, 0.1, "Here's some money");

	// Load items into the transaction list
	// m_TList->Add(transaction1);
	// m_TList->Add(transaction2);
	// m_TList->Add(transaction3);

	m_Status->SetHeading("Building Block #" + std::to_string(m_User->m_BlockchainCopy->Size()));

	connect(Ui::MainWindow::btn_choosePath, &QPushButton::released, this, [=]() {
		qDebug() << this->m_FileBrowser->getSaveFileName(
											Ui::MainWindow::Settings, QFileDialog::tr("Choose an RSA output location"),
											QString::fromStdString(rsafs::HOME_DIR), QFileDialog::tr("Text Files (*.txt);;All Files (*.*, *)"),
											nullptr, QFileDialog::DontUseNativeDialog
										);
	});

	// Add a contact to the list
	Contact* contact1 = new Contact("Ryan", "rmsmith", "pca12345", QDate(2005, 2, 16));
	Contact* contact2 = new Contact("John", "jdoe", "pca67890", QDate(1999, 9, 9));
	Contact* contact3 = new Contact("Alexander", "alex", "pca31415", QDate(2000, 1, 1));

	m_AddressBook->Add(contact1);
	m_AddressBook->Add(contact2);
	m_AddressBook->Add(contact3);

	m_AddressBook->Sort();

	m_TransactionManager->UpdateContactsList(m_AddressBook);
}

MainWindow::~MainWindow() {
	delete m_Status;
	delete m_Authenticator;
	delete m_TList;
	delete m_AccPgs;
	delete m_FileBrowser;
	delete m_AddressBook;
}

// Create QTextBrowsers to display on the mining tab
Status* MainWindow::CreateMiningVisuals() {
	// The four widgets to display on the screen once a block has been mined.
	QTextBrowser *browser1 = new QTextBrowser(Ui::MainWindow::Mine),
				 *browser2 = new QTextBrowser(Ui::MainWindow::Mine),
				 *browser3 = new QTextBrowser(Ui::MainWindow::Mine),
				 *browser4 = new QTextBrowser(Ui::MainWindow::Mine);

 	return new Status(browser1, browser2, browser3, browser4);
}

AccountPages* MainWindow::CreatePages() {
	// Create warning labels for all 5 input fields
	QLabel *label1 = new QLabel("", Ui::MainWindow::signIn),
		   *label2 = new QLabel("", Ui::MainWindow::signIn),
		   *label3 = new QLabel("", Ui::MainWindow::signUp),
	 	   *label4 = new QLabel("", Ui::MainWindow::signUp),
	 	   *label5 = new QLabel("", Ui::MainWindow::signUp);

	return new AccountPages(Ui::MainWindow::accountView, label1, label2, label3, label4, label5, m_FormErrorAlert);
}

// Call block mining code and make visual changes to the GUI once it's done
void MainWindow::StartMining() {
	Block* latest = m_User->m_BlockchainCopy->GetLatest(); // Get the latest block
	Block newBlock(latest->m_Index + 1, latest->m_Hash, m_BlockContents); // Create a new block

	auto start = high_resolution_clock::now(); // Begin timing the function

	bool success = false, valid = false;
	uint8_t code;

	std::tie(success, code) = m_User->m_BlockchainCopy->Mine(newBlock); // Mine the block

	std::cout << "Success: " << success << std::endl;
	std::cout << "Code: " << (uint)code << std::endl;

	auto stop = high_resolution_clock::now(); // End timing
	m_LastMiningDur = std::chrono::duration_cast<seconds>(stop - start); // Find the duration

	// NOTE: Ideally, the blockchain will be validated without altering even the user's
	// personal copy first.
	if (success) {
		m_User->m_BlockchainCopy->Add(&newBlock);
		valid = m_User->m_BlockchainCopy->Validate();
	}

	if (valid) {
		emit MiningSuccess();
	}
	else {
		emit MiningFailure();
	}
}

void MainWindow::ResetBlock() {
	m_BlockContents.clear();
	blockTransactionList->clear();
}

void MainWindow::UpdateStatus(const Block& block, seconds time) {
	m_Status->SetHeading("Finishing Block #" + std::to_string(block.m_Index));

	m_Status->SetHash(block.m_Hash);
	m_Status->SetNonce(block.m_Nonce);
	m_Status->SetTime(time);

	m_Status->LoadVisuals();
}

void MainWindow::ShowContact(Contact* contact) {
	// Set the read only fields
	m_NameDisplay->setText(QString::fromStdString(contact->GetName()));
	m_UsernameDisplay->setText(QString::fromStdString(contact->GetUsername()));
	m_AddressDisplay->setText(QString::fromStdString(contact->GetAddress()));

	// Set the writable fields
	nameField->setText(QString::fromStdString(contact->GetName()));
	usernameField->setText(QString::fromStdString(contact->GetUsername()));
	addressField->setText(QString::fromStdString(contact->GetAddress()));

	birthday->setDate(contact->GetBirthday()); // Set the birthday
}
