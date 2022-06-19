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
	m_TransactionList(new TransactionList(Ui::MainWindow::transactionList)),
	m_Wallet(new Wallet())
{
	shared_mem::deleteMemory(shared_mem::FILENAME);
	shared_mem::deleteMemory(shared_mem::READER_FILENAME);
	shared_mem::deleteMemory(shared_mem::WRITER_FILENAME);

	RegisterNode();

	Ui_MainWindow::setupUi(this);

	// QPushButton* button = new QPushButton("Button", this);
	// button->setGeometry(QRect(0, 0, 100, 30));
	// button->show();

	// QPropertyAnimation* animation = new QPropertyAnimation(button, "geometry");
	// animation->setDuration(10000);
	// animation->setStartValue(QRect(0, 0, 100, 30));
	// animation->setEndValue(QRect(250, 250, 100, 30));

	// animation->start();
	// connect(animation, &QPropertyAnimation::finished, button, &QPushButton::deleteLater);


	// std::future<void> manageSharedMem = std::async([this](std::atomic<bool>& running) {
	// 	this->ManageSharedMem(running);
	// }, std::ref(runningThread));

	tabWidget->setCurrentIndex(0);

	m_FormErrorAlert = new QMessageBox(); // Create a message box to display authentication errors
	m_TransactionAlert = new QMessageBox(); // Create a message box to sign and send a transaction

	m_Status = CreateMiningVisuals();
	m_AccPgs = CreatePages();
	m_AddressBook = new AddressBook(
						Ui::MainWindow::contactsList, m_NameDisplay, Ui::MainWindow::nameField,
						m_UsernameDisplay, Ui::MainWindow::usernameField, m_AddressDisplay,
						Ui::MainWindow::addressField, m_BirthdayDisplay, Ui::MainWindow::birthday,
						Ui::MainWindow::btndiag_confirm, Ui::MainWindow::field1, Ui::MainWindow::field2,
						Ui::MainWindow::field3, Ui::MainWindow::field4
					);
	m_TransactionManager =  new TransactionManager(
								Ui::MainWindow::contacts, Ui::MainWindow::transactionLog, Ui::MainWindow::messageField,
								Ui::MainWindow::amountSelector, Ui::MainWindow::feeSelector, Ui::MainWindow::btndiag_send,
								m_TransactionAlert
						    );
	m_TransactionView = new TransactionView(Ui::MainWindow::transactionView, amountSelector->decimals(), feeSelector->decimals());
	m_MiningDialog = new MiningDialog(this);
	m_BlockView = new BlockView(Ui::MainWindow::blockView);
	m_BlockchainViewer = new BlockchainViewer(m_User->m_BlockchainCopy, Ui::MainWindow::blockView, Ui::MainWindow::blockTrxnView);
	m_WalletPage = new WalletPage(Ui::MainWindow::receiptList, Ui::MainWindow::pendingList);

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
											Ui::MainWindow::SettingsTab, QFileDialog::tr("Choose an RSA output location"),
											QString::fromStdString(rsafs::HOME_DIR), QFileDialog::tr("Text Files (*.txt);;All Files (*.*, *)"),
											nullptr, QFileDialog::DontUseNativeDialog
										);
	});

	connect(this, &MainWindow::BlockCompleted, this, [=]() {
		Block* latest = this->m_User->m_BlockchainCopy->GetLatest();
		this->m_MiningDialog->Display(latest);
	});

	// Add a contact to the list
	Contact* contact1 = new Contact("Ryan", "rmsmith", "74E53206EC86B36DB2616EFD81C48419E3F85D4A", QDate(2005, 2, 16));
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
	QTextBrowser *browser1 = new QTextBrowser(Ui::MainWindow::MiningTab),
				 *browser2 = new QTextBrowser(Ui::MainWindow::MiningTab),
				 *browser3 = new QTextBrowser(Ui::MainWindow::MiningTab),
				 *browser4 = new QTextBrowser(Ui::MainWindow::MiningTab);

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
	Block newBlock = mining::makeBlock(m_User->m_BlockchainCopy, m_BlockContents, difficulty);

	bool success = false, valid = false;
	uint8_t code;

	std::tie(success, code) = mining::mine(m_User->m_BlockchainCopy, newBlock);

	if (!success) {
		return;
	}

	valid = mining::validate(m_User->m_BlockchainCopy, &newBlock);

	if (!valid) {
		return;
	}

	std::cout << "Valid" << std::endl;

	// Update and display the block
	newBlock.m_MinerAddr = m_User->GetAddress();
	m_User->m_BlockchainCopy->Add(&newBlock);
	m_BlockchainViewer->Latest();

	std::this_thread::sleep_for(std::chrono::seconds(1));

	mining::transmitBlock(&newBlock, m_User->GetKnownHosts());
	emit BlockCompleted();

	std::this_thread::sleep_for(std::chrono::seconds(2));
	shared_mem::writeMemory("");

	std::vector<string> data;
	Transmitter* transmitter = new Transmitter();

	//
	// Experimental code
	//
	// Get a list of Address Lookup nodes' IP addresses
	// NOTE: only works if Address Lookup nodes self-register or sync first
	//
	// UserQuery* query = new UserQuery{"192.168.1.44", "addrlookup"};
	// data = transmitter->Format(query);
	// transmitter->Transmit(data, std::stoi(data[0]));
	// delete query;
	//
	// Parse the IPs
	// std::string result = shared_mem::readMemory(true); // Read the shared memory
	// std::cout << "Node Result: " << result << std::endl;
	// std::vector<string> hosts = json::parseArray(json::parse(result), "nodes");
	//

	Node* node = nullptr;

	// Transmit transaction receipts
	for (auto trxn: newBlock.m_Transactions) {
		// Request the IP address associated with the transaction's recipient address
		node = new Node("", trxn->m_RecipientAddr);
		data = transmitter->Format(node, m_User->GetIP(), false);
		transmitter->Transmit(data, std::stoi(data[0]));

		// Parse the result
		std::string result = shared_mem::readMemory(true); // Read the shared memory
		std::cout << "Result: " << result << std::endl;
		std::string ip = json::parse(result)["ip"].toString().toStdString();

		shared_mem::writeMemory("");
		std::this_thread::sleep_for(std::chrono::milliseconds(500));

		// Send the transaction receipt to the IP address
		Receipt* receipt = trxn->GetReceipt();
		data = transmitter->Format(receipt);
		transmitter->Transmit(data, std::stoi(data[0]), {ip});

		std::this_thread::sleep_for(std::chrono::milliseconds(500));
	}

	delete transmitter;
	delete node;
}

void MainWindow::ResetBlock() {
	m_BlockContents.clear();
	blockContents->clear();
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
	m_BirthdayDisplay->setText(contact->GetBirthday().toString());

	// Set the writable fields
	nameField->setText(QString::fromStdString(contact->GetName()));
	usernameField->setText(QString::fromStdString(contact->GetUsername()));
	addressField->setText(QString::fromStdString(contact->GetAddress()));

	birthday->setDate(contact->GetBirthday()); // Set the birthday
}

void MainWindow::RegisterNode() {
	// Register that the node is online
	Transmitter* transmitter = new Transmitter();
	auto data = transmitter->Format(m_User, m_User->GetIP());
	std::cout << data[0] << std::endl;
	transmitter->Transmit(data, std::stoi(data[0]));

	string result = shared_mem::readMemory(true); // Read the shared memory
	std::cout << "Node Result: " << result << std::endl;

	// Parse the JSON string
	QJsonObject object = json::parse(result);
	std::vector<string> hosts = json::parseArray(object, "nodes");
	m_User->SetKnownHosts(hosts);

	for (auto host: hosts) {
		std::cout << "Host: " << host << std::endl;
	}

	shared_mem::writeMemory("");
	delete transmitter;
}

void MainWindow::ManageSharedMem() {
	string data = shared_mem::readMemory(true);
	QJsonObject object = json::parse(data);

	go::PacketTypes packetType = static_cast<go::PacketTypes>(json::getPacketType(object));

	if (data.empty()) {
		return;
	}

	std::cout << data << std::endl;

	switch (packetType) {
		case go::PacketTypes::ID_CODE: {
			IDCode* idCode = json::toIDCode(object);
			shared_mem::writeMemory("");
			go::IDCodes code = static_cast<go::IDCodes>(idCode->m_Code);

			if (code == go::IDCodes::START_SYNC) {
				std::cout << "Starting sync" << std::endl;
				m_IsSyncing = true;
			}
			else if (code == go::IDCodes::END_SYNC) {
				std::cout << "Ending sync" << std::endl;
				m_IsSyncing = false;
				ManageSyncedData();
			}

			break;
		}

		case go::PacketTypes::TRANSACTION:
			m_TransactionList->ConfirmToMempool(json::toTransaction(object));
			shared_mem::writeMemory("");
			break;

		case go::PacketTypes::BLOCK: {
			std::cout << "Received a block" << std::endl;
			shared_mem::writeMemory("");

			if (object.empty() || data.empty()) {
				break;
			}

			Block* block = json::toBlock(object);

			// If the block is received though a blockchain sync, just store it and continue listening
			if (m_IsSyncing) {
				m_SyncedData.push(block);
				break;
			}

			// If a new block is received, stop trying to solve the current block.
			if (block->m_MinerAddr != m_User->GetAddress()) {
				m_User->m_BlockchainCopy->StopMining(std::move(m_ExitSignal));
				std::cout << "Stopping" << std::endl;
			}

			m_User->m_BlockchainCopy->Add(block);
			m_BlockchainViewer->Latest();
			UpdateButtons();

			break;
		}

		case go::PacketTypes::RECEIPT: {
			shared_mem::writeMemory("");
			std::cout << "Here" << std::endl;

			Receipt* receipt = json::toReceipt(object);
			m_WalletPage->AddReceipt(receipt);
			break;
		}

		case go::PacketTypes::SYNC_REQUEST: {
			std::cout << "Received sync request" << std::endl;
			shared_mem::writeMemory("");

			if (object.empty() || data.empty()) {
				break;
			}

			SyncRequest* syncRequest = json::toSyncRequest(object);

			if (syncRequest->m_SyncType == static_cast<uint8_t>(go::PacketTypes::BLOCK)) {
				std::vector<string> packet;
				Transmitter* transmitter = new Transmitter();

				// Signal the start of the sync period
				IDCode syncSignal {static_cast<uint8_t>(go::IDCodes::START_SYNC)};
				packet = transmitter->Format(&syncSignal);
				transmitter->Transmit(packet, std::stoi(packet[0]), {syncRequest->m_Host});

				std::this_thread::sleep_for(std::chrono::milliseconds(300));

				// Sync the blockchain with the recipient node
				for (auto block: m_User->m_BlockchainCopy->GetBlockchain()) {
					packet = transmitter->Format(block);
					transmitter->Transmit(packet, std::stoi(packet[0]), {syncRequest->m_Host});

					std::this_thread::sleep_for(std::chrono::seconds(1));
				}

				std::this_thread::sleep_for(std::chrono::milliseconds(500));

				// Signal the end of the sync period
				syncSignal.m_Code = static_cast<uint8_t>(go::IDCodes::END_SYNC);
				packet = transmitter->Format(&syncSignal);
				transmitter->Transmit(packet, std::stoi(packet[0]), {syncRequest->m_Host});

				std::this_thread::sleep_for(std::chrono::milliseconds(100));

				delete transmitter;
			}

			break;
		}

		case go::PacketTypes::PENDING_TRXN:
			shared_mem::writeMemory("");

			m_WalletPage->AddPending(json::toPendingTrxn(object));
			break;

		// case go::PacketTypes::NODE:
		// 	std::cout << "Node" << std::endl;

		default:
			break;
	}

	std::this_thread::sleep_for(std::chrono::milliseconds(50));
}

void MainWindow::ManageSyncedData() {
	while (!m_SyncedData.empty()) {
		m_User->m_BlockchainCopy->Add(m_SyncedData.front());
		m_SyncedData.pop();
	}

	m_BlockchainViewer->Latest();
	UpdateButtons();
}

void MainWindow::UpdateButtons() {
	bool genesis, previous, next, latest;
	std::tie(genesis, previous, next, latest) = m_BlockchainViewer->GetBtnStates();

	btn_first->setEnabled(genesis);
	btn_previous->setEnabled(previous);
	btn_next->setEnabled(next);
	btn_last->setEnabled(latest);
}
