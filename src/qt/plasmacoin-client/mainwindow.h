//
// FILENAME: mainwindow.h | Plasmacoin Cryptocurrency
// DESCRIPTION: The app's main window and base functionality
// CREATED: 2021-03-21 @ 3:47 PM
// COPYRIGHT: Copyright (c) 2021 by Ryan Smith <rysmith2113@gmail.com>
//

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <thread>
#include <functional>
#include <vector>
#include <iostream>
#include <chrono>

#include <QtWidgets/QMainWindow>
#include <QStringList>
#include <QThread>
#include <QtWidgets/QListWidgetItem>
#include <QFileDialog>

#include "ui_mainwindow.h"

#include "transaction-list.h"
#include "mining-status.h"
#include "account-pages.h"
//#include "settings-manager.h"

#include "block.hpp"
#include "blockchain.hpp"
#include "node.hpp"
#include "rsa-fs.hpp"

using std::chrono::high_resolution_clock;
using std::chrono::seconds;

class MainWindow : public QMainWindow, public Ui::MainWindow {
	Q_OBJECT

public:
	MainWindow(QWidget* parent = nullptr);
	~MainWindow();

	Status* CreateMiningVisuals(); // Load certain content during mining operations
	AccountPages* CreatePages();   // Create warning labels for authentication pages

	void StartMining(); // Initiate the mining process
	void ResetBlock();	// Reset the user's block

	void UpdateStatus(const Block& block, std::chrono::seconds time); // Update the mining status while a block is being mined

	QWidget* parent;
	Status* m_Status;
	Auth* m_Authenticator;
	TransactionList* m_TList;
	AccountPages* m_AccPgs;
	//SettingsManager* m_SettingsManager;

	std::vector<Transaction*> m_BlockContents;
	std::chrono::seconds m_LastMiningDur;
	Block m_LastBlock;

private:
	QTabWidget* m_TabBar = Ui::MainWindow::tabWidget;

	Transaction* m_CurrTrans = nullptr;
	QFileDialog* m_FileBrowser = new QFileDialog();

public:
	Node* m_User = new Node("Ryan", "ryan", "1234", "192.168.1.6"); // Temporary data

signals:
	void MiningSuccess();
	void MiningFailure();

private slots:
	void DisplayPage(int index) const; // Actually set the index of the stack widget
};

#endif // MAINWINDOW_H
