//
// FILENAME: parse-json.hpp | Plasmacoin Cryptocurrency
// DESCRIPTION: Parse a JSON string
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

using std::vector;
using std::string;

namespace json {
	QJsonObject parse(const string& jsonstr);
	vector<string> parseArray(const QJsonObject& object, const string& key);
}

#endif // PARSE_JSON_HPP