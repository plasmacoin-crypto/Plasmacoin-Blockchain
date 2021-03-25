#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent):
	QMainWindow(parent)
{
	setupUi(this);
}

MainWindow::~MainWindow() {}

void MainWindow::UpdateWindow() {
	// Tab indicies should line up with stack widget indicies
	int index = tabWidget->currentIndex();
	//QWidget* tab = m_TabBar->currentWidget();

	connect(m_TabBar, &QTabWidget::tabBarClicked, this, &MainWindow::DisplayPage);
}

void MainWindow::DisplayPage(int index) {
	stackedWidget->setCurrentIndex(index);
}

