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

#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonValue>
#include <QJsonArray>

#include <cryptopp/secblock.h>
#include <cryptopp/rsa.h>

#include "block.hpp"
#include "packet-types.h"
#include "rsa-fs.hpp"

using std::vector;
using std::string;

namespace json {
	QJsonObject parse(const string& jsonstr);
	vector<string> parseArray(const QJsonObject& object, const string& key);

	uint8_t getPacketType(const QJsonObject& object);

	Block* toBlock(const QJsonObject& object);
	Transaction* toTransaction(const QJsonObject& object);
	Signature* toSignature(const QJsonObject& object);
}

#endif // PARSE_JSON_HPP