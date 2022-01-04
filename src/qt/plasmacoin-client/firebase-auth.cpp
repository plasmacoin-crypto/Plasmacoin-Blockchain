//
// FILENAME: firebase-auth.cpp | Plasmacoin Cryptocurrency
// DESCRIPTION: The source file for firebase-auth.h
// CREATED: 2021-07-09 @ 12:15 AM
// COPYRIGHT: Copyright (c) 2021 by Ryan Smith <rysmith2113@gmail.com>
//

#include "firebase-auth.h"
#include <iostream>

Auth::Auth():
	m_Manager(new QNetworkAccessManager(this)),
	m_Reply(m_Manager->get(QNetworkRequest(QUrl("https://plasmacoin-crypto-default-rtdb.firebaseio.com/users.json"))))

	//m_UsernameValidator(new QRegularExpressionValidator(QRegularExpression(USERNAME_REGEX), this)),
	//m_PasswordValidator(new QRegularExpressionValidator(QRegularExpression(PASSWORD_REGEX), this))
{
	connect(this, &Auth::FinishedRequest, this, [this]() {
		if (m_Errors != 0) {
			emit FoundAuthErrors();
		}
	});

	connect(this, &Auth::FoundEmptyField, this, [this]() {
		AddError(ErrorCodes::EMPTY_FIELD);
	});
}

Auth::~Auth() {
	delete m_UsernameRegex;
	delete m_PasswordRegex;
}

// Sign a user up for a Plasmacoin Account
void Auth::SignUp(const QString& email, const QString& username, const QString& password) {
	m_Errors = 0;

	//
	// Evaluate the provided username and password against their
	// regular expressions. NOTE: only non-empty strings are tested.
	//

	if (username != "" && !ValidateUsername(username)) {
		AddError(ErrorCodes::INVALID_USERNAME);
	}

	if (password != "" && !ValidatePassword(password)) {
		AddError(ErrorCodes::INVALID_PASSWORD);
	}

	// Check if any of the fields are empty
	if (email.isEmpty() || username.isEmpty() || password.isEmpty()) {
		AddError(ErrorCodes::EMPTY_FIELD);
	}

	// The API URL
	QString endpoint = "https://identitytoolkit.googleapis.com/v1/accounts:signUp?key=" + m_APIKey;

	// Add the JSON information
	QVariantMap payload;
	payload["email"] = email;
	payload["password"] = password;
	payload["returnSecureToken"] = true;

	QJsonDocument jsonPayload = QJsonDocument::fromVariant(payload); // Load the QVariant as JSON
	Post(endpoint, jsonPayload); // Make a post request

	// Add the user to the RTDB
	connect(this, &Auth::UserSignedIn, this, [&, this, email, username, password]() {
		this->AddUser(email, username, password, this->m_UserID);
		this->ModUsername(username);
	});
}

// Sign a user into their Plasmacoin account
void Auth::SignIn(const QString& email, const QString& password) {
	m_Errors = 0;

	// Check if any of the fields are empty
	if (email.isEmpty() || password.isEmpty()) {
		AddError(ErrorCodes::EMPTY_FIELD);
	}

	std::cout << (uint)GetErrors() << std::endl;

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

uint8_t Auth::GetErrors() const {
	return m_Errors;
}

// A slot that perform actions on API response data
void Auth::NetworkReplyReady() {
	QByteArray response = m_Reply->readAll();
	ParseResponse(response);
}

void Auth::AddUser(const QString& email, const QString& username, const QString& password, const QString& uid) {
	QVariantMap newUser;

	// Add the new user's information
	newUser["username"] = username;
	newUser["email"] = email;
	newUser["password"] = QString(this->EncryptPassword(password.toStdString().c_str()).c_str());

	QJsonDocument body = QJsonDocument::fromVariant(newUser); // Load the QVariant as JSON
	QString jsonStr = "{\"" + uid + "\":" + QString(body.toJson(QJsonDocument::Compact)) + "}"; // Build a JSON object as a QString

	QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonStr.toUtf8()); // Convert the QString to a QJsonDocument

	Patch("https://plasmacoin-crypto-default-rtdb.firebaseio.com/users.json?auth=" + this->m_IDToken, jsonDoc);
}

void Auth::ModUsername(const QString& username) {
	connect(this, &Auth::UserSignedIn, this, &Auth::RequestToken);

	connect(this, &Auth::RequestedToken, this, [&, this, username]() {
		QString endpoint = "https://identitytoolkit.googleapis.com/v1/accounts:update?key=" + this->m_APIKey;

		// Add the user's new information
		QVariantMap modUser;
		modUser["idToken"] = this->m_IDToken;
		modUser["displayName"] = username;
		modUser["photoUrl"] = ""; // Changing account pictures won't be allowed, at least for now
		modUser["deleteAttribute"] = "PHOTO_URL";
		modUser["returnSecureToken"] = false; // This call is not meant to refresh tokens, despite the functionality being available

		QJsonDocument jsonPayload = QJsonDocument::fromVariant(modUser); // Load the QVariant as JSON
		Post(endpoint, jsonPayload); // Make a post request
	});
}

bool Auth::ValidateUsername(const QString& username) {
	return m_UsernameRegex->match(username).hasMatch();
}

bool Auth::ValidatePassword(const QString& password) {
	return m_PasswordRegex->match(password).hasMatch();
}

// Use a POST request to write data to a certain Firebase API endpoint
// Data type: QJsonDocument
void Auth::Post(const QString& url, const QJsonDocument& payload, const QString& header) {
	// Prepare a request
	QNetworkRequest request((QUrl(url)));
	request.setHeader(QNetworkRequest::ContentTypeHeader, QString(header));

	m_Reply = m_Manager->post(request, payload.toJson()); // Make the request
	connect(m_Reply, &QNetworkReply::readyRead, this, &Auth::NetworkReplyReady); // Send the data to be parsed
}

// Use a POST request to write data to a certain Firebase API endpoint
// Data type: QByteArray
void Auth::Post(const QString& url, const QByteArray& data, const QString& header) {
	// Prepare a request
	QNetworkRequest request((QUrl(url)));
	request.setHeader(QNetworkRequest::ContentTypeHeader, QString(header));
	request.setHeader(QNetworkRequest::ContentLengthHeader, data.size());

	m_Reply = m_Manager->post(request, data); // Make the request
	connect(m_Reply, &QNetworkReply::readyRead, this, &Auth::NetworkReplyReady); // Send the data to be parsed
}

// Use a PUT request to insert data at a certain Firebase API endpoint
void Auth::Put(const QString& url, const QJsonDocument& payload, const QString& header) {
	// Prepare a request
	QNetworkRequest request((QUrl(url)));
	request.setHeader(QNetworkRequest::ContentTypeHeader, QString(header));

	m_Reply = m_Manager->put(request, payload.toJson()); // Make the request
	connect(m_Reply, &QNetworkReply::readyRead, this, &Auth::NetworkReplyReady); // Send the data to be parsed
}

void Auth::Patch(const QString& url, const QJsonDocument& payload, const QString& header) {
	// Prepare a request
	QNetworkRequest request((QUrl(url)));
	request.setHeader(QNetworkRequest::ContentTypeHeader, QString(header));

	m_Reply = m_Manager->sendCustomRequest(request, "PATCH", payload.toJson()); // Make the request
	connect(m_Reply, &QNetworkReply::readyRead, this, &Auth::NetworkReplyReady); // Send the data to be parsed

	// QNetworkRequest request(destination);
	// request.setHeader(QNetworkRequest::ContentTypeHeader,
	// 	"application/x-www-form-urlencoded");
	// qDebug()<<jsonString;
	// manager->sendCustomRequest(request,"PATCH",buffer);
}

// Request that a user's ID token be regenerated. This is done by calling the Token Service
// API with the user's refresh token, which doesn't expire. The result is a new ID token for
// the user that lasts 3600 seconds (1 hour).
void Auth::RequestToken() {
	// The API URL
	QString endpoint = "https://securetoken.googleapis.com/v1/token?key=" + m_APIKey;
	QString header = "application/x-www-form-urlencoded";

	QByteArray data;
	data.append("grant_type=refresh_token");
	data.append(std::string("&refresh_token=" + m_RefreshToken.toStdString()).c_str());

	Post(endpoint, data, header); // Make a post request to the RTDB
}

// Make an authenticated GET request to the RTDB
void Auth::Get() {
	connect(this, &Auth::UserSignedIn, this, &Auth::RequestToken); // Request a new ID token

	// Make a GET request
	connect(this, &Auth::RequestedToken, this, [&, this]() {
		QString endpoint = "https://plasmacoin-crypto-default-rtdb.firebaseio.com/users.json?auth=" + m_IDToken;
		this->m_Reply = m_Manager->get(QNetworkRequest(QUrl(endpoint))); // Get data from the RTDB

		// Send the data to be parsed
		connect(this->m_Reply, &QNetworkReply::readyRead, this, &Auth::NetworkReplyReady);
	});
}

bool Auth::SearchFor(QString query) {
	QJsonDocument doc = QJsonDocument::fromJson(m_LastResponse);
	QJsonObject json = doc.object();

	return json.find(query) != json.end();
}

void Auth::ParseResponse(const QByteArray& response) {
	QJsonDocument jsonDocument = QJsonDocument::fromJson(response);
	m_LastResponse = jsonDocument.toJson();

	qDebug().noquote() << jsonDocument.toJson();

	if (jsonDocument.object().contains("error")) {
		// Get the JSON dictionary called "error" within the response object
		QVariantMap errorMap = jsonDocument.object().toVariantMap()["error"].toMap();

		//
		// Handle an email error.
		//
		// If the email is in use, it is also technically invalid, but saying it exists
		// is more specific, so handle that case first.
		//
		if (errorMap["message"].toString() == "EMAIL_EXISTS") {
			AddError(ErrorCodes::EMAIL_EXISTS);
		}
		else if (errorMap["message"].toString() == "INVALID_EMAIL" || errorMap["message"].toString() == "EMAIL_NOT_FOUND") {
			AddError(ErrorCodes::INVALID_EMAIL);
		}

		// Handle a password error
		if (
			errorMap["message"].toString() == "WEAK_PASSWORD" ||
			errorMap["message"].toString() == "INVALID_PASSWORD"
		) {
			AddError(ErrorCodes::INVALID_PASSWORD);
		}
	}
	else if (jsonDocument.object().value("kind") == "identitytoolkit#VerifyPasswordResponse") {
		m_IDToken = jsonDocument.object().value("idToken").toString();
		m_RefreshToken = jsonDocument.object().value("refreshToken").toString();
		m_UserID = jsonDocument.object().value("localId").toString();

		qDebug() << "ID token:" << m_IDToken;
		qDebug() << "Refresh token" << m_RefreshToken;

		qDebug() << "User signed in";
		emit UserSignedIn();
	}
	else if (jsonDocument.object().contains("id_token")) {
		qDebug() << "Here";
		QString refreshToken = jsonDocument.object().value("refresh_token").toString();

		m_IDToken = jsonDocument.object().value("id_token").toString();
		m_RefreshToken = (refreshToken == m_RefreshToken)? m_RefreshToken : refreshToken; // Just in case a new refresh token is issued as well

		qDebug() << "New ID token:" << m_IDToken;

		emit RequestedToken();
	}
	else {
		qDebug() << "Response:" << jsonDocument.toJson();
	}

	emit FinishedRequest();
}

// Encrypt a user's password. This is done by combining a cryptographic salt with the
// password, then using SHA-256 to hash the resulting string. Here, all the work is done
// using PBKDF2 rather than each step being perfomred separately.
std::string Auth::EncryptPassword(const std::string& _password) const {
	// ----------------------------------

	// Use Crypto++ to generate a random number. On Linux-based systems, /dev/random or /dev/urandom
	// is used to generate the number. On Windows, CryptGenRandom is used.
	CryptoPP::SecByteBlock key(CryptoPP::AES::DEFAULT_KEYLENGTH);
	std::string randomNum;

	CryptoPP::OS_GenerateRandomBlock(false, key, key.size()); // Pass `false` as the first argument to use /dev/random on Linux/macOS

	// Encode convert the number to hex, then store it as a std::string
	HexEncoder hex(new StringSink(randomNum));
	hex.Put(key, key.size());
	hex.MessageEnd();

	// ----------------------------------

	// Copy the user's password into a CryptoPP::byte array, then get its length
	size_t size = _password.size();
	byte password[size + 1];
	std::copy(std::begin(_password), std::end(_password), password);
	password[size + 1] = '\0'; // Add the terminating character when copying from std::string to char[]

	size_t plen = std::strlen(reinterpret_cast<const char*>(password));

	// Copy the salt into a CryptoPP::byte array, then get it's length
	byte salt[randomNum.size()];
	std::copy(std::begin(randomNum), std::end(randomNum), salt);
	size_t slen = std::strlen(reinterpret_cast<const char*>(salt));

	byte derived[SHA256::DIGESTSIZE];

	CryptoPP::PKCS5_PBKDF2_HMAC<SHA256> pbkdf;
	byte unused = 0;

	// Encrypt the password with the salt and SHA-256
	pbkdf.DeriveKey(derived, sizeof(derived), unused, password, plen, salt, slen, 1024, 0.0f);

	std::string result;
	HexEncoder encoder(new StringSink(result));

	encoder.Put(derived, sizeof(derived));
	encoder.MessageEnd();

	return result;
}
