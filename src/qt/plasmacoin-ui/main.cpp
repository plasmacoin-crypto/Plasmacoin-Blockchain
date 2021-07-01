
#include "mainwindow.h"

#include "ui_mainwindow.h"

#include <QtWidgets/QApplication>
#include <QtWidgets/QPushButton>

void minePage(MainWindow& window) {
	window.status.SetHeading("Mining block");

	// Mine a block when the correct button is clicked
	window.connect(window.btn_mine, &QPushButton::released, &window, [&window]() {
		window.mine.wait();
	});
}

int main(int argc, char *argv[]) {
	QApplication app(argc, argv);

	MainWindow window;
	window.show();

	minePage(window);

	return app.exec();
}
