
#include "mainwindow.h"

#include <QtWidgets/QApplication>

int main(int argc, char *argv[]) {
	QApplication app(argc, argv);

	MainWindow window;
	window.show();

	window.status.SetHeading("Hello");

	return app.exec();
}
