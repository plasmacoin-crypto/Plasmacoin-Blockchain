//
// FILENAME: firebase-auth.h | Plasmacoin Cryptocurrency
// DESCRIPTION: Authenticate a user to the app through the Firebase Realtime Database
// CREATED: 2021-07-09 @ 12:15 AM
// COPYRIGHT: Copyright (c) 2021 by Ryan Smith <rysmith2113@gmail.com>
//

#ifndef FIREBASE_AUTH_H
#define FIREBASE_AUTH_H

#include <QtWidgets/QMainWindow>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QJsonDocument>
#include <QJsonObject>
#include <QVariantMap>
#include <QDebug>
#include <QString>
#include <QObject>

#include "ui_mainwindow.h"

class Auth : public QMainWindow, public Ui_MainWindow {
	Q_OBJECT

public:
	Auth();

	void SignUp(const QString& email, const QString& password);
	void SignIn(const QString& email, const QString& password);

private:
	QNetworkAccessManager* m_Manager;
	QNetworkReply* m_Reply;
	QString m_APIKey = "AIzaSyCy39L5RALPFihk-akUffLx-cMGH6wWlBY";
	QString m_IDToken;

signals:
	void UserSignedIn();

public slots:
	void NetworkReplyReady();
	void DBCall();

private:
	void Post(QVariant newUser);
	void Post(const QString& url, const QJsonDocument& payload);

	void ParseResponse(const QByteArray& response);

};

#endif // FIREBASE_AUTH_H