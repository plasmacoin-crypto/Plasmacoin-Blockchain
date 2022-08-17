//
// FILENAME: main.cpp | Plasmacoin Cryptocurrency
// DESCRIPTION: Launch the client application
// CREATED: 2021-03-21 @ 3:47 PM
// COPYRIGHT: Copyright (c) 2021 by Ryan Smith <rysmith2113@gmail.com>
//

#include "version-info.h"
#include "declare-beta-release.h"

#include <functional>
#include <atomic>
#include <chrono>

#include <QApplication>
#include <QSplashScreen>
#include <QPixmap>
#include <QIcon>
#include <QColor>
#include <QFuture>

#include "mainwindow.h"
#include "ui.h"
#include "connections.hpp"
#include "pc-splash-screen.h"
#include "net-constants.hpp"

// Run the application
int main(int argc, char* argv[]) {
	QApplication app(argc, argv);

	QCoreApplication::setOrganizationName("Plasmacoin Cryptocurrency");
    QCoreApplication::setOrganizationDomain("");
    QCoreApplication::setApplicationName("Plasmacoin Client");
	QCoreApplication::setApplicationVersion(QString::fromStdString(PLASMACOIN_FULL_VERSION));

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

	window.m_SettingsManager->LoadSettings(); // Load the user's settings

	if (online) {
		window.RegisterNode();
		std::atomic<bool> runningThread = true;

		QFuture<void> manageSharedMem = QtConcurrent::run([&window, &runningThread] {
			shared_mem::writeMemory("");

			while (runningThread) {
				window.ManageSharedMem();
			}
		});

		QFuture<void> manageUPnP = QtConcurrent::run([&window, &runningThread]() {
			// Wait for the settings data to be populated so it can be used to get the
			// UPnP device.
			std::unique_lock<std::mutex> lock(window.m_SettingsManager->m_SettingsMutex);
			window.m_SettingsManager->m_CondVar.wait(lock);

			settings::upnpServiceID = window.upnpDevSelector->itemText(settings::serviceIDIndex).toStdString();

			//upnp::openPort(settings::upnpServiceID.c_str(), netconsts::TCP, netconsts::TEST_PORT, netconsts::LOCAL_IP);
			auto threadStart = std::chrono::system_clock::now();

			do {
				if (auto now = std::chrono::system_clock::now(); threadStart + std::chrono::seconds(900) <= now) {
					//std::thread(upnp::openPort, settings::upnpServiceID.c_str(), netconsts::TCP, netconsts::TEST_PORT, netconsts::LOCAL_IP).detach();
					threadStart = now;
				}
			} while (runningThread);
		});

		std::this_thread::sleep_for(std::chrono::milliseconds(500));

		app.connect(&app, &QApplication::aboutToQuit, &window, [&online, &runningThread, &window]() mutable {
			runningThread = false;

			if (online) {
				window.RemoveNode();
			}
		});
	}

	if (online) {
		splashScreen->showMessage("Checking for new blocks", Qt::AlignBottom, QColorConstants::White);
		window.SyncBlockchain();
	}

	std::this_thread::sleep_for(std::chrono::milliseconds(500));

	splashScreen->showMessage("Launching", Qt::AlignBottom, QColorConstants::White);
	splashScreen->finish(&window);
	window.show();

	delete splashScreen;
	return app.exec();
}
