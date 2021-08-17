//
// FILENAME: account-pages.cpp | Plasmacoin Cryptocurrency
// DESCRIPTION: The source file for account-pages.h
// CREATED: 2021-07-14 @ 2:29 PM
// COPYRIGHT: Copyright (c) 2021 by Ryan Smith <rysmith2113@gmail.com>
//

#include "account-pages.h"
#include <iostream>

AccountPages::AccountPages(QStackedWidget*& pages, QLabel* label1, QLabel* label2, QLabel* label3):
	m_EmailWarning(label1),
	m_UsernameWarning(label2),
	m_PasswordWarning(label3),

	m_AccountView(pages)
{
	// Style all of the warning labels and position them on the screen
	m_EmailWarning->setStyleSheet(STYLE);
	m_EmailWarning->setGeometry(540, 170, 121, 31);

	m_UsernameWarning->setStyleSheet(STYLE);
	m_UsernameWarning->setGeometry(540, 210, 121, 31);

	m_PasswordWarning->setStyleSheet(STYLE);
	m_PasswordWarning->setGeometry(540, 250, 121, 31);

	// Hide all the warning labels
	m_EmailWarning->setVisible(false);
	m_UsernameWarning->setVisible(false);
	m_PasswordWarning->setVisible(false);
}

// Display a certain page of the account view
void AccountPages::DisplayPage(int index) {
	m_AccountView->setCurrentIndex(index);
}

// Get the inputs to the login fields
std::tuple<QString, QString, QString> AccountPages::ReadText() {
	//std::tuple<QString, QString, QString>

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