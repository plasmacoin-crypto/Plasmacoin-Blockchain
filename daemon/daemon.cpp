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

void networkDaemon() {
	std::future<const char*> fut = std::async(&go::receive, "tcp", "192.168.1.44", "8080");
	std::cout << std::string(fut.get()) << std::endl;
}

int main() {
	std::thread receive(networkDaemon);
	std::this_thread::sleep_for(std::chrono::seconds(1));

	receive.join();

	#ifdef __APPLE__
		//
		// On macOS, launchd will think the daemon has crashed if execution time is less than 10
		// seconds, even if nothing is actually wrong. To fix this, wait for 12 seconds after the
		// thread exits on Macs.
		//
		std::this_thread::sleep_for(std::chrono::seconds(12));
	#endif

	return 0;
}