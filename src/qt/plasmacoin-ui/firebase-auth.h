//
// FILENAME: firebase-auth.h | Plasmacoin Cryptocurrency
// DESCRIPTION: Authenticate a user to the app through the Firebase Realtime Database
// CREATED: 2021-07-09 @ 12:15 AM
// COPYRIGHT: Copyright (c) 2021 by Ryan Smith <rysmith2113@gmail.com>
//

#ifndef FIREBASE_AUTH_H
#define FIREBASE_AUTH_H

#include <string>
#include <cstring>
#include <iterator>
#include <algorithm>

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
#include <QUrlQuery>

#include <cryptopp/cryptlib.h>
#include <cryptopp/pwdbased.h>
#include <cryptopp/sha.h>
#include <cryptopp/hex.h>
#include <cryptopp/osrng.h>

#include "ui_mainwindow.h"

using CryptoPP::byte;
using CryptoPP::SHA256;
using CryptoPP::HexEncoder;
using CryptoPP::StringSink;

class Auth : public QMainWindow, public Ui_MainWindow {
	Q_OBJECT

public:
	Auth();

	void SignUp(const QString& email, const QString& username, const QString& password);
	void SignIn(const QString& email, const QString& password);

private:
	QNetworkAccessManager* m_Manager;
	QNetworkReply* m_Reply;
	QString m_APIKey = "AIzaSyCy39L5RALPFihk-akUffLx-cMGH6wWlBY";
	QString m_IDToken, m_RefreshToken;

signals:
	void UserSignedIn();
	void RequestedToken();

public slots:
	void NetworkReplyReady();

private:
	void AddUser(const QString& email, const QString& username, const QString& password);

	void Post(const QString& url, const QJsonDocument& payload, const QString& header = "application/json");
	void Post(const QString& url, const QByteArray& data, const QString& header = "application/json");

public:
	void RequestToken();

public:
	void Get();
	bool SearchFor(std::string query);

private:
	void ParseResponse(const QByteArray& response);
	std::string EncryptPassword(std::string _password);
};

#endif // FIREBASE_AUTH_H