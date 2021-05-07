// The source file for mainwindow.h

#include "mainwindow.h"
#include <iostream>

MainWindow::MainWindow(QWidget* parent):
	QMainWindow(parent),
	parent(parent),
	m_TList(new TransactionList(transactionList)),

	// Use these definitions as a workaround to pass `this` into std::async
	mine(std::async(std::launch::deferred, &MainWindow::StartMining, this)),
	load(std::async(std::launch::deferred, &MainWindow::LoadMiningVisuals, this, m_CurrTrans))
{
	setupUi(this);
	DisplayPage(0); // Reset the QStackedWidget to page 1 (index 0)

	m_TList->Populate(); // Load items into the transaction list

	load.wait(); // Load the mining visuals
	Status* status = load.get(); // Capture the return value

	// Allow tab switching
	connect(Ui::MainWindow::tabWidget, &QTabWidget::tabBarClicked, this, &MainWindow::DisplayPage);

	// Mine a block when the correct button is clicked
	connect(Ui::MainWindow::btn_mine, &QPushButton::released, this, [=]() { this->mine.wait(); });
}

MainWindow::~MainWindow() {
	delete m_TList;
}

Status* MainWindow::LoadMiningVisuals(Transaction* transaction) {
	// The three widgets to display on the screen
	QTextBrowser  *browser1 = new QTextBrowser(Ui::MainWindow::mineCoins),
				  *browser2 = new QTextBrowser(Ui::MainWindow::mineCoins),
				  *browser3 = new QTextBrowser(Ui::MainWindow::mineCoins);

	Status* status = new Status(browser1, browser2, browser3);
	status->LoadVisuals();

	return status
}

void MainWindow::StartMining() {
	Block newBlock(-1, nullptr, nullptr); // Instantiate the block with some throwaway values

	// Some test nodes
	Node* node1 = new Node("Ryan", "ryan", "1234", "192.168.1.6", false);
	Node* node2 = new Node("John", "john", "4567", "192.168.1.7", false);

	auto trans = node1->MakeTransaction(*node2, 1.0, "Here's some money");
	m_CurrTrans = &trans;

	m_User->m_BlockchainCopy->AddToLedger(m_CurrTrans); // Load a transaction onto the block

	bool result = m_User->m_BlockchainCopy->Mine(newBlock); // Mine the block
}

// Definitions for slots

// Display a certain page of the QStackedWidget
void MainWindow::DisplayPage(int index) {
	stackedWidget->setCurrentIndex(index);
}
