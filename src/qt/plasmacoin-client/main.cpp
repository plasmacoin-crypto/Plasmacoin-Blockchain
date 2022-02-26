
#include <functional>
#include <atomic>

#include <QApplication>
#include <QSplashScreen>
#include <QPixmap>
#include <QIcon>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "connections.hpp"

// Run the application
int main(int argc, char* argv[]) {
	QApplication app(argc, argv);

	QPixmap pixmap("../assets/plasmacoin-banner.png");
    QSplashScreen splashScreen(pixmap);
    splashScreen.show();

	MainWindow window;
	window.show();

	window.plusSign->setIcon(QIcon("../assets/plus.png"));
	window.minusSign->setIcon(QIcon("../assets/minus.png"));

	window.btn_reset->setIcon(QIcon("../assets/reset.png"));

	window.addressCopy->setIcon(QIcon("../assets/clipboard.png"));
	window.pubKeyCopy->setIcon(QIcon("../assets/clipboard.png"));
	window.privKeyCopy->setIcon(QIcon("../assets/clipboard.png"));

	window.pubKeyShow->setIcon(QIcon("../assets/view.png"));
	window.privKeyShow->setIcon(QIcon("../assets/view.png"));

	window.bannerText1->setText("<html><head/><body><p align=\"center\"><span style=\"font-size:24pt; color:#000000;\">Welcome Back!</span></p><p align=\"center\"><span style=\"font-size:24pt; color:#000000;\">Please sign in to continue.</span><span style=\"color:#000000;\"><br/></span></p><p align=\"center\"><br/></p><p align=\"center\"><br/></p><p align=\"center\"><br/></p><p align=\"center\"><br/></p><p align=\"center\"><br/></p><p align=\"center\"><br/></p><p align=\"center\"><br/></p><p align=\"center\"><br/><br/></p><p align=\"center\"><img src=\"../assets/plasmacoin-banner.png\" width=\"550\" height=\"150\"/></p></body></html>");

	window.contactImage->setPixmap(QPixmap("../assets/contact-default.png"));
	window.btn_addContact->setIcon(QIcon("../assets/plus.png"));

	splashScreen.finish(&window);

	// std::atomic<bool> threadRunning = true;
	// std::thread sharedMem(connections::manageSharedMem, std::ref(threadRunning), std::ref(window));

	// Connect everything
	connections::minePage(window);
	connections::accountPages(window);
	connections::addressBook(window);
	connections::transactionPage(window);
	connections::addToBlock(window);
	connections::removeFromBlock(window);

	std::atomic<bool> runningThread = true;
	QFuture<void> manageSharedMem = QtConcurrent::run([&window](std::atomic<bool>& running) {
		window.ManageSharedMem(running);
	}, std::ref(runningThread));

	//sharedMem.detach();
	//threadRunning = false;

	return app.exec();
}
