//
// FILENAME: account-pages.h | Plasmacoin Cryptocurrency
// DESCRIPTION: Control the different account screens within the app
// CREATED: 2021-07-14 @ 2:29 PM
// COPYRIGHT: Copyright (c) 2021 by Ryan Smith <rysmith2113@gmail.com>
//

#include <string>
#include <tuple>

#include <QtWidgets/QWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QStackedWidget>
#include <QRegularExpression>
#include <QList>

#include "firebase-auth.h"
#include "ui_mainwindow.h"

class AccountPages : public QMainWindow, public Ui_MainWindow {
public:
	AccountPages(QStackedWidget*& pages, QLabel* label1, QLabel* label2, QLabel* label3);

	void DisplayPage(int index);
	std::tuple<QString, QString, QString> ReadText();

	QLabel *m_EmailWarning, *m_UsernameWarning, *m_PasswordWarning;

private:
	QStackedWidget*& m_AccountView;

	const QString STYLE = "font-size:11pt;font-style:italic;color:rgba(255,0,0,0.784314);";
};