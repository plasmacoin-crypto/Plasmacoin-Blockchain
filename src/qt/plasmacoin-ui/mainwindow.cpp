// The source file for mainwindow.h

#include "mainwindow.h"

MainWindow::MainWindow(QWidget* parent):
	QMainWindow(parent),
	parent(parent),
	m_TList(new TransactionList(transactionList))
{
	setupUi(this);
	DisplayPage(0); // Reset the QStackedWidget to page 1 (index 0)

	m_TList->Populate(); // Load items into the transaction list
	LoadMiningVisuals();

	// Allow tab switching
	connect(Ui::MainWindow::tabWidget, &QTabWidget::tabBarClicked, this, &MainWindow::DisplayPage);

	// Mine a block when the correct button is clicked
	connect(Ui::MainWindow::btn_mine, &QPushButton::released, this, &MainWindow::StartMining);
}

MainWindow::~MainWindow() {
	delete m_TList;
}

void MainWindow::LoadMiningVisuals() {
	// The three widgets to display on the screen
	QTextBrowser  *browser1 = new QTextBrowser(mineCoins),
				  *browser2 = new QTextBrowser(mineCoins),
				  *browser3 = new QTextBrowser(mineCoins);

	Status* status = new Status(browser1, browser2, browser3);

	status->LoadVisuals();
	status->SetHeading("Test Content");
}

// Definitions for slots

// Display a certain page of the QStackedWidget
void MainWindow::DisplayPage(int index) {
	stackedWidget->setCurrentIndex(index);
}

void MainWindow::StartMining() {

}

