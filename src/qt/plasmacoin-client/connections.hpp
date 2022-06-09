//
// FILENAME: connections.hpp | Plasmacoin Cryptocurrency
// DESCRIPTION: Connect the Qt GUI to the blockchain
// CREATED: 2022-02-06 @ 10:57 PM
// COPYRIGHT: Copyright (c) 2022 by Ryan Smith <rysmith2113@gmail.com>
//

#ifndef CONNECTIONS_HPP
#define CONNECTIONS_HPP

#include <string>
#include <atomic>
#include <thread>
#include <vector>
#include <future>

using std::string;

#include <QApplication>
#include <QPushButton>
#include <QListWidget>
#include <QListWidgetItem>
#include <QSplashScreen>
#include <QDialogButtonBox>
#include <QSignalBlocker>
#include <QDialogButtonBox>
#include <QLineEdit>
#include <QAbstractButton>
#include <QMessageBox>

#include "mainwindow.h"
#include "ui.h"
#include "firebase-auth.h"
#include "transmitter.hpp"
#include "shared-mem.hpp"
#include "packet-types.h"
#include "parse-json.hpp"
#include "dssize.hpp"

namespace connections {
	void minePage(MainWindow& window);
	void accountPages(MainWindow& window);
	void addressBook(MainWindow& window);
	void transactionPage(MainWindow& window);
	void blockchainPage(MainWindow& window);
	void addToBlock(MainWindow& window);
	void removeFromBlock(MainWindow& window);

	void manageSharedMem(std::atomic<bool>& running, MainWindow& window);
	double calculateFee(MainWindow& window);
	void updateButtons(MainWindow& window);
}

#endif // CONNECTIONS_HPP
