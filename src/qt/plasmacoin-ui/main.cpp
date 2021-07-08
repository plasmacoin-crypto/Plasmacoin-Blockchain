
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

// Allow the user to add transactions to their block
void addToBlock(MainWindow& window) {
	window.connect(window.plusSign, &QToolButton::released, &window, [&window]() {
		auto selected = window.transactionList->selectedItems();
		int row = window.transactionList->currentRow();

		// A user will only be able to add a transaction if:
		//
		// 1) They have selected a transaction from the list on the right (no blank selections)
		// 2) They have not added that transaction previously (no adding duplicate elements)
		//
		if ((selected.size() != 0) && (window.blockTransactionList->findItems(selected.front()->text(), Qt::MatchFixedString).size() == 0)) {
			QListWidgetItem* item = window.transactionList->item(row); // Get the item at the currently selected row

			window.m_BlockContents.push_back(item); // Record the selected item
			window.blockTransactionList->addItem(item->text());
		}
	});
}

// Allow the user to remove transactions from their block
void removeFromBlock(MainWindow& window) {
	window.connect(window.minusSign, &QToolButton::released, &window, [&window]() {
		// To remove a transaction, the only requirement is that it's selected
		if (window.blockTransactionList->selectedItems().size() != 0) {
			int row = window.blockTransactionList->currentRow();
			QListWidgetItem* item = window.blockTransactionList->item(row); // get the item at the currently selected row

			window.m_BlockContents.erase(window.m_BlockContents.begin() + row); // Remove the selected item
			window.blockTransactionList->takeItem(row);
		}
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
