//
// FILENAME: daemon.cpp | Plasmacoin Cryptocurrency
// DESCRIPTION: A network daemon that manages TCP connections
// CREATED: 2021-10-11 @ 9:00 PM
// COPYRIGHT: Copyright (c) 2021 by Ryan Smith <rysmith2113@gmail.com>
//

#include <iostream>
#include <unistd.h>
#include <thread>
#include <chrono>
#include <future>

namespace go {
	#include "pcnetworkd.h"
}

#include "shared-mem.hpp"

void networkDaemon() {
	std::future<const char*> fut = std::async(&go::receive, "tcp", go::getLocalIP(), "8080");
	std::string data = fut.get();

	std::cout << "Data: " << data << std::endl;

	shared_mem::writeMemory("");
	shared_mem::writeMemory(data);
}

void process() {
	std::thread(networkDaemon).join();
}

int main() {
	#ifdef __APPLE__
		//
		// On macOS, launchd will think the daemon has crashed if execution time is less than 10
		// seconds, even if nothing is actually wrong. To fix this, run the code in a loop on macOS
		// instead of running the executable over and over.
		//
		while (true) {
			process();
		}
	#else
		process();
	#endif

	return 0;
}