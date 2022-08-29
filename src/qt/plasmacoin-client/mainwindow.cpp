//
// FILENAME: mainwindow.cpp | Plasmacoin Cryptocurrency
// DESCRIPTION: The source file for mainwindow.h
// CREATED: 2021-03-21 @ 3:47 PM
// COPYRIGHT: Copyright (c) 2021 by Ryan Smith <rysmith2113@gmail.com>
//

#include "mainwindow.h"

MainWindow::MainWindow(bool online, QWidget* parent):
	QMainWindow(parent),
	parent(parent),
	m_Authenticator(new Auth()),
	m_Wallet(new Wallet()),
	m_Settings(new QSettings()),
	m_IsOnline(online)
{
	shared_mem::deleteMemory(shared_mem::FILENAME);
	shared_mem::deleteMemory(shared_mem::READER_FILENAME);
	shared_mem::deleteMemory(shared_mem::WRITER_FILENAME);

	Ui_MainWindow::setupUi(this);
	LoadGeometry();
	
	m_FormErrorAlert = new QMessageBox(); // Create a message box to display authentication errors
	m_TransactionAlert = new QMessageBox(); // Create a message box to sign and send a transaction

	m_TransactionList = new TransactionList(this);
	m_Status = CreateMiningVisuals();
	m_AccPgs = CreatePages();
	m_AddressBook = new AddressBook(this, m_NameDisplay, m_UsernameDisplay, m_AddressDisplay, m_BirthdayDisplay);
	m_TransactionManager =  new TransactionManager(this, m_TransactionAlert);
	m_TransactionView = new TransactionView(Ui::MainWindow::transactionView, amountSelector->decimals(), feeSelector->decimals());
	m_MiningDialog = new MiningDialog(this);
	m_BlockView = new BlockView(Ui::MainWindow::blockView);
	m_BlockchainViewer = new BlockchainViewer(this, m_User->m_BlockchainCopy);
	m_WalletPage =  new WalletPage(this, m_Wallet);
	m_SettingsManager = new SettingsManager(this, m_Settings);

	Authentication();
	UpdateAmounts();

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

	Ui::MainWindow::rsaKeyPath->setText(QString::fromStdString(rsafs::RSA_KEY_PATH));
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
	Contact* contact2 = new Contact("Laptop", "laptop", "6A956A233B5DC113F2BE28ED546E1EF984AB4A8C", QDate(1970, 1, 1));
	//Contact* contact3 = new Contact("Alexander", "alex", "pca31415", QDate(2000, 1, 1));

	m_AddressBook->Add(contact1);
	m_AddressBook->Add(contact2);
	//m_AddressBook->Add(contact3);

	m_AddressBook->Sort();

	m_TransactionManager->UpdateContactsList(m_AddressBook);
}

MainWindow::~MainWindow() {
	delete m_Status;
	delete m_Authenticator;
	delete m_TransactionList;
	delete m_AccPgs;
	delete m_TransactionManager;
	delete m_TransactionView;
	delete m_MiningDialog;
	delete m_BlockView;
	delete m_BlockchainViewer;
	delete m_WalletPage;
	delete m_FileBrowser;
	delete m_AddressBook;
	delete m_Settings;
	//delete m_SysTrayIcon;

	std::queue<Block*>().swap(m_SyncedData);

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
	double difficulty = m_User->m_BlockchainCopy->GetDifficulty();
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

	UserQuery* query = new UserQuery{go::getLocalIP(), "addrlookup"};
	data = transmitter->Format(query);
	transmitter->Transmit(data, std::stoi(data[0]));
	delete query;

	// Parse the IPs
	std::string result = shared_mem::readMemory(true); // Read the shared memory
	std::cout << "Node Result: " << result << std::endl;
	std::vector<string> hosts = json::parseArray(json::parse(result), "nodes");

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

void MainWindow::FindAddrLookupNodes() {}

void MainWindow::RegisterNode() {
	// Register that the node is online
	Transmitter* transmitter = new Transmitter();
	auto data = transmitter->Format(m_User, m_User->GetIP(), netconsts::TEST_PORT);
	std::cout << data[0] << std::endl;
	transmitter->Transmit(data, std::stoi(data[0]));
	std::vector<string> hosts;

	NodeListPurpose purpose = NodeListPurpose::REGISTRATION;
	connect(this, &MainWindow::ReceivedNodeList, this, [=, &transmitter, &purpose] mutable {
		if (purpose != NodeListPurpose::REGISTRATION) {
			return;
		}

		std::cout << "Here" << std::endl;
		string packet = this->m_ShMemLog.back();

		// Parse the JSON string
		QJsonObject object = json::parse(packet);
		hosts = json::parseArray(object, "nodes");
		m_User->AddKnownHosts(hosts);

		shared_mem::writeMemory("");
		std::this_thread::sleep_for(std::chrono::milliseconds(300));

		// for (unsigned int i = 0; i < static_cast<unsigned int>(m_AddressBook->Size()); i++) {
		// 	Contact* contact = m_AddressBook->At(i);

		// 	auto data = transmitter->Format(contact->MakeNode(), m_User->GetIP(), netconsts::TEST_PORT, false);
		// 	transmitter->Transmit(data, std::stoi(data[0]));

		// 	std::this_thread::sleep_for(std::chrono::milliseconds(100));
		// }
	});

	connect(this, &MainWindow::ReceivedNodeData, this, [=](NodeData* node) mutable {
		if (node != nullptr) {
			this->m_User->AddKnownHost(node->m_IPAddress);
		}
	});
}

void MainWindow::RemoveNode() {
	Transmitter* transmitter = new Transmitter();
	RemovalRequest* remRequest = new RemovalRequest {netconsts::PUBLIC_IP};
	auto data = transmitter->Format(remRequest);
	transmitter->Transmit(data, std::stoi(data[0]));

	delete remRequest;
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
	m_ShMemLog.push_back(data);

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

		case go::PacketTypes::TRANSACTION: {
			std::cout << "Transaction" << std::endl;
			Transaction* transaction = json::toTransaction(object);
			qDebug() << object;

			//
			// Calculate the sender's balance using the blockchain. If a user's address
			// received a transaction, add money to the balance. If their address
			// sent a transaction, remove money from their balance. Users sending transactions
			// also spend fees, so subtract the fees too.
			//
			// Assuming blockchain verification has worked up until this point, double-spending
			// can be detected just by subtracting the incoming transaction total from the calculated
			// balance. Balances less than zero signify a double-spend or an attempt to spend more than
			// the user has in their wallet.
			//

			// double balance = 0;

			// for (auto block: m_User->m_BlockchainCopy->GetBlockchain()) {
			// 	for (auto trxn: block->m_Transactions) {
			// 		if (trxn->m_RecipientAddr == transaction->m_SenderAddr) {
			// 			balance += trxn->m_Amount;
			// 		}
			// 		else if (trxn->m_SenderAddr == transaction->m_SenderAddr) {
			// 			balance -= trxn->m_Amount + trxn->m_Fee;
			// 		}
			// 	}
			// }

			//if (balance >= transaction->m_Amount + transaction->m_Fee) {
				bool result = m_TransactionList->ConfirmToMempool(transaction);
				std::cout << "Confirmed: " << result << std::endl;
				shared_mem::writeMemory("");
			//}

			break;
		}

		case go::PacketTypes::BLOCK: {
			std::cout << "Received a block" << std::endl;
			shared_mem::writeMemory("");

			if (object.empty() || data.empty()) {
				break;
			}

			Block* block = json::toBlock(object);

			// If the block is received though a blockchain sync, just store it and continue listening
			if (m_IsSyncing) {
				std::cout << "Adding synced data" << std::endl;
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

		case go::PacketTypes::NODE:
			#if defined(__linux__) || defined(__APPLE__)
				emit ReceivedNodeData(json::toNodeData(object));
				shared_mem::writeMemory("");
			#endif

			break;

		case go::PacketTypes::NODE_LIST:
			#if defined(__linux__) || defined(__APPLE__)
				emit ReceivedNodeList();
				shared_mem::writeMemory("");
			#endif

			break;

		default:
			break;

		case go::PacketTypes::RECEIPT: {
			shared_mem::writeMemory("");
			std::cout << "Here" << std::endl;

			Receipt* receipt = json::toReceipt(object);
			m_WalletPage->AddReceipt(receipt);
			emit UpdateWalletAmounts();

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

				std::this_thread::sleep_for(std::chrono::milliseconds(500));

				// Sync the blockchain with the recipient node
				for (auto block: m_User->m_BlockchainCopy->GetBlockchain()) {
					packet = transmitter->Format(block);
					transmitter->Transmit(packet, std::stoi(packet[0]), {syncRequest->m_Host});

					std::this_thread::sleep_for(std::chrono::seconds(300));
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

		case go::PacketTypes::PENDING_TRXN: {
			std::cout << "Pending notification" << std::endl;
			shared_mem::writeMemory("");
			PendingTransaction* pendingTrxn = json::toPendingTrxn(object);

			m_WalletPage->AddPending(pendingTrxn);
			emit UpdateWalletAmounts();

			break;
		}
	}

	std::this_thread::sleep_for(std::chrono::milliseconds(50));
}

#if defined(__APPLE__) || defined(__linux__)
	void MainWindow::SyncBlockchain() {
		Transmitter* transmitter = new Transmitter();
		std::vector<string> data;

		// Request a list of viable nodes to sync from
		UserQuery* userQuery = new UserQuery {go::getLocalIP(), "light"};
		data = transmitter->Format(userQuery);
		transmitter->Transmit(data, std::stoi(data[0]));

		shared_mem::writeMemory("");
		std::this_thread::sleep_for(std::chrono::milliseconds(300));

		NodeListPurpose purpose = NodeListPurpose::SYNC;
		connect(this, &MainWindow::ReceivedNodeList, this, [=, &transmitter, &purpose] mutable {
			if (purpose != NodeListPurpose::SYNC) {
				return;
			}

			std::cout << "Here" << std::endl;
			string packet = this->m_ShMemLog.back();
			QJsonObject object = json::parse(packet);

			std::vector<string> hosts = json::parseArray(object, "nodes");

			shared_mem::writeMemory("");

			if (!hosts.empty()) {
				// Request to sync
				SyncRequest* syncRequest = new SyncRequest {static_cast<int>(go::PacketTypes::BLOCK), "192.168.1.44"};
				auto data = transmitter->Format(syncRequest);
				transmitter->Transmit(data, std::stoi(data[0]), hosts);

				std::this_thread::sleep_for(std::chrono::seconds(1));
			}

			transmitter = nullptr;
		});
	}
#else
	// Windows
#endif

void MainWindow::ManageSyncedData() {
	if (m_SyncedData.empty()) {
		return;
	}

	while (!m_SyncedData.empty()) {
		Block* nextBlock = m_SyncedData.front();
		bool valid = mining::validate(m_User->m_BlockchainCopy, nextBlock);

		if (valid) {
			m_User->m_BlockchainCopy->Add(nextBlock);
			m_SyncedData.pop();
		}
	}

	m_BlockchainViewer->Latest();
	UpdateButtons();
}

void MainWindow::ManageSyncedData(QSplashScreen& splashScreen) {
	std::cout << "With splashscreen" << std::endl;

	if (m_SyncedData.empty()) {
		splashScreen.showMessage("Already up to date", Qt::AlignBottom, QColorConstants::White);
		emit DisplayApp();
		return;
	}

	//
	// When calculating percentages to display during a blockchain sync, the
	// percentage will increase by a certain number each time a block is processed.
	// Larger amounts of synced data require a smaller increment on the display.
	// With a number of blocks evenly divisible by 100, eveything works out nicely.
	// For non-multiples, we take the ceiling of the quotient and then max the display
	// out at 100%. By taking the ceiling, we sill increment the correct number of times.
	//
	const int PCT_JUMP = std::ceil(100.0 / m_SyncedData.size());
	int percent = 0;

	splashScreen.showMessage(QString("Syncing blockchain (%1\% complete)").arg(QString::number(percent, 10)), Qt::AlignBottom, QColorConstants::White);
	std::this_thread::sleep_for(std::chrono::milliseconds(500));

	while (!m_SyncedData.empty()) {
		m_User->m_BlockchainCopy->Add(m_SyncedData.front());

		percent = (percent + PCT_JUMP <= 100)? percent + PCT_JUMP : 100; // 100% is the max
		splashScreen.showMessage(QString("Syncing blockchain (%1\% complete)").arg(QString::number(percent, 10)), Qt::AlignBottom, QColorConstants::White);

		m_SyncedData.pop();
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
	}

	splashScreen.showMessage("Done", Qt::AlignBottom, QColorConstants::White);

	m_BlockchainViewer->Latest();
	UpdateButtons();

	emit DisplayApp();
}

void MainWindow::UpdateButtons() {
	bool genesis, previous, next, latest;
	std::tie(genesis, previous, next, latest) = m_BlockchainViewer->GetBtnStates();

	btn_first->setEnabled(genesis);
	btn_previous->setEnabled(previous);
	btn_next->setEnabled(next);
	btn_last->setEnabled(latest);
}

void MainWindow::UpdateAmounts() {
	double balance = m_Wallet->GetBalance();
	double pending = m_Wallet->GetPendingBal();
	double available = m_Wallet->GetAvailableBal();
	double total = m_Wallet->GetFutureBal();

	std::cout << "Total: " << total << std::endl;

	Ui::MainWindow::balance->setText(QString::number(balance, 'f', 10));
	pendingBalance->setText(QString::number(pending, 'f', 10));
	availableBalance->setText(QString::number(available, 'f', 10));
	futureBalance->setText(QString::number(total, 'f', 10));

	m_Authenticator->AdjustBalance(m_Wallet->GetBalance());
}

void MainWindow::SaveGeometry() {
	m_Settings->beginGroup("mainwindow");
    m_Settings->setValue("geometry", saveGeometry());
    m_Settings->endGroup();
}

void MainWindow::LoadGeometry() {
	m_Settings->beginGroup("mainwindow");

    auto geometry = m_Settings->value("geometry", QByteArray()).toByteArray();
    if (!geometry.isEmpty()) {
        restoreGeometry(geometry);
	}

    m_Settings->endGroup();
}

void MainWindow::Authentication() {
	tabWidget->setCurrentIndex(5);

	#ifdef BETA_RELEASE
		m_AccPgs->DisplayPage(0); // Display beta key entry page

		if (!datfs::hasBetaKeyCache()) {
			return;
		}

	#endif

	m_AccPgs->DisplayPage(1); // Display the sign-in page

	if (!datfs::hasCredCache()) {
		return;
	}

	string email, password;
	std::tie(email, password) = datfs::loadLoginInfo();

	m_Authenticator->SignIn(QString::fromStdString(email), QString::fromStdString(password));
}

void MainWindow::closeEvent(QCloseEvent* event) {
	SaveGeometry();
	m_SettingsManager->SaveSettings();
}
