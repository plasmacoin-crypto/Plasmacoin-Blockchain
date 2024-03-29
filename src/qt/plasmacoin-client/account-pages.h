//
// FILENAME: account-pages.h | Plasmacoin Cryptocurrency
// DESCRIPTION: Control the different account screens within the app
// CREATED: 2021-07-14 @ 2:29 PM
// COPYRIGHT: Copyright (c) 2021 by Ryan Smith <rysmith2113@gmail.com>
//

#ifndef ACCOUNT_PAGES_H
#define ACCOUNT_PAGES_H

#include "declare-beta-release.h"

#include <string>
#include <tuple>

using std::string;

#include <QWidget>
#include <QMainWindow>
#include <QStackedWidget>
#include <QRegularExpression>
#include <QList>
#include <QMessageBox>
#include <QString>

#include <cryptopp/secblock.h>

#include "firebase-auth.h"
#include "ui.h"
#include "dat-fs.hpp"

class AccountPages : public QMainWindow, public Ui_MainWindow {
public:
	AccountPages(
		QStackedWidget*& pages, QLabel* label1, QLabel* label2,
		QLabel* label3, QLabel* label4, QLabel* label5, QMessageBox* messageBox
	);
	~AccountPages();

	enum class PageType {SIGN_IN, SIGN_UP};

	void DisplayPage(int index) const;
	std::tuple<QString, QString, QString> ReadText();
	void DisplayErrorMsg(const string& detailedText, PageType page);

	void CacheCredentials(const string& email, const string& password);

	#ifdef BETA_RELEASE
		void CacheBetaKey(const string& betaKey);
	#endif

	QLabel *m_EmailSignInWarning, *m_PasswordSignInWarning, *m_EmailSignUpWarning,
		   *m_UsernameWarning, *m_PasswordSignUpWarning;

private:
	QStackedWidget*& m_AccountView;
	QMessageBox* m_FormErrorAlert;

	const QString STYLE = "font-size: 11pt; font-style: italic; color: rgba(255,0,0,0.784314);";
};

#endif // ACCOUNT_PAGES_H