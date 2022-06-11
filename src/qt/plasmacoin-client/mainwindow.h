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
#include <atomic>
#include <future>
#include <queue>

#include <QMainWindow>
#include <QStringList>
#include <QThread>
#include <QListWidgetItem>
#include <QFileDialog>
#include <QDateEdit>
#include <QMessageBox>
#include <QDialogButtonBox>
#include <QFuture>
#include <QWindow>
#include <QtConcurrent/QtConcurrent>

#include "ui.h"

#include "transaction-list.h"
#include "mining-status.h"
#include "account-pages.h"
#include "address-book.h"
#include "transaction-manager.h"
#include "transaction-view.h"
#include "mining-dialog.h"
#include "block-view.h"
#include "blockchain-viewer.h"
//#include "settings-manager.h"

#include "block.hpp"
#include "blockchain.hpp"
#include "node.hpp"
#include "rsa-fs.hpp"
#include "shared-mem.hpp"
#include "validation.hpp"
#include "dssize.hpp"
#include "transmitter.hpp"
#include "parse-json.hpp"
#include "utility.hpp"

namespace go {
	#include "pcnetworkd.h"
}

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
	void ShowContact(Contact* contact);

	void ManageSharedMem();
	void ManageSyncedData();

	void UpdateButtons();

	QWidget* parent;
	Status* m_Status;
	Auth* m_Authenticator;
	TransactionList* m_TransactionList;
	AccountPages* m_AccPgs;
	AddressBook* m_AddressBook;
	TransactionManager* m_TransactionManager;
	TransactionView* m_TransactionView;
	MiningDialog* m_MiningDialog;
	BlockView* m_BlockView;
	BlockchainViewer* m_BlockchainViewer;
	//SettingsManager* m_SettingsManager;

	QLabel* m_NameDisplay = new QLabel();
	QLabel* m_UsernameDisplay = new QLabel();
	QLabel* m_AddressDisplay = new QLabel();
	QLabel* m_BirthdayDisplay = new QLabel();

	QMessageBox *m_FormErrorAlert, *m_ConfirmTransaction;

	std::vector<Transaction*> m_BlockContents;
	std::chrono::seconds m_LastMiningDur;

	std::promise<void> m_ExitSignal;
	std::future<void> m_ExitFuture = m_ExitSignal.get_future();

private:
	QTabWidget* m_TabBar = Ui::MainWindow::tabWidget;

	Transaction* m_CurrTrans = nullptr;
	QFileDialog* m_FileBrowser = new QFileDialog();

	bool m_IsSyncing = false;
	std::queue<Block*> m_SyncedData;

public:
	Node* m_User = new Node("Ryan", "ryan", "1234", "192.168.1.44"); // Temporary data

signals:
	void BlockCompleted();
};

#endif // MAINWINDOW_H
