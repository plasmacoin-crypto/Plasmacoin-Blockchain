
#include <functional>
#include <atomic>

#include <QApplication>
#include <QSplashScreen>
#include <QPixmap>
#include <QIcon>

#include "mainwindow.h"
#include "ui.h"
#include "connections.hpp"

// Run the application
int main(int argc, char* argv[]) {
	QApplication app(argc, argv);

	// const char* block[] = {
	// 	"2", "0", "1", "52", "0", "", "", "", "true", "1", "",
	// 	"", "", "", "1", "1", "", "IIIIII4ggg", "MzA4MjAxQTAzMDBEMDYwOTJBODY0ODg2RjcwRDAxMDEwMTA1MDAwMzgyMDE4RDAwMzA4MjAxODgwMjgyMDE4MTAwQTBGRDI5QzU0N0M0MERBRDI2MjAxNDBDQjg1RTJDRjVBQUNBRDI1OUVDQ0IyRDdCREEzQkE5NjBBQkUyRTkxRUI4N0EwN0M0NEZDMkM1RTgwNUI0NzM1RTlFMTdGN0UxQjFCOEFGRjQxM0E2QTdBRjRERUFDMEY3OENGMDY0QzNCQ0I4QzkzQUVCQURCRkFCQTlEMjcxOEFCNDkxNDBCRUVGNEZDQTI0ODc5MDQxMjZDNTNFRUNFNERDNzcwQUZDMDU1NkMxRkVFN0U0RTI4MzBDODUxQTU2MTI4NEU5MUNBMEJCOTFGNTlCNUUwREIzQkEzNTY1QUUzNTQ4RDExQkQ1REVBQjgxMDlBNzI0MDlDQkRGNkU2NDEyQzBCRjI4NDhEMjI5MzIyN0NDRUYwRURFQjdDQjY5RTE4NkE0MTY1MkNBM0JDNDA4MDQ3RTc1NDE1NzAxNTQzQTY3MkYxQThEM0YxRThGRTIzMDY4Q0VFRjEwRkNDQTdFMTgxQkM0RDVBRTExQTE5Q0ZGMzZFNEZBREQ0NkQ2NEY3MjYzNjM1NDJCNDkzNTVGNTU0RkU3NkIyMzlGOUJCQTdGRDE1RDAzRjYxM0FEQURCQ0JFNTI2QkQ3MkRGNzQ5QThDMzQ2MDhGMjVDOUE2QUI2RjZDMDFGQzYxQzEwMzUwMTc4MzI0QTJDN0VBRTI5RTQ5QjE3M0VFRDlENUJBREVBNDVEQzQ2MTA0RDZBREFCNzU1NEFFMERBMzNENDdGMzlEODUwMDlCOERBMDRBQ0YyMDBEQjZBREI3MjMzQTg3MTdGMzAxOEM2Q0E3NzY3MTc1Qjc3RTYyOEY4NjFBRDRBQkU1NzRDN0U4NjBEMUE1NjBCOEVBNEM3QkU1ODc3NjMxMDI2NjIzNkQ4NkJGRDlFNDRGMTk2ODlDQ0Y5MEM4QkNEN0U1NDkwMzBCNzk4M0NEMDU4REM4MDEzN0YwMDEzMUEwNDRDQ0U5Njc3Q0Y4NkJBOUI0MjNEMkE1QkI0QjJCNTRCMDIwMTEx", "384", "", ""
	// };
	// go::GoSlice slice = {block, 22, 22};

	// go::joinGroup("en0", utility::IPv4(224, 0, 0, 251).c_str(), 5001);
	// go::sendMulticast(utility::IPv4(224, 0, 0, 251).c_str(), 5001, 2, slice);

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

	window.btn_first->setIcon(QIcon("../assets/double-left-arrow.png"));
	window.btn_previous->setIcon(QIcon("../assets/arrow-left.png"));
	window.btn_next->setIcon(QIcon("../assets/arrow-right.png"));
	window.btn_last->setIcon(QIcon("../assets/double-right-arrow.png"));
	window.btn_sync->setIcon(QIcon("../assets/sync.png"));

	splashScreen.finish(&window);

	// std::atomic<bool> threadRunning = true;
	// std::thread sharedMem(connections::manageSharedMem, std::ref(threadRunning), std::ref(window));

	// Connect everything
	connections::minePage(window);
	connections::accountPages(window);
	connections::addressBook(window);
	connections::transactionPage(window);
	connections::blockchainPage(window);
	connections::addToBlock(window);
	connections::removeFromBlock(window);

	std::atomic<bool> runningThread = true;

	QFuture<void> manageSharedMem = QtConcurrent::run([&window](std::atomic<bool>& running) {
		while (running) {
			window.ManageSharedMem();
		}
	}, std::ref(runningThread));

	app.connect(&app, &QApplication::aboutToQuit, &window, [&runningThread]() mutable {
		runningThread = false;
	});

	return app.exec();
}
