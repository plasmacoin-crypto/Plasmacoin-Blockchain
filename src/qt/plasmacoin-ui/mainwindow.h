//
// FILENAME: mainwindow.h | Plasmacoin Cryptocurrency
// DESCRIPTION: The app's main windoow and base functionality
// CREATED: 2021-03-21 @ 3:47 PM
// COPYRIGHT: Copyright (c) 2021 by Ryan Smith <rysmith2113@gmail.com>
//

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <thread>
#include <functional>
#include <future>
#include <vector>
#include <iostream>

#include <QtWidgets/QMainWindow>
#include <QStringList>
#include <QThread>
#include <QtWidgets/QListWidgetItem>
#include <QFileDialog>

#include "ui_mainwindow.h"

#include "transaction-list.h"
#include "mining-status.h"
#include "account-pages.h"
#include "settings-manager.h"

#include "block.hpp"
#include "blockchain.hpp"
#include "node.hpp"
#include "rsa-fs.hpp"

class MainWindow : public QMainWindow, public Ui::MainWindow {
	Q_OBJECT

public:
	MainWindow(QWidget* parent = nullptr);
	~MainWindow();

	Status LoadMiningVisuals(Transaction* transaction); // Load certain content during mining operations

	QWidget* parent;
	Status m_Status;
	AccountPages* m_AccPgs;
	Auth* m_Authenticator;
	SettingsManager* m_SettingsManager;

	std::vector<QListWidgetItem*> m_BlockContents;

private:
	void StartMining(); // Initiate the mining process
	void UpdateStatus(Block& block, std::chrono::seconds time); // Update the mining status while a block is being mined

	QTabWidget* m_TabBar = Ui::MainWindow::tabWidget;
	TransactionList* m_TList;

	Transaction* m_CurrTrans = nullptr;
	QFileDialog* m_FileBrowser = new QFileDialog();

public:
	Node* m_User = new Node("Ryan", "ryan", "1234", "192.168.1.6"); // Temporary data

private slots:
	void DisplayPage(int index); // Actually set the index of the stack widget

public:
	// Asynchronous functions called during mining
	std::future<void> mine;
	std::future<Status> load;
};

#endif // MAINWINDOW_H
