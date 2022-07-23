//
// FILENAME: main.cpp | Plasmacoin Cryptocurrency
// DESCRIPTION: Launch the client application
// CREATED: 2021-03-21 @ 3:47 PM
// COPYRIGHT: Copyright (c) 2021 by Ryan Smith <rysmith2113@gmail.com>
//

#include <functional>
#include <atomic>

#include <QApplication>
#include <QSplashScreen>
#include <QPixmap>
#include <QIcon>
#include <QColor>

#include "mainwindow.h"
#include "ui.h"
#include "connections.hpp"

// Run the application
int main(int argc, char* argv[]) {
	QApplication app(argc, argv);

	QPixmap pixmap("../assets/plasmacoin-banner.png");
    QSplashScreen splashScreen(pixmap);

	splashScreen.show();
	splashScreen.showMessage("Preparing application", Qt::AlignBottom, QColorConstants::White);

	MainWindow window;

	window.plusSign->setIcon(QIcon("../assets/plus.png"));
	window.minusSign->setIcon(QIcon("../assets/minus.png"));

	window.btn_reset->setIcon(QIcon("../assets/reset.png"));

	window.addressCopy->setIcon(QIcon("../assets/clipboard.png"));
	window.pubKeyCopy->setIcon(QIcon("../assets/clipboard.png"));
	window.privKeyCopy->setIcon(QIcon("../assets/clipboard.png"));

	window.pubKeyShow->setIcon(QIcon("../assets/view.png"));
	window.privKeyShow->setIcon(QIcon("../assets/view.png"));

	window.bannerText1->setText("<html><head/><body><p align=\"center\"><span style=\"font-size:24pt; color:#000000;\">Welcome Back!</span></p><p align=\"center\"><span style=\"font-size:24pt; color:#000000;\">Please sign in to continue.</span><span style=\"color:#000000;\"><br/></span></p><p align=\"center\"><br/></p><p align=\"center\"><br/></p><p align=\"center\"><br/></p><p align=\"center\"><br/></p><p align=\"center\"><br/></p><p align=\"center\"><br/></p><p align=\"center\"><br/></p><p align=\"center\"><br/><br/></p><p align=\"center\"><img src=\"../assets/plasmacoin-banner.png\" width=\"550\" height=\"150\"/></p></body></html>");
	window.bannerText2->setText("<html><head/><body><p align=\"center\"><span style=\" font-size:14pt; color:#000000;\">What is my account for?</span></p><p align=\"center\"><span style=\" font-size:14pt; color:#000000;\">Your Plasmacoin account registers you for the desktop app.<br/>This registers your computer as a Plasmacoin node and also<br/>gives you access to the offical Plasmacoin software wallet.</span></p><p align=\"center\"><span style=\" color:#000000;\"><br/></span></p><p align=\"center\"><span style=\" font-size:14pt; color:#000000;\">Credentials</span></p><p align=\"center\"><span style=\" font-size:14pt; color:#000000;\">Once you're signed in, you'll have access to your public and<br/>private keys, as well as your Plasmacoin address, which is what<br/>you'll use to send and recieve transactions.</span></p><p align=\"center\"><span style=\" color:#000000;\"><br/></span></p><p align=\"center\"><span style=\" font-size:14pt; color:#000000;\">Address Book</span></p><p align=\"center\"><span style=\" font-size:14pt; color:#000000;\">With your account, you can access the built-in address book,<br/>which allows you to save the addresses of other Plasmacoin<br/>users.</span></p><p align=\"center\"><br/></p><p align=\"center\"><img src=\"../assets/plasmacoin-banner.png\" width=\"550\" height=\"150\"/></p></body></html>");

	window.contactImage->setPixmap(QPixmap("../assets/contact-default.png"));
	window.btn_addContact->setIcon(QIcon("../assets/plus.png"));

	window.btn_first->setIcon(QIcon("../assets/double-left-arrow.png"));
	window.btn_previous->setIcon(QIcon("../assets/arrow-left.png"));
	window.btn_next->setIcon(QIcon("../assets/arrow-right.png"));
	window.btn_last->setIcon(QIcon("../assets/double-right-arrow.png"));
	window.btn_sync->setIcon(QIcon("../assets/sync.png"));

	// Connect everything
	splashScreen.showMessage("Making connections", Qt::AlignBottom, QColorConstants::White);
	connections::minePage(window);
	connections::accountPages(window);
	connections::addressBook(window);
	connections::transactionPage(window);
	connections::blockchainPage(window);
	connections::addToBlock(window);
	connections::removeFromBlock(window);
	connections::settingsPage(window);
	connections::updateWalletAmounts(window);
	std::this_thread::sleep_for(std::chrono::milliseconds(200));

	std::atomic<bool> runningThread = true;

	QFuture<void> manageSharedMem = QtConcurrent::run([&window](std::atomic<bool>& running) {
		shared_mem::writeMemory("");

		while (running) {
			window.ManageSharedMem();
		}
	}, std::ref(runningThread));
	std::this_thread::sleep_for(std::chrono::milliseconds(500));

	splashScreen.showMessage("Checking for new blocks", Qt::AlignBottom, QColorConstants::White);
	//window.SyncBlockchain();
	//window.ManageSyncedData(splashScreen);

	splashScreen.showMessage("Launching", Qt::AlignBottom, QColorConstants::White);
	splashScreen.finish(&window);
	window.show();

	app.connect(&app, &QApplication::aboutToQuit, &window, [&runningThread, &window]() mutable {
		runningThread = false;
		window.RemoveNode();
	});

	return app.exec();
}
