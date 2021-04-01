// The source file for mainwindow.h

#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent):
	QMainWindow(parent)
{
	setupUi(this);
	DisplayPage(0); // Reset the QStackedWidget to page 1 (index 0)

	// Allow tab switching
	connect(Ui::MainWindow::tabWidget, &QTabWidget::tabBarClicked, this, &MainWindow::DisplayPage);
}

MainWindow::~MainWindow() {}

void MainWindow::DisplayPage(int index) {
	stackedWidget->setCurrentIndex(index);
}

