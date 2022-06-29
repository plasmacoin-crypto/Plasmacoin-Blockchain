//
// FILENAME: dat-fs.cpp | Plasmacoin Cryptocurrency
// DESCRIPTION: The source file for dat-fs.hpp
// CREATED: 2021-09-19 @ 10:00 PM
// COPYRIGHT: Copyright (c) 2021 by Ryan Smith <rysmith2113@gmail.com>
//

#include "dat-fs.hpp"

// Create a place to store application data
void datfs::createDataPath() {
	std::vector<string> directories = {
		datfs::APP_DATA, datfs::BLOCKS_LOC,
		datfs::WALLET_LOC, datfs::CREDS_LOC
	};

	for (auto dir: directories) {
		if (!fs::exists(dir)) {
			fs::create_directory(dir);
		}
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

void datfs::saveLoginInfo(const string& email, const string& password) {
	QJsonObject object;
	object["email"] = QString::fromStdString(email);
	object["password"] = QString::fromStdString(password);

	QJsonDocument document(object);
	string jsonData = document.toJson(QJsonDocument::Indented).toStdString();

	// Make a new AES data file
	string path = datfs::CREDS_LOC + DELIM + "credentials.json";
	std::ofstream dataFile(path);

	dataFile.write(jsonData.c_str(), jsonData.size()); // Write the JSON to the file
}

std::pair<string, string> datfs::loadLoginInfo() {
	// Read the credentials file as a JSON document
	string path = datfs::CREDS_LOC + DELIM + "credentials.json";
	QFile jsonFile(QString::fromStdString(path));
    jsonFile.open(QFile::ReadOnly);
	QJsonDocument document(QJsonDocument::fromJson(jsonFile.readAll()));

	// Convert the document to a JSON object
	QJsonObject object = document.object();

	// Read the data. The email is plaintext, but the password is Base64-encoded binary.
	string email = object["email"].toString().toStdString();
	CryptoPP::SecByteBlock sbbpswd = utility::sbbFromBase64(object["password"].toString().toStdString());

	// Load the AES key and initialization vector
	CryptoPP::SecByteBlock key, iv;
	std::tie(key, iv) = datfs::loadAESData();

	string password = datfs::AESDecrypt(utility::sbbToString(sbbpswd), key, iv); // Decrypt the password

	return std::make_pair(email, password);
}

bool datfs::hasCredCache() {
	return (
		fs::exists(datfs::CREDS_LOC + datfs::DELIM + "credentials.json") &&
		fs::exists(datfs::CREDS_LOC + datfs::DELIM + "aes_secrets.json")
	);
}

void datfs::saveAESData(const CryptoPP::SecByteBlock& key, const CryptoPP::SecByteBlock& iv) {
	// Convert the secret key and initialization vector to Base64 strings
	string base64key = utility::sbbToBase64(key);
	string base64iv = utility::sbbToBase64(iv);

	QJsonObject object;
	object["key"] = QString::fromStdString(base64key);
	object["iv"] = QString::fromStdString(base64iv);

	QJsonDocument document(object);
	string jsonData = document.toJson(QJsonDocument::Indented).toStdString();

	// Make a new AES data file
	string path = datfs::CREDS_LOC + DELIM + "aes_secrets.json";
	std::ofstream dataFile(path);

	dataFile.write(jsonData.c_str(), jsonData.size()); // Write the JSON to the file
}

std::pair<CryptoPP::SecByteBlock, CryptoPP::SecByteBlock> datfs::loadAESData() {
	// Read the data file as a JSON document
	string path = datfs::CREDS_LOC + DELIM + "aes_secrets.json";
	QFile jsonFile(QString::fromStdString(path));
    jsonFile.open(QFile::ReadOnly);
	QJsonDocument document(QJsonDocument::fromJson(jsonFile.readAll()));

	// Convert the document to a JSON object
	QJsonObject object = document.object();

	// Read the data as Base64 and convert it to SecByteBlocks
	string strKey = object["key"].toString().toStdString();
	string strIv = object["iv"].toString().toStdString();

	CryptoPP::SecByteBlock key = utility::sbbFromBase64(strKey);
	CryptoPP::SecByteBlock iv = utility::sbbFromBase64(strIv);

	return std::make_pair(key, iv);
}

std::tuple<string, CryptoPP::SecByteBlock, CryptoPP::SecByteBlock> datfs::AESEncrypt(const string& message) {
	CryptoPP::AutoSeededRandomPool prng;
    CryptoPP::HexEncoder encoder(new CryptoPP::FileSink(std::cout));

    CryptoPP::SecByteBlock key(AES::DEFAULT_KEYLENGTH);
    CryptoPP::SecByteBlock iv(AES::BLOCKSIZE);

	// Create blocks for the secret key and initialization vector
    prng.GenerateBlock(key, key.size());
    prng.GenerateBlock(iv, iv.size());

    std::string cipher;

	// Encrypt the message using AES in CBC mode
	try {
        CryptoPP::CBC_Mode<AES>::Encryption encrypter;
        encrypter.SetKeyWithIV(key, key.size(), iv);

        CryptoPP::StringSource ssource(message, true,
            new CryptoPP::StreamTransformationFilter(encrypter,
                new CryptoPP::StringSink(cipher)
            ) // StreamTransformationFilter
        ); // StringSource
    }
    catch (const CryptoPP::Exception& e) {
        std::cerr << e.what() << std::endl;
        exit(1);
    }

	return std::make_tuple(cipher, key, iv);
}

string datfs::AESDecrypt(const string& cipher, const CryptoPP::SecByteBlock& key, const CryptoPP::SecByteBlock& iv) {
	string recovered;

	try {
        CryptoPP::CBC_Mode<AES>::Decryption decrypter;
        decrypter.SetKeyWithIV(key, key.size(), iv);

        CryptoPP::StringSource ssource(cipher, true,
            new CryptoPP::StreamTransformationFilter(decrypter,
                new CryptoPP::StringSink(recovered)
            ) // StreamTransformationFilter
        ); // StringSource
    }
    catch (const CryptoPP::Exception& e) {
        std::cerr << e.what() << std::endl;
        exit(1);
    }

	return recovered;
}