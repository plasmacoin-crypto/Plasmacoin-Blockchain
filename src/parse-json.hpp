//
// FILENAME: parse-json.hpp | Plasmacoin Cryptocurrency
// DESCRIPTION: Get data about packets sent/received by Plasmacoin
// CREATED: 2022-01-15 @ 11:45 AM
// COPYRIGHT: Copyright (c) 2021 by Ryan Smith <rysmith2113@gmail.com>
//

#ifndef PARSE_JSON_HPP
#define PARSE_JSON_HPP

#include <string>
#include <vector>

#include <QtGlobal>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonValue>
#include <QJsonArray>

#include <cryptopp/secblock.h>
#include <cryptopp/rsa.h>
#include <cryptopp/config_int.h>

#include "packet-types.h"
#include "idcode.hpp"
#include "transaction.hpp"
#include "block.hpp"
#include "sync-request.hpp"
#include "utility.hpp"
#include "pending-trxn.hpp"
#include "removal-request.hpp"

using std::vector;
using std::string;

namespace json {
	QJsonObject parse(const string& jsonstr);
	//string stringify(const QJsonObject& objectT)

	vector<string> parseArray(const QJsonObject& object, const string& key);

	uint8_t getPacketType(const QJsonObject& object);

	IDCode* toIDCode(const QJsonObject& object);
	Transaction* toTransaction(const QJsonObject& object);
	Block* toBlock(const QJsonObject& object);
	Signature* toSignature(const QJsonObject& object);
	Receipt* toReceipt(const QJsonObject& object);
	SyncRequest* toSyncRequest(const QJsonObject& object);
	PendingTransaction* toPendingTrxn(const QJsonObject& object);
	RemovalRequest* toRemovalRequest(const QJsonObject& object);

	QJsonObject fromTransaction(Transaction* transaction);
	QJsonObject fromBlock(Block* block);
	QJsonObject fromSignature(Signature* signature);
	QJsonObject fromReceipt(Receipt* reciept);
}

#endif // PARSE_JSON_HPP