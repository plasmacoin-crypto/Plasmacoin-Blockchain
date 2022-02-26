//
// FILENAME: parse-json.hpp | Plasmacoin Cryptocurrency
// DESCRIPTION: The source file for parse-json.hpp
// CREATED: 2022-01-15 @ 11:45 PM
// COPYRIGHT: Copyright (c) 2021 by Ryan Smith <rysmith2113@gmail.com>
//

#include "parse-json.hpp"

QJsonObject json::parse(const string& jsonstr) {
	QString str = QString::fromStdString(jsonstr);

	QJsonDocument json = QJsonDocument::fromJson(str.toUtf8());
	QJsonObject object = json.object();

	return object;
}

vector<string> json::parseArray(const QJsonObject& object, const string& key) {
	QJsonValue value = object.value(QString::fromStdString(key));
	QJsonArray array = value.toArray();

	vector<string> result;
	for (auto value: array) {
		result.push_back(value.toString().toStdString());
	}

	return result;
}

uint8_t json::getPacketType(const QJsonObject& object) {
	return object["type"].toInt();
}

Block* json::toBlock(const QJsonObject& object) {
	if (json::getPacketType(object) != static_cast<uint8_t>(go::PacketTypes::BLOCK)) {
		return nullptr;
	}

	// PacketType   int           `json:"type"`
	// Index        int           `json:"index"`
	// Difficulty   int64         `json:"difficulty"`
	// Nonce        int           `json:"nonce"`
	// Hash         string        `json:"hash"`
	// PrevHash     string        `json:"prevhash"`
	// CreationTime string        `json:"created"`
	// MineTime     string        `json:"mined"`
	// IsGenesis    bool          `json:"genesis"`
	// Transactions []Transaction `json:"transactions"`

	int index = object["index"].toInt();
	int nonce = object["nonce"].toInt();
	string hash = object["hash"].toString().toStdString();
	string prevHash = object["prevhash"].toString().toStdString();
	string creationTime = object["created"].toString().toStdString();
	string mineTime = object["mined"].toString().toStdString();
	bool isGenesis = object["genesis"].toBool();

	vector<Transaction*> transactions;
	auto array = object["transactions"].toArray();

	for (auto trxn: array) {
		transactions.push_back(json::toTransaction(trxn.toObject()));
	}

	Block* block = new Block(index, nonce, hash, prevHash, creationTime, mineTime, transactions, isGenesis);
	return block;
}

Transaction* json::toTransaction(const QJsonObject& object) {
	// PacketType    int       `json:"type"`
	// SenderAddr    string    `json:"senderAddr"`
	// RecipientAddr string    `json:"recipientAddr"`
	// CreationTime  string    `json:"created"`
	// SigningTime   string    `json:"signed"`
	// Amount        float32   `json:"amount"`
	// Fee           float32   `json:"fee"`
	// Content       string    `json:"content"`
	// Signature     Signature `json:"sigfield"`
	// Hash          string    `json:"hash"`

	string senderAddr = object["senderAddr"].toString().toStdString();
	string recipientAddr = object["recipientAddr"].toString().toStdString();
	string creationTime = object["created"].toString().toStdString();
	string signingTime = object["signed"].toString().toStdString();
	float amount = object["amount"].toDouble();
	float fee = object["fee"].toDouble();
	string content = object["content"].toString().toStdString();
	Signature* signature = json::toSignature(object["sigfield"].toObject());
	string hash = object["hash"].toString().toStdString();

	Transaction* transaction = new Transaction(senderAddr, recipientAddr, creationTime, signingTime, amount, fee, content, signature, hash);
	return transaction;
}

Signature* json::toSignature(const QJsonObject& object) {
	// Signature string `json:"signature"`
	// PublicKey []byte `json:"publicKey"`
	// Length    int    `json:"length"`

	string signature = object["signature"].toString().toStdString();
	string strPublicKey = object["publicKey"].toString().toStdString();
	size_t length = object["length"].toInt();

	CryptoPP::SecByteBlock sbb(reinterpret_cast<const unsigned char*>(signature.data()), signature.size());

	CryptoPP::StringSource ssource(strPublicKey, true);
	CryptoPP::RSA::PublicKey publicKey;
	publicKey.Load(ssource);

	Signature* sigfield = new Signature {sbb, publicKey, length};
	return sigfield;
}