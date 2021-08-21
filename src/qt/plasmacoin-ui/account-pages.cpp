//
// FILENAME: account-pages.cpp | Plasmacoin Cryptocurrency
// DESCRIPTION: The source file for account-pages.h
// CREATED: 2021-07-14 @ 2:29 PM
// COPYRIGHT: Copyright (c) 2021 by Ryan Smith <rysmith2113@gmail.com>
//

#include "account-pages.h"
#include <iostream>

AccountPages::AccountPages(
	QStackedWidget*& pages, QLabel* label1, QLabel* label2,
	QLabel* label3, QLabel* label4, QLabel* label5
):
	m_EmailSignInWarning(label1),
	m_PasswordSignInWarning(label2),
	m_EmailSignUpWarning(label3),
	m_UsernameWarning(label4),
	m_PasswordSignUpWarning(label5),

	m_AccountView(pages)
{
	// Style all of the warning labels and position them on the screen
	m_EmailSignInWarning->setStyleSheet(STYLE);
	m_EmailSignInWarning->setGeometry(540, 210, 121, 21);

	m_PasswordSignInWarning->setStyleSheet(STYLE);
	m_PasswordSignInWarning->setGeometry(540, 250, 121, 21);

	m_EmailSignUpWarning->setStyleSheet(STYLE);
	m_EmailSignUpWarning->setGeometry(540, 170, 121, 31);

	m_UsernameWarning->setStyleSheet(STYLE);
	m_UsernameWarning->setGeometry(540, 210, 121, 31);

	m_PasswordSignUpWarning->setStyleSheet(STYLE);
	m_PasswordSignUpWarning->setGeometry(540, 250, 121, 31);

	// Hide all the warning labels
	m_EmailSignInWarning->setVisible(false);
	m_PasswordSignInWarning->setVisible(false);
	m_EmailSignUpWarning->setVisible(false);
	m_UsernameWarning->setVisible(false);
	m_PasswordSignUpWarning->setVisible(false);
}

// Display a certain page of the account view
void AccountPages::DisplayPage(int index) {
	m_AccountView->setCurrentIndex(index);
}

// Get the inputs to the login fields
std::tuple<QString, QString, QString> AccountPages::ReadText() {
	switch (m_AccountView->currentIndex()) {
		case 0: { // The sign-in page
			// Fetch all QLineEdit objects on the current page
			auto fields = m_AccountView->findChildren<QLineEdit*>(
				QRegularExpression(QRegularExpression::wildcardToRegularExpression("s_*"))
			);

			if (!fields[0]->text().isEmpty() && !fields[1]->text().isEmpty()) {
				return std::make_tuple(fields[0]->text(), "", fields[1]->text());
			}
			else {
				// Highlight any empty fields with a red border. In the case that a now non-empty field
				// is highlighted, reset its border.
				for (auto field: fields) {
					if (!field->isModified() || field->text().isEmpty()) {
						field->setStyleSheet("border: 0.5px solid rgba(255, 0, 0, 150); border-radius: 2px;");
					}
					else {
						field->setStyleSheet("border-color: none;");
					}

				}
			}

			break;
		}

		case 1: {
			// Fetch all QLineEdit objects on the current page
			auto fields = m_AccountView->findChildren<QLineEdit*>(
				QRegularExpression(QRegularExpression::wildcardToRegularExpression("c_*"))
			);

			qDebug() << fields;

			if (!fields[0]->text().isEmpty() && !fields[1]->text().isEmpty() && !fields[2]->text().isEmpty()) {
				return std::make_tuple(fields[0]->text(), fields[1]->text(), fields[2]->text());
			}
			else {
				// Highlight any empty fields with a red border. In the case that a now non-empty field
				// is highlighted, reset its border.
				for (auto field: fields) {
					if (!field->isModified() || field->text().isEmpty()) {
						field->setStyleSheet("border: 0.5px solid rgba(255, 0, 0, 150); border-radius: 2px;");
					}
					else {
						field->setStyleSheet("border-color: none;");
					}

				}
			}

			break;
		}

		default:
			break;
	}

	return std::make_tuple("", "", ""); // The default return value
}