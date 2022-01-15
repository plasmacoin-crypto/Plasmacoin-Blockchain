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