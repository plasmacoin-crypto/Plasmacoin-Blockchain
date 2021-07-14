//
// FILENAME: firebase-auth.cpp | Plasmacoin Cryptocurrency
// DESCRIPTION: The source file for firebase-auth.h
// CREATED: 2021-07-09 @ 12:15 AM
// COPYRIGHT: Copyright (c) 2021 by Ryan Smith <rysmith2113@gmail.com>
//

#include "firebase-auth.h"

Auth::Auth():
	m_Manager(new QNetworkAccessManager(this)),
	m_Reply(m_Manager->get(QNetworkRequest(QUrl("https://plasmacoin-crypto-default-rtdb.firebaseio.com/users.json"))))
{
	//connect(this, &Auth::UserSignedIn, this, &Auth::DBCall);
}

// Sign a user up for a Plasmacoin Account
void Auth::SignUp(const QString& email, const QString& password) {
	// The API URL
	QString endpoint = "https://identitytoolkit.googleapis.com/v1/accounts:signUp?key=" + m_APIKey;

	// Add the JSON information
	QVariantMap payload;
	payload["email"] = email;
	payload["password"] = password;
	payload["returnSecureToken"] = true;

	QJsonDocument jsonPayload = QJsonDocument::fromVariant(payload); // Load the QVariant as JSON
	Post(endpoint, jsonPayload); // Make a post request

	// Add the new user's information
	//QVariantMap newUser;
	//newUser["name"] = "John";
	//newUser["email"] = "johndoe@example.com";

}

// Sign a user into their Plasmacoin account
void Auth::SignIn(const QString& email, const QString& password) {
	// The API URL
	QString endpoint = "https://identitytoolkit.googleapis.com/v1/accounts:signInWithPassword?key=" + m_APIKey;

	// Add the JSON information
	QVariantMap payload;
	payload["email"] = email;
	payload["password"] = password;
	payload["returnSecureToken"] = true;

	QJsonDocument jsonPayload = QJsonDocument::fromVariant(payload); // Load the QVariant as JSON
	Post(endpoint, jsonPayload); // Make a post request
}

// This is a signal that notifies other objects that a user signed in. It has no
// implementation here.
void UserSignedIn() {}

// A slot that perform actions on API response data
void Auth::NetworkReplyReady() {
	QByteArray response = m_Reply->readAll();
	ParseResponse(response);
}

// Make an authenticated call to the RTDB
void Auth::DBCall() {
	QString endpoint = "https://plasmacoin-crypto-default-rtdb.firebaseio.com/users.json?auth=" + m_IDToken;
	m_Reply = m_Manager->get(QNetworkRequest(QUrl(endpoint))); // Get data from the RTDB

	connect(m_Reply, &QNetworkReply::readyRead, this, &Auth::NetworkReplyReady); // Send the data to be parsed
}

void Auth::Post(QVariant newUser) {
	QJsonDocument jsonDoc = QJsonDocument::fromVariant(newUser); // Load the QVariant as JSON

	// Make a post request to the RTDB
	QNetworkRequest addUser(QUrl("https://plasmacoin-crypto-default-rtdb.firebaseio.com/users.json"));
	addUser.setHeader(QNetworkRequest::ContentTypeHeader, QString("application/json"));
	m_Manager->post(addUser, jsonDoc.toJson()); // Send the data
}

void Auth::Post(const QString& url, const QJsonDocument& payload) {
	// Make a post request to the RTDB
	QNetworkRequest addUser((QUrl(url)));
	addUser.setHeader(QNetworkRequest::ContentTypeHeader, QString("application/json"));
	m_Reply = m_Manager->post(addUser, payload.toJson()); // Send the data

	connect(m_Reply, &QNetworkReply::readyRead, this, &Auth::NetworkReplyReady); // Send the data to be parsed
}

void Auth::ParseResponse(const QByteArray& response) {
	QJsonDocument jsonDocument = QJsonDocument::fromJson(response);

	if (jsonDocument.object().contains("error")) { // Handle a failure
		qDebug() << "Error:" << response;
	}
	else if (jsonDocument.object().contains("kind")) { // Handle a successful call
		m_IDToken = jsonDocument.object().value("idToken").toString();
		qDebug() << "Recieved token:" << m_IDToken;

		qDebug() << "User signed in";
		emit UserSignedIn();
	}
	else {
		qDebug() << "Response:" << response;
	}
}
