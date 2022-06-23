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

IDCode* json::toIDCode(const QJsonObject& object) {
	// Code int `json:"code"`
	auto value = object.value("code");

	if (value == QJsonValue::Undefined) {
		IDCode* idCode = new IDCode {static_cast<uint8_t>(go::IDCodes::ERROR)};
		return idCode;
	}

	uint8_t code = object.value("code").toInt();

	IDCode* idCode = new IDCode {code};
	return idCode;
}

Transaction* json::toTransaction(const QJsonObject& object) {
	// PacketType    int       `json:"type"`
	// SenderAddr    string    `json:"senderAddr"`
	// RecipientAddr string    `json:"recipientAddr"`
	// CreationTime  int64     `json:"created"`
	// SigningTime   int64     `json:"signed"`
	// Amount        float64   `json:"amount"`
	// Fee           float64   `json:"fee"`
	// Content       string    `json:"content"`
	// Signature     Signature `json:"sigfield"`
	// Hash          string    `json:"hash"`

	string senderAddr = object["senderAddr"].toString().toStdString();
	string recipientAddr = object["recipientAddr"].toString().toStdString();
	time_t creationTime = object["created"].toInt();
	time_t signingTime = object["signed"].toInt();
	double amount = object["amount"].toDouble();
	double fee = object["fee"].toDouble();
	string content = object["content"].toString().toStdString();
	Signature* signature = json::toSignature(object["sigfield"].toObject());
	string hash = object["hash"].toString().toStdString();

	Transaction* transaction = new Transaction(senderAddr, recipientAddr, creationTime, signingTime, amount, fee, content, signature, hash);
	return transaction;
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
	// MinerAddr    string        `json:"miner"`
	// CreationTime int64         `json:"created"`
	// MineTime     int64         `json:"mined"`
	// IsGenesis    bool          `json:"genesis"`
	// Transactions []Transaction `json:"transactions"`

	int index = object["index"].toInt();
	int difficulty = object["difficulty"].toInt();
	int nonce = object["nonce"].toInt();
	string hash = object["hash"].toString().toStdString();
	string prevHash = object["prevhash"].toString().toStdString();
	string minerAddr = object["miner"].toString().toStdString();
	time_t creationTime = object["created"].toInt();
	time_t mineTime = object["mined"].toInt();
	bool isGenesis = object["genesis"].toBool();

	vector<Transaction*> transactions;
	auto array = object["transactions"].toArray();

	qDebug() << array;

	for (auto trxn: array) {
		transactions.push_back(json::toTransaction(trxn.toObject()));
	}

	Block* block = new Block(index, nonce, hash, prevHash, minerAddr, creationTime, mineTime, transactions, difficulty, isGenesis);
	return block;
}


Signature* json::toSignature(const QJsonObject& object) {
	// Signature string `json:"signature"`
	// PublicKey string `json:"publicKey"`
	// Length    int    `json:"length"`

	qDebug() << "Debug to:" << object;

	string strSignature = object["signature"].toString().toStdString();
	string strPublicKey = object["publicKey"].toString().toStdString();
	size_t length = object["length"].toInt();

	CryptoPP::SecByteBlock signature = utility::sigFromBase64(strSignature);
	CryptoPP::RSA::PublicKey publicKey = utility::pubKeyFromBase64(strPublicKey);

	Signature* sigfield = new Signature {signature, publicKey, length};
	return sigfield;
}

Receipt* json::toReceipt(const QJsonObject& object) {
	string senderAddr = object["senderAddr"].toString().toStdString();
	string recipientAddr = object["receipientAddr"].toString().toStdString();
	time_t trxnCreated = object["trxnCreated"].toInt();
	time_t signTime = object["signed"].toInt();
	double amount = object["amount"].toDouble();
	double fee = object["fee"].toDouble();
	Signature* signature = json::toSignature(object["sigfield"].toObject());
	string hash = object["hash"].toString().toStdString();

	Receipt* receipt = new Receipt(senderAddr, recipientAddr, trxnCreated, signTime, amount, fee, *signature, hash);
	return receipt;
}

SyncRequest* json::toSyncRequest(const QJsonObject& object) {
	int syncType = object["synctype"].toInt();
	string host = object["host"].toString().toStdString();

	SyncRequest* syncRequest = new SyncRequest {syncType, host};
	return syncRequest;
}

PendingTransaction* json::toPendingTrxn(const QJsonObject& object) {
	time_t timestamp = object["timestamp"].toInt();
	string hash = object["hash"].toString().toStdString();
	double amount = QString::number(object["amount"].toDouble(), 'f', 10).toDouble();

	PendingTransaction* pendingTrxn = new PendingTransaction {timestamp, hash, amount};
	return pendingTrxn;
}

RemovalRequest* json::toRemovalRequest(const QJsonObject& object) {
	std::string senderIP = object["senderIP"].toString().toStdString();

	RemovalRequest* remRequest = new RemovalRequest {senderIP};
	return remRequest;
}

QJsonObject json::fromTransaction(Transaction* transaction) {
	QJsonObject object;

	object["senderAddr"] = QString::fromStdString(transaction->m_SenderAddr);
	object["recipientAddr"] = QString::fromStdString(transaction->m_RecipientAddr);
	object["created"] = static_cast<int64_t>(transaction->m_CreationTime);
	object["signed"] = static_cast<int64_t>(transaction->m_SignTime);
	object["amount"] = QString::number(transaction->m_Amount, 'f', 10).toDouble();
	object["fee"] = QString::number(transaction->m_Fee, 'f', 5).toDouble();
	object["content"] = QString::fromStdString(transaction->m_Content);
	object["sigfield"] = json::fromSignature(&transaction->m_Signature);
	object["hash"] = QString::fromStdString(transaction->m_Hash);

	return object;
}

QJsonObject json::fromBlock(Block* block) {
	QJsonObject object;

	object["index"] = block->m_Index;
	object["difficulty"] = block->m_Difficulty;
	object["nonce"] = block->m_Nonce;
	object["hash"] = QString::fromStdString(block->m_Hash);
	object["prevhash"] = QString::fromStdString(block->m_PrevHash);
	object["miner"] = QString::fromStdString(block->m_MinerAddr);
	object["created"] = static_cast<qint64>(block->m_CreationTime);
	object["mined"] = static_cast<qint64>(block->m_MineTime);
	object["genesis"] = block->m_IsGenesis;

	QJsonArray transactions;

	for (auto trxn: block->m_Transactions) {
		QJsonObject trxnObject = json::fromTransaction(trxn);
		transactions.append(QJsonValue(trxnObject));
	}

	object["transactions"] = transactions;

	return object;
}

QJsonObject json::fromSignature(Signature* signature) {
	QJsonObject object;

	string strSignature = utility::sigToBase64(signature->m_Signature);
	string strPublicKey = utility::pubKeyToBase64(signature->m_PublicKey);

	object["signature"] = QString::fromStdString(strSignature);
	object["publicKey"] = QString::fromStdString(strPublicKey);
	object["length"] = static_cast<int64_t>(signature->m_Length);

	return object;
}

QJsonObject json::fromReceipt(Receipt* receipt) {
	QJsonObject object;

	object["sender"] = QString::fromStdString(receipt->m_SenderAddr);
	object["receipient"] = QString::fromStdString(receipt->m_RecipientAddr);
	object["created"] = static_cast<qint64>(receipt->m_TransactionTime);
	object["signed"] = static_cast<qint64>(receipt->m_SignTime);
	object["amount"] = QString::number(receipt->m_Amount, 'f', 10).toDouble();
	object["fee"] = QString::number(receipt->m_Fee, 'f', 5).toDouble();
	object["sigfield"] = json::fromSignature(&receipt->m_Signature);
	object["hash"] = QString::fromStdString(receipt->m_Hash);

	return object;
}