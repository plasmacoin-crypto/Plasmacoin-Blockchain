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
	m_TransactionList(new TransactionList(Ui::MainWindow::transactionList))
{
	shared_mem::deleteMemory(shared_mem::FILENAME);
	shared_mem::deleteMemory(shared_mem::READER_FILENAME);
	shared_mem::deleteMemory(shared_mem::WRITER_FILENAME);

	Ui_MainWindow::setupUi(this);

	// std::future<void> manageSharedMem = std::async([this](std::atomic<bool>& running) {
	// 	this->ManageSharedMem(running);
	// }, std::ref(runningThread));

	tabWidget->setCurrentIndex(0);

	m_FormErrorAlert = new QMessageBox(); // Create a message box to display authentication errors
	m_ConfirmTransaction = new QMessageBox(); // Create a message box to sign and send a transaction

	m_Status = CreateMiningVisuals();
	m_AccPgs = CreatePages();
	m_AddressBook = new AddressBook(
						Ui::MainWindow::contactsList, m_NameDisplay, Ui::MainWindow::nameField, m_UsernameDisplay,
						Ui::MainWindow::usernameField, m_AddressDisplay, Ui::MainWindow::addressField,
						Ui::MainWindow::birthday, Ui::MainWindow::btndiag_confirm, Ui::MainWindow::field1,
						Ui::MainWindow::field2, Ui::MainWindow::field3, Ui::MainWindow::field4
					);
	m_TransactionManager =  new TransactionManager(
								Ui::MainWindow::contacts, Ui::MainWindow::transactionLog, Ui::MainWindow::messageField,
								Ui::MainWindow::amountSelector, Ui::MainWindow::feeSelector, Ui::MainWindow::btndiag_send,
								m_ConfirmTransaction
						    );
	m_TransactionView = new TransactionView(Ui::MainWindow::transactionView, amountSelector->decimals(), feeSelector->decimals());

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
	delete m_TransactionList;
	delete m_AccPgs;
	delete m_FileBrowser;
	delete m_AddressBook;

	// Clear and free any shared memory that was used
	shared_mem::deleteSemaphore(shared_mem::READER_FILENAME);
	shared_mem::deleteSemaphore(shared_mem::WRITER_FILENAME);
	shared_mem::deleteMemory(shared_mem::FILENAME);
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
	int64_t difficulty = m_User->m_BlockchainCopy->GetDifficulty();
	Block newBlock;

	if (m_User->m_BlockchainCopy->Size() == 0) {
		newBlock = Block(0, m_BlockContents, difficulty, true); // Create a new block
	}
	else {
		Block* latest = m_User->m_BlockchainCopy->GetLatest(); // Get the latest block
		newBlock = Block(latest->m_Index + 1, latest->m_Hash, m_BlockContents, difficulty); // Create a new block
	}

	bool success = false, valid = false;
	uint8_t code;

	auto start = high_resolution_clock::now(); // Begin timing the function
	std::tie(success, code) = m_User->m_BlockchainCopy->Mine(newBlock); // Mine the block
	auto stop = high_resolution_clock::now(); // End timing

	std::cout << "Success: " << success << std::endl;
	std::cout << "Code: " << (uint)code << std::endl;

	m_LastMiningDur = std::chrono::duration_cast<seconds>(stop - start); // Find the duration

	// Verify and append the block
	if (success) {
		newBlock.m_MineTime = utility::getUTCTime(); // Timestamp the block
	}

	Blockchain* tempChain = new Blockchain(*m_User->m_BlockchainCopy);
	tempChain->Add(&newBlock);
	valid = validation::validate(*tempChain);

	if (valid) {
		std::cout << "Valid" << std::endl;
		m_User->m_BlockchainCopy->Add(&newBlock);

		std::this_thread::sleep_for(std::chrono::seconds(1));

		Transmitter* transmitter = new Transmitter();
		auto data = transmitter->Format(&newBlock);
		transmitter->Transmit(data, std::stoi(data[0]));

		emit MiningSuccess();
	}
	else {
		std::cout << "Hash: " << newBlock.m_Hash << std::endl;

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

void MainWindow::ManageSharedMem(std::atomic<bool>& running) {
	std::cout << "Running" << std::endl;

	while (running) {
		string data = shared_mem::readMemory(true);
		QJsonObject object = json::parse(data);

		go::PacketTypes packetType = static_cast<go::PacketTypes>(json::getPacketType(object));

		switch (packetType) {
			case go::PacketTypes::TRANSACTION:
				std::cout << "Here" << std::endl;
				m_TransactionList->ConfirmToMempool(json::toTransaction(object));
				break;

			case go::PacketTypes::BLOCK: {
				// If a new block is received, stop trying to solve the current block.
				if (!object.empty() && !data.empty()) {
					m_User->m_BlockchainCopy->StopMining(std::move(m_ExitSignal));
					std::cout << "Stopping" << std::endl;
				}

				Block* block = json::toBlock(object);

				for (auto transaction: block->m_Transactions) {
					if (m_User->GetAddress() == transaction->m_SenderAddr) {
						Receipt* receipt = transaction->GetReceipt();

						// Transmit the receipt to the recipient
						Transmitter* transmitter = new Transmitter();
						auto data = transmitter->Format(transaction);
						transmitter->Transmit(data, std::stoi(data[0]));
					}
				}

				break;
			}

			default:
				break;
		}

		std::this_thread::sleep_for(std::chrono::milliseconds(50));
	}
}
