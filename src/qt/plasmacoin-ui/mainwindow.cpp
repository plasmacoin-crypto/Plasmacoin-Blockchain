//
// FILENAME: mainwindow.cpp | Plasmacoin Cryptocurrency
// DESCRIPTION: The source file for mainwindow.h
// CREATED: 2021-03-21 @ 3:47 PM
// COPYRIGHT: Copyright (c) 2021 by Ryan Smith <rysmith2113@gmail.com>
//

#include "mainwindow.h"

using std::chrono::high_resolution_clock;
using std::chrono::seconds;

MainWindow::MainWindow(QWidget* parent):
	QMainWindow(parent),
	parent(parent),
	m_Authenticator(new Auth()),
	m_SettingsManager(new SettingsManager()),
	m_TList(new TransactionList(Ui::MainWindow::transactionList)),

	// Use these definitions as a workaround to pass `this` into std::async
	mine(std::async(std::launch::deferred, &MainWindow::StartMining, this)),
	load(std::async(std::launch::deferred, &MainWindow::LoadMiningVisuals, this, m_CurrTrans))
{
	setupUi(this);
	DisplayPage(0); // Reset the QStackedWidget to page 1 (index 0)

	// Create some temporary nodes to make transactions between
	Node* node1 = new Node("Ryan", "ryan", "1234", "192.168.1.6");
	Node* node2 = new Node("John", "john", "4567", "192.168.1.7", "/home/rmsmith/.ssh/node2keys/");
	Node* node3 = new Node("Bill", "bill", "8901", "192.168.1.8", "/home/rmsmith/.ssh/node3keys/");

	Transaction* transaction1 = node1->MakeTransaction(*node2, 1.0, "Here's some money");
	Transaction* transaction2 = node2->MakeTransaction(*node3, 5.7, "Here's some money");
	Transaction* transaction3 = node3->MakeTransaction(*node1, 2.1, "Here's some money");

	std::cout << transaction1->m_Condensed << std::endl;

	m_TList->Add(transaction1); // Load items into the transaction list
	m_TList->Add(transaction2); // Load items into the transaction list
	m_TList->Add(transaction3); // Load items into the transaction list

	load.wait(); // Load the mining visuals
	this->m_Status = load.get(); // Capture the return value

	// Create warning labels for all 5 input fields
	QLabel *label1 = new QLabel("", Ui::MainWindow::signIn),
		   *label2 = new QLabel("", Ui::MainWindow::signIn),
		   *label3 = new QLabel("", Ui::MainWindow::signUp),
	 	   *label4 = new QLabel("", Ui::MainWindow::signUp),
	 	   *label5 = new QLabel("", Ui::MainWindow::signUp);

	m_AccPgs = new AccountPages(Ui::MainWindow::accountView, label1, label2, label3, label4, label5);

	// Allow tab switching
	connect(Ui::MainWindow::tabWidget, &QTabWidget::tabBarClicked, this, &MainWindow::DisplayPage);

	connect(Ui::MainWindow::btn_choosePath, &QPushButton::released, this, [this]() {
		qDebug() << this->m_FileBrowser->getSaveFileName(
											Ui::MainWindow::settings, QFileDialog::tr("Choose an RSA output location"),
											QString::fromStdString(rsafs::HOME_DIR), QFileDialog::tr("Text Files (*.txt);;All Files (*.*, *)"),
											nullptr, QFileDialog::DontUseNativeDialog
										);
	});
}

MainWindow::~MainWindow() {
	delete m_AccPgs;
	delete m_Authenticator;
	delete m_TList;
}

// Create QTextBrowsers to display on the mining tab
Status MainWindow::LoadMiningVisuals(Transaction* transaction) {
	// The three widgets to display on the screen
	QTextBrowser *browser1 = new QTextBrowser(Ui::MainWindow::mineCoins),
				 *browser2 = new QTextBrowser(Ui::MainWindow::mineCoins),
				 *browser3 = new QTextBrowser(Ui::MainWindow::mineCoins),
				 *browser4 = new QTextBrowser(Ui::MainWindow::mineCoins);

 	Status status(browser1, browser2, browser3, browser4);
 	return status;
}

// Call block mining code and make visual changes to the GUI once it's done
void MainWindow::StartMining() {
	Block* latest = m_User->m_BlockchainCopy->GetLatest(); // Get the latest block

	// TODO: Make sure transactions are somehow readable from the QListWidget
	//std::cout << m_BlockContents[0]->data(Qt::UserRole).toInt() << std::endl;

	// std::vector<QListWidgetItem*> transactions;

	// for (int i = 0; i < Ui::MainWindow::blockTransactionList->count(); i++) {
	// 	transactions.push_back(Ui::MainWindow::blockTransactionList->row(i));
	// }

	Block newBlock(latest->m_Index + 1, latest->m_PrevHash, m_TList->m_List); // Create a new block

	auto start = high_resolution_clock::now(); // Begin timing the function

	bool result = m_User->m_BlockchainCopy->Mine(newBlock); // Mine the block

	auto stop = high_resolution_clock::now(); // End timing
	auto duration = std::chrono::duration_cast<seconds>(stop - start); // Find the duration

	UpdateStatus(newBlock, duration);
}

void MainWindow::UpdateStatus(Block& block, seconds time) {
	m_Status.SetHash(block.m_Hash);
	m_Status.SetNonce(block.m_Nonce);
	m_Status.SetTime(time);

	m_Status.LoadVisuals();
}

// Definitions for slots

// Display a certain page of the app
void MainWindow::DisplayPage(int index) {
	stackedWidget->setCurrentIndex(index);
	tabWidget->setCurrentIndex(index);
}
