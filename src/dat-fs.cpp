//
// FILENAME: dat-fs.cpp | Plasmacoin Cryptocurrency
// DESCRIPTION: The source file for dat-fs.hpp
// CREATED: 2021-09-19 @ 10:00 PM
// COPYRIGHT: Copyright (c) 2021 by Ryan Smith <rysmith2113@gmail.com>
//

#include "dat-fs.hpp"

void datfs::createDataPath() {
	if (!fs::exists(datfs::APP_DATA)) {
		fs::create_directory(datfs::APP_DATA); // Create a place to store application data

		// Storage for blocks and transactions in the user's wallet
		fs::create_directory(datfs::BLOCKS_LOC);
		fs::create_directory(datfs::WALLET_LOC);
	}
}

void datfs::saveBlock(Block* block) {
	QJsonObject object = json::fromBlock(block);
	QJsonDocument document = QJsonDocument(object);
	string jsonData = document.toJson(QJsonDocument::Indented).toStdString();

	// Make a new block data file
	string path = datfs::BLOCKS_LOC + DELIM + "block" + std::to_string(block->m_Index) + ".dat";
	std::ofstream dataFile(path);

	dataFile.write(jsonData.c_str(), jsonData.size()); // Write the JSON to the file
}

void datfs::saveReceipt(Receipt* receipt) {
	QJsonObject object = json::fromReceipt(receipt);
	QJsonDocument document = QJsonDocument(object);
	string jsonData = document.toJson(QJsonDocument::Indented).toStdString();

	// Make a new receipt data file
	string path = datfs::WALLET_LOC + DELIM + receipt->m_Hash.substr(0, 8) + ".dat";
	std::ofstream dataFile(path);

	dataFile.write(jsonData.c_str(), jsonData.size()); // Write the JSON to the file
}