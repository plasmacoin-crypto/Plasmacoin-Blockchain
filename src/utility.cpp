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

// Get the nummber of seconds since the Unix Epoch (January 1, 1970)
time_t utility::getUnixEpoch() {
	std::chrono::seconds sinceEpoch = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch());
	return sinceEpoch.count();
}

// Return a formatted, human-readable string of a Unix Epoch time
string utility::formatEpoch(time_t sinceEpoch) {
	char buf[50]; // This should be long enough for the current date and future ones as well
	std::strftime(buf, sizeof(buf), "%Y-%m-%d %X", std::gmtime(&sinceEpoch));

	string strbuf = buf;
	strbuf.shrink_to_fit();
	return strbuf;
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

// Encode a CryptoPP::SecByteBlock in Base64
string utility::sbbToBase64(const CryptoPP::SecByteBlock& sbb) {
	string base64str;
	CryptoPP::Base64Encoder encoder(new CryptoPP::StringSink(base64str));

	encoder.Put(sbb.begin(), sbb.size());
	encoder.MessageEnd();

	return base64str;
}

// Decode a Base64-encoded CryptoPP::SecByteBlock
CryptoPP::SecByteBlock utility::sbbFromBase64(const string& base64str) {
	string sbbStr;

	CryptoPP::StringSource ss(base64str, true,
    	new CryptoPP::Base64Decoder(
        	new CryptoPP::StringSink(sbbStr)
    	) // Base64Decoder
	); // StringSource

	return utility::sbbFromString(sbbStr);
}

// Convert a CryptoPP::SecByteBlock to a std::string
string utility::sbbToString(const CryptoPP::SecByteBlock& sbb) {
	return string(reinterpret_cast<const char*>(&sbb[0]), sbb.size());
}

// Convert a std::string to a CryptoPP::SecByteBlock
CryptoPP::SecByteBlock utility::sbbFromString(const string& strSbb) {
	return CryptoPP::SecByteBlock(reinterpret_cast<const CryptoPP::byte*>(&strSbb[0]), strSbb.size());
}

string utility::IPv4(uint8_t o1, uint8_t o2, uint8_t o3, uint8_t o4) {
	//
	// C++20 adds support for std::format, which works similarly to sprintf defined in stdio.h/cstdio.
	// Currently, no compliers support the format header that includes the function definition. In order
	// to use this functionality, the user must have a C++20-compatible compiler, have the header file,
	// and the feature must be implemented. Otherwise, sprintf will be used.
	//
	#if __cplusplus >= 202002L && __has_include(<format>) && defined(__cpp_lib_format)
		#include <format>
		return std::format("{}.{}.{}.{}", o1, o2, o3, o4);
	#else
		char address[IPv4_MAX_LENGTH + 1]; // Make space for \0
		sprintf(address, "%d.%d.%d.%d", o1, o2, o3, o4);

		return string(address);
	#endif
}

string utility::IPv4(uint8_t o1, uint8_t o2, uint8_t o3, uint8_t o4, uint16_t port) {
	//
	// C++20 adds support for std::format, which works similarly to sprintf defined in stdio.h/cstdio.
	// Currently, no compliers support the format header that includes the function definition. In order
	// to use this functionality, the user must have a C++20-compatible compiler, have the header file,
	// and the feature must be implemented. Otherwise, sprintf will be used.
	//
	#if __cplusplus >= 202002L && __has_include(<format>) && defined(__cpp_lib_format)
		#include <format>
		return std::format("{}.{}.{}.{}:{}", o1, o2, o3, o4, port);
	#else
		char address[IPv4_MAX_LENGTH + IPv4_PORT_MAX_LENGTH + 1]; // Make space for \0
		sprintf(address, "%s:%d", IPv4(o1, o2, o3, o4).c_str(), port);

		return string(address);
	#endif
}