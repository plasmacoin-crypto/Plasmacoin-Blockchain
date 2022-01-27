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
	std::future<const char*> fut = std::async(&go::receive, "tcp", "192.168.1.44", "8080");
	std::string data = fut.get();

	shared_mem::writeMemory(data);
}

void process() {
	auto start = std::chrono::high_resolution_clock::now(); // Begin timing the function

	std::thread receive(networkDaemon);
	std::this_thread::sleep_for(std::chrono::seconds(1));
	receive.join();

	auto stop = std::chrono::high_resolution_clock::now(); // End timing
	auto duration = std::chrono::duration_cast<std::chrono::seconds>(stop - start); // Find the duration
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