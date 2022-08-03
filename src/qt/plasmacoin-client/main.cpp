//
// FILENAME: main.cpp | Plasmacoin Cryptocurrency
// DESCRIPTION: Launch the client application
// CREATED: 2021-03-21 @ 3:47 PM
// COPYRIGHT: Copyright (c) 2021 by Ryan Smith <rysmith2113@gmail.com>
//

#include "declare-beta-release.h"

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
#include "pc-splash-screen.h"

// Run the application
int main(int argc, char* argv[]) {
	QApplication app(argc, argv);

	QCoreApplication::setOrganizationName("Plasmacoin Cryptocurrency");
    QCoreApplication::setOrganizationDomain("");
    QCoreApplication::setApplicationName("Plasmacoin Client");
	QCoreApplication::setApplicationVersion("0.1.0");

	QPixmap pixmap(":assets/plasmacoin-banner.png");
    QSplashScreen* splashScreen = new QSplashScreen(pixmap);

	splashScreen->show();
	splashScreen->showMessage("Preparing application", Qt::AlignBottom, QColorConstants::White);

	QCommandLineParser parser;
	parser.setApplicationDescription("The Plasmacoin client software");
    parser.addHelpOption();
    parser.addVersionOption();

	parser.addOptions({
		{{"n", "no-connect"}, "Launch in offline mode."}
		#ifdef BETA_RELEASE
			, {{"s", "skip-key"}, "Skip beta key entry (developer only)."}
		#endif
	});

	parser.process(app);
	bool online = !parser.isSet("no-connect");

	MainWindow window(online);

	// Connect everything
	splashScreen->showMessage("Making connections", Qt::AlignBottom, QColorConstants::White);
	connections::minePage(window);
	connections::accountPages(window);
	connections::addressBook(window);
	connections::transactionPage(window);
	connections::blockchainPage(window);
	connections::addToBlock(window);
	connections::removeFromBlock(window);
	connections::settingsPage(window);
	connections::aboutPage(window);
	connections::updateWalletAmounts(window);
	std::this_thread::sleep_for(std::chrono::milliseconds(200));

	window.m_SettingsManager->LoadSettings(); // Load the user's settings

	if (online) {
		std::atomic<bool> runningThread = true;

		QFuture<void> manageSharedMem = QtConcurrent::run([&window](std::atomic<bool>& running) {
			shared_mem::writeMemory("");

			while (running) {
				window.ManageSharedMem();
			}
		}, std::ref(runningThread));
		std::this_thread::sleep_for(std::chrono::milliseconds(500));

		app.connect(&app, &QApplication::aboutToQuit, &window, [&online, &runningThread, &window]() mutable {
			runningThread = false;

			if (online) {
				window.RemoveNode();
			}
		});
	}

	splashScreen->showMessage("Checking for new blocks", Qt::AlignBottom, QColorConstants::White);
	window.SyncBlockchain();
	std::this_thread::sleep_for(std::chrono::milliseconds(500));

	splashScreen->showMessage("Launching", Qt::AlignBottom, QColorConstants::White);
	splashScreen->finish(&window);
	window.show();

	delete splashScreen;
	return app.exec();
}
