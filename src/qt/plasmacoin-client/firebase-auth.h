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
#include <future>

#include <QtWidgets/QMainWindow>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QVariantMap>
#include <QDebug>
#include <QString>
#include <QObject>
#include <QUrlQuery>
#include <QRegularExpression>
#include <QRegularExpressionValidator>

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
	enum class ErrorCodes: uint8_t {
		EMAIL_EXISTS 	 = 1 << 0,
		USERNAME_TAKEN 	 = 1 << 1,
		INVALID_EMAIL	 = 1 << 2,
		INVALID_USERNAME = 1 << 3,
		INVALID_PASSWORD = 1 << 4,
		EMPTY_FIELD		 = 1 << 5,

		LAST			 = 6	// This is probably okay
	};

	Auth();
	~Auth();

	void SignUp(const QString& email, const QString& username, const QString& password);
	void SignIn(const QString& email, const QString& password);

	uint8_t GetErrors() const;
	inline void AddError(const ErrorCodes& error);

private:
	QNetworkAccessManager* m_Manager;
	QNetworkReply* m_Reply;
	QString m_APIKey = "AIzaSyCy39L5RALPFihk-akUffLx-cMGH6wWlBY";
	QString m_IDToken, m_RefreshToken, m_UserID;
	QByteArray m_LastResponse; // The last JSON response from the REST API
	QRegularExpressionValidator *m_UsernameValidator, *m_PasswordValidator;

	QRegularExpression* m_UsernameRegex = new QRegularExpression("^([^\\.\\-])([_]{0,})(?=.{2,20}$)(?<![\\.\\-])(?!.*[_\\.\\-]{})[\\w_\\.\\-]+([^\\._\\-]|(?![_]))(?!\\.\\-)(?<![\\.\\-])$");
	QRegularExpression* m_PasswordRegex = new QRegularExpression("^((?=\\S*?[A-Z])(?=\\S*?[a-z])(?=\\S*?[0-9]).{6,})\\S$");

	uint8_t m_Errors = 0; // Stores a number that corresponds to certain authentication errors

public:
	bool ValidateUsername(const QString& username);
	bool ValidatePassword(const QString& password);

signals:
	void FinishedRequest();

	void UserSignedIn();
	void RequestedToken();

	void FoundAuthErrors();
	void FoundEmptyField();

public slots:
	void NetworkReplyReady();
	void RequestToken();

private:
	void AddUser(const QString& email, const QString& username, const QString& password, const QString& uid);
	void ModUsername(const QString& username);

	// HTTP Request Implementations
	void Post(const QString& url, const QJsonDocument& payload, const QString& header = "application/json");
	void Post(const QString& url, const QByteArray& data, const QString& header = "application/json");

	void Put(const QString& url, const QJsonDocument& payload, const QString& header = "application/json");

	void Patch(const QString& url, const QJsonDocument& payload, const QString& header = "application/json");

public:
	void Get(); // HTTP GET request
	bool SearchFor(QString query);

private:
	void ParseResponse(const QByteArray& response);
	std::string EncryptPassword(const std::string& _password) const;
};

inline void Auth::AddError(const ErrorCodes& error) {
	m_Errors |= static_cast<uint8_t>(error);
}

#endif // FIREBASE_AUTH_H