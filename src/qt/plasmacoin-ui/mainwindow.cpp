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

	// Allow tab switching
	connect(Ui::MainWindow::tabWidget, &QTabWidget::tabBarClicked, this, &MainWindow::DisplayPage);
}

MainWindow::~MainWindow() {
	//delete m_TList;
}

void MainWindow::DisplayPage(int index) {
	stackedWidget->setCurrentIndex(index);
}

