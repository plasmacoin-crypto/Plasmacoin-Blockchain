// mainwindow.h
// Template generated by QT Creator, then modified

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <thread>
#include <functional>
#include <future>

#include <QtWidgets/QMainWindow>
#include <QStringList>
#include <QThread>

#include "ui_mainwindow.h"

#include "transaction-list.h"
#include "mining-status.h"

#include "block.hpp"
#include "blockchain.hpp"
#include "node.hpp"

class MainWindow : public QMainWindow, public Ui::MainWindow {
	Q_OBJECT

public:
	MainWindow(QWidget* parent = nullptr);
	~MainWindow();

	void LoadMiningVisuals(Transaction* transaction); // Load certain content during mining operations

	QWidget* parent;

private:
	void StartMining(); // Initiate the mining process

	QTabWidget* m_TabBar = Ui::MainWindow::tabWidget;
	TransactionList* m_TList;

	Transaction* m_CurrTrans = nullptr;

	Node* m_User = new Node("Ryan", "ryan", "1234", "192.168.1.6", false); // Temporary data

private slots:
	void DisplayPage(int index); // Actually set the index of the stack widget

private:
	std::future<void> mine, load; // Asynchronous functions called during mining
};

#endif // MAINWINDOW_H
