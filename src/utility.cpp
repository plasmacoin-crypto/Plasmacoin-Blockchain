//
// FILENAME: utility.cpp | Plasmacoin Cryptocurrency
// DESCRIPTION: The source file for utility.cpp
// CREATED: 2021-02-06 @ 7:37 PM
// COPYRIGHT: Copyright (c) 2022 by Ryan Smith <rysmith2113@gmail.com>
//

#include "utility.hpp"

std::string utility::getUTCTime() {
	#if __cplusplus >= 202002L
		// Since C++20, we can get the UTC time through std::chrono::utc_clock
		std::cout << "Here" << std::endl;
		auto now = std::chrono::utc_clock::now();
		std::time_t timeNow = std::chrono::system_clock::to_time_t(now);
		return std::ctime(&timeNow);
	#else
		// Get the UTC time using the C method

		std::time_t now = std::time(0);
		std::tm* timeNow = std::gmtime(&now);

		char buf[50]; // This should be long enough for the current date and future ones as well
		std::strftime(buf, sizeof(buf), "%Y-%m-%d %X", timeNow);

		std::string strbuf = buf;
		strbuf.shrink_to_fit();
		return strbuf;
	#endif
}