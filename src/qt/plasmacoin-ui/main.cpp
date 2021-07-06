
#include <QtWidgets/QApplication>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QListWidgetItem>

#include "mainwindow.h"
#include "ui_mainwindow.h"

void minePage(MainWindow& window) {
	window.status.SetHeading("Mining block");

	// Mine a block when the correct button is clicked
	window.connect(window.btn_mine, &QPushButton::released, &window, [&window]() {
		window.mine.wait();
	});
}

void addToBlock(MainWindow& window) {
	// Allow adding and removal of transactions from the miner's block
	window.connect(window.plusSign, &QToolButton::released, &window, [&window]() {
		int row = window.transactionList->currentRow();
		QListWidgetItem* item = window.transactionList->item(row); // get the item at the currently selected row

		window.m_BlockContents.push_back(item); // Record the selected item
		window.blockTransactionList->addItem(item->text());
	});
}

void removeFromBlock(MainWindow& window) {
	// Allow adding and removal of transactions from the miner's block
	window.connect(window.minusSign, &QToolButton::released, &window, [&window]() {
		int row = window.blockTransactionList->currentRow();
		QListWidgetItem* item = window.blockTransactionList->item(row); // get the item at the currently selected row

		window.m_BlockContents.erase(window.m_BlockContents.begin() + row); // Remove the selected item
		window.blockTransactionList->takeItem(row);
	});
}

int main(int argc, char *argv[]) {
	QApplication app(argc, argv);

	MainWindow window;
	window.show();

	minePage(window);
	addToBlock(window);
	removeFromBlock(window);

	return app.exec();
}
