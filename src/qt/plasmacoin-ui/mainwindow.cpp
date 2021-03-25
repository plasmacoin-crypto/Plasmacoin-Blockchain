// The source file for mainwindow.h

#include <thread>

#include "mainwindow.h"

using std::thread;

MainWindow::MainWindow(QWidget *parent):
	QMainWindow(parent)
{
	setupUi(this);

	class thread windowManager([this]() { this->UpdateWindow(); });
	windowManager.join();
}

MainWindow::~MainWindow() {}

void MainWindow::UpdateWindow() {
	// Tab indicies should line up with stack widget indicies
	int index = tabWidget->currentIndex();

	connect(Ui::MainWindow::tabWidget, &QTabWidget::tabBarClicked, this, &MainWindow::DisplayPage);
}

void MainWindow::DisplayPage(int index) {
	stackedWidget->setCurrentIndex(index);
}

