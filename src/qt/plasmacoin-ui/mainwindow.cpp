// The source file for mainwindow.h

#include "mainwindow.h"
#include <iostream>
#include <cassert>

using std::chrono::high_resolution_clock;
using std::chrono::seconds;

MainWindow::MainWindow(QWidget* parent):
	QMainWindow(parent),
	parent(parent),
	m_AccPgs(new AccountPages(accountView)),
	m_Authenticator(new Auth()),
	m_TList(new TransactionList(transactionList)),

	// Use these definitions as a workaround to pass `this` into std::async
	mine(std::async(std::launch::deferred, &MainWindow::StartMining, this)),
	load(std::async(std::launch::deferred, &MainWindow::LoadMiningVisuals, this, m_CurrTrans))
{
	setupUi(this);
	DisplayPage(0); // Reset the QStackedWidget to page 1 (index 0)

	m_TList->Populate(); // Load items into the transaction list

	load.wait(); // Load the mining visuals
	this->m_Status = load.get(); // Capture the return value

	// Allow tab switching
	connect(Ui::MainWindow::tabWidget, &QTabWidget::tabBarClicked, this, &MainWindow::DisplayPage);
}

MainWindow::~MainWindow() {
	delete m_AccPgs;
	delete m_Authenticator;
	delete m_TList;
}

// Create QTextBrowsers to display on the mining tab
Status MainWindow::LoadMiningVisuals(Transaction* transaction) {
	// The three widgets to display on the screen
	QTextBrowser  *browser1 = new QTextBrowser(Ui::MainWindow::mineCoins),
				  *browser2 = new QTextBrowser(Ui::MainWindow::mineCoins),
				  *browser3 = new QTextBrowser(Ui::MainWindow::mineCoins),
				  *browser4 = new QTextBrowser(Ui::MainWindow::mineCoins);

	Status status(browser1, browser2, browser3, browser4);

	return status;
}

// Call block mining code and make visual changes to the GUI once it's done
void MainWindow::StartMining() {
	Block* latest = m_User->m_BlockchainCopy->GetLatest(); // Get the latest block

	//std::cout << m_BlockContents[0]->data(Qt::UserRole).toInt() << std::endl;

	Block newBlock(latest->m_Index + 1, latest->m_PrevHash, {nullptr}); // Create a new block

	// Some test nodes
	Node* node1 = new Node("Ryan", "ryan", "1234", "192.168.1.6", false);
	Node* node2 = new Node("John", "john", "4567", "192.168.1.7", false);

	auto trans = node1->MakeTransaction(*node2, 1.0, "Here's some money");
	m_CurrTrans = &trans;

	m_User->m_BlockchainCopy->AddToLedger(m_CurrTrans); // Add a transaction (temporary)

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
