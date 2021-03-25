// The source file for mainwindow.h

#include <thread>

#include "mainwindow.h"

using std::thread;

MainWindow::MainWindow(QWidget *parent):
	QMainWindow(parent)
{
	setupUi(this);

	connect(Ui::MainWindow::tabWidget, &QTabWidget::tabBarClicked, this, &MainWindow::DisplayPage);
}

MainWindow::~MainWindow() {}

void MainWindow::DisplayPage(int index) {
	stackedWidget->setCurrentIndex(index);
}

