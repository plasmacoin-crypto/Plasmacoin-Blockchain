
#include <QtWidgets/QApplication>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QListWidgetItem>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "firebase-auth.h"

// Allow the user to mine their block
void minePage(MainWindow& window) {
	window.m_Status.SetHeading("Mining block");

	// Mine a block when the correct button is clicked
	window.connect(window.btn_mine, &QPushButton::released, &window, [&window]() {
		window.mine.wait();
	});
}

// Allow the user to type information in forms (QLineEdits) and be authenticated to
// the app through the Firebase REST API
void accountPages(MainWindow& window) {
	// Take a user from the sign in screen to the sign up screen
	window.connect(window.btn_create, &QPushButton::released, &window, [&window]() {
		window.m_AccPgs->DisplayPage(1);
	});

	// Sign a user into their account
	window.connect(window.btn_signIn, &QPushButton::released, &window, [&window]() {
		QString email, username, password;
		std::tie(email, username, password) = window.m_AccPgs->ReadText(); // Get the user's entries

		window.m_Authenticator->SignIn(email, password);
	});

	window.connect(window.btn_signUp, &QPushButton::released, &window, [&window]() {
		QString email, username, password;
		std::tie(email, username, password) = window.m_AccPgs->ReadText(); // Get the user's entries

		window.m_Authenticator->SignUp(email, username, password);
	});

	// Take the user to the logged in view if Firebase successfully logged them in
	window.connect(window.m_Authenticator, &Auth::UserSignedIn, &window, [&window]() {
		if (!window.m_Authenticator->SearchFor("error")) {
			window.m_AccPgs->DisplayPage(2);
		}
	});

	// Display a warning when a user tries to create an account with an email that's in use
	window.connect(window.m_Authenticator, &Auth::EmailExists, &window, [&window]() {
		window.m_AccPgs->m_EmailWarning->setText("Email in use");
		window.m_AccPgs->m_EmailWarning->setVisible(true);
	});

	// Display a warning when a user tries to create an account with an invalid email
	window.connect(window.m_Authenticator, &Auth::InvalidEmail, &window, [&window]() {
		window.m_AccPgs->m_EmailWarning->setText("Invalid email");
		window.m_AccPgs->m_EmailWarning->setVisible(true);
	});

	// Display a warning when a user tries to create an account with an email that's in use
	window.connect(window.m_Authenticator, &Auth::UsernameTaken, &window, [&window]() {
		window.m_AccPgs->m_EmailWarning->setText("Username already in use");
		window.m_AccPgs->m_EmailWarning->setVisible(true);
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
		// To remove a transaction, the only requirement is that it's been selected on
		// the list of transactions in user's block
		if (window.blockTransactionList->selectedItems().size() != 0) {
			int row = window.blockTransactionList->currentRow();
			QListWidgetItem* item = window.blockTransactionList->item(row); // get the item at the currently selected row

			window.m_BlockContents.erase(window.m_BlockContents.begin() + row); // Remove the selected item
			window.blockTransactionList->takeItem(row);
		}
	});
}

// Run the application
int main(int argc, char* argv[]) {
	QApplication app(argc, argv);

	MainWindow window;
	window.show();

	// Connect everything
	minePage(window);
	addToBlock(window);
	removeFromBlock(window);
	accountPages(window);

	return app.exec();
}
