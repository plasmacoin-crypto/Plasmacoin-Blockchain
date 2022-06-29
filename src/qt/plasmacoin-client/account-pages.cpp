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
	QLabel* label3, QLabel* label4, QLabel* label5, QMessageBox* messageBox
):
	m_EmailSignInWarning(label1),
	m_PasswordSignInWarning(label2),
	m_EmailSignUpWarning(label3),
	m_UsernameWarning(label4),
	m_PasswordSignUpWarning(label5),
	m_AccountView(pages),
	m_FormErrorAlert(messageBox)
{
	// Style all of the warning labels and position them on the screen
	m_EmailSignInWarning->setStyleSheet(STYLE);
	m_EmailSignInWarning->setGeometry(480, 380, 121, 31);

	m_PasswordSignInWarning->setStyleSheet(STYLE);
	m_PasswordSignInWarning->setGeometry(480, 420, 121, 31);

	m_EmailSignUpWarning->setStyleSheet(STYLE);
	m_EmailSignUpWarning->setGeometry(480, 350, 121, 31);

	m_UsernameWarning->setStyleSheet(STYLE);
	m_UsernameWarning->setGeometry(480, 390, 121, 31);

	m_PasswordSignUpWarning->setStyleSheet(STYLE);
	m_PasswordSignUpWarning->setGeometry(480, 430, 121, 31);

	// Hide all the warning labels
	m_EmailSignInWarning->setVisible(false);
	m_PasswordSignInWarning->setVisible(false);
	m_EmailSignUpWarning->setVisible(false);
	m_UsernameWarning->setVisible(false);
	m_PasswordSignUpWarning->setVisible(false);
}

AccountPages::~AccountPages() {
	delete m_EmailSignInWarning;
	delete m_PasswordSignInWarning;
	delete m_EmailSignUpWarning;
	delete m_UsernameWarning;
	delete m_PasswordSignUpWarning;
}

// Display a certain page of the account view
void AccountPages::DisplayPage(int index) const {
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

void AccountPages::DisplayErrorMsg(const string& detailedText, PageType page) {
	string action = (page == PageType::SIGN_IN)? "sign in" : "sign up";

	m_FormErrorAlert = new QMessageBox(
		QMessageBox::Warning, "Plasmacoin Client", QString::fromStdString("Errors occured during " + action),
		QMessageBox::StandardButton::Ok
	);
	m_FormErrorAlert->setDetailedText(QString::fromStdString(detailedText));

	m_FormErrorAlert->exec();
}

void AccountPages::CacheCredentials(const string& email, const string& password) {
	string encryptedPswd;
	CryptoPP::SecByteBlock key, iv;

	std::tie(encryptedPswd, key, iv) = datfs::AESEncrypt(password);
	datfs::saveAESData(key, iv);

	CryptoPP::SecByteBlock sbb = utility::sbbFromString(encryptedPswd);
	string base64pswd = utility::sbbToBase64(sbb);

	datfs::saveLoginInfo(email, base64pswd);
}
