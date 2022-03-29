//
// FILENAME: utility.cpp | Plasmacoin Cryptocurrency
// DESCRIPTION: The source file for utility.cpp
// CREATED: 2021-02-06 @ 7:37 PM
// COPYRIGHT: Copyright (c) 2022 by Ryan Smith <rysmith2113@gmail.com>
//

#include "utility.hpp"

string utility::getUTCTime() {
	#if __cplusplus >= 202002L
		// Since C++20, we can get the UTC time through std::chrono::utc_clock

		auto now = std::chrono::utc_clock::now();
		std::time_t timeNow = std::chrono::system_clock::to_time_t(now);

		return std::ctime(&timeNow);
	#else
		// Get the UTC time using the C method

		std::time_t now = std::time(0);
		std::tm* timeNow = std::gmtime(&now);

		char buf[50]; // This should be long enough for the current date and future ones as well
		std::strftime(buf, sizeof(buf), "%Y-%m-%d %X", timeNow);

		string strbuf = buf;
		strbuf.shrink_to_fit();
		return strbuf;
	#endif
}

// Encode a raw RSA key in Base64
string utility::pubKeyToBase64(const CryptoPP::RSAFunction& rsaKey) {
	CryptoPP::ByteQueue queue;
	CryptoPP::Base64Encoder encoder;

	rsaKey.Save(queue);
	rsafs::saveBase64(rsafs::TMP_PATH.c_str(), queue);

	return rsafs::readBase64(rsafs::TMP_PATH.c_str(), queue);
}

// Decode a Base64 RSA key to a raw RSA key
CryptoPP::RSAFunction utility::pubKeyFromBase64(const string& base64key) {
	CryptoPP::Base64Decoder decoder;
	CryptoPP::ByteQueue queue;
	decoder.Put((const CryptoPP::byte*)base64key.data(), base64key.size());
	decoder.MessageEnd();

	rsafs::saveToFile(rsafs::TMP_PATH.c_str(), decoder);
	CryptoPP::RSAFunction rsaKey;

	try {
		CryptoPP::FileSource file(rsafs::TMP_PATH.c_str(), true);
		rsaKey.BERDecode(file); // Clean up the temporary file

		fs::remove(rsafs::TMP_PATH);
		return rsaKey;
	}
	catch (const CryptoPP::Exception& e) {
		std::cerr << e.what() << std::endl;
		fs::remove(rsafs::TMP_PATH); // Clean up the temporary file
   		exit(1);
	}
}

// Encode an RSA signature (as a CryptoPP::SecByteBlock) in Base64
string utility::sigToBase64(const CryptoPP::SecByteBlock& signature) {
	string base64sig;
	CryptoPP::Base64Encoder encoder(new CryptoPP::StringSink(base64sig));

	encoder.Put(signature.begin(), signature.size());
	encoder.MessageEnd();

	return base64sig;
}

// Decode a Base64 RSA signature to a CryptoPP::SecByteBlock
CryptoPP::SecByteBlock utility::sigFromBase64(const string& base64sig) {
	string strSig;

	CryptoPP::StringSource ss(base64sig, true,
    	new CryptoPP::Base64Decoder(
        	new CryptoPP::StringSink(strSig)
    	) // Base64Decoder
	); // StringSource

	return utility::sbbFromString(strSig);
}

// Convert a CryptoPP::SecByteBlock to a std::string
string utility::sbbToString(const CryptoPP::SecByteBlock& sbb) {
	return string(reinterpret_cast<const char*>(&sbb[0]), sbb.size());
}

// Convert a std::string to a CryptoPP::SecByteBlock
CryptoPP::SecByteBlock utility::sbbFromString(const string& strSbb) {
	return CryptoPP::SecByteBlock(reinterpret_cast<const CryptoPP::byte*>(&strSbb[0]), strSbb.size());
}