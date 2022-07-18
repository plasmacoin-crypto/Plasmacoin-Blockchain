//
// FILENAME: shared-mem.hpp | Plasmacoin Cryptocurrency
// DESCRIPTION: Manage IPC through shared memeory
// CREATED: 2022-01-10 @ 9:58 PM
// COPYRIGHT: Copyright (c) 2021 by Ryan Smith <rysmith2113@gmail.com>
//

#ifndef SHARED_MEM_HPP
#define SHARED_MEM_HPP

#include <string>
#include <cstring>
#include <iostream>
#include <unistd.h>
#include <thread>
#include <chrono>

#if defined(__APPLE__) || defined(__linux__)
	#include <sys/ipc.h>
	#include <sys/shm.h>
	#include <fcntl.h>
	#include <semaphore.h>
#elif defined(WIN32)
	// Include necessary Windows IPC/semaphore libraries
#endif

namespace shared_mem {
	const int32_t BLOCK_SIZE = 4096;
	const char* const FILENAME = "shared-memory";
	const char* const READER_FILENAME = "/reader";
	const char* const WRITER_FILENAME = "/writer";
	const char* const NO_DATA = "";
	const int32_t TRYWAIT_FAILURE = -1;

	const mode_t PERMISSIONS = 0666;

	#ifdef __APPLE__
		const mode_t CREATE = IPC_CREAT;
		const mode_t BLOCK_CREATE = PERMISSIONS | CREATE;
	#elif defined(__linux__)
		const mode_t SEM_CREATE = O_CREAT | O_EXCL;
		const mode_t BLOCK_CREATE = PERMISSIONS | IPC_CREAT;
	#endif

	std::string readMemory(bool immediate = false);
	void writeMemory(std::string data);

	void detatch(void* block);
	void deleteMemory(const char* const filename);
	void deleteSemaphore(const char* const sem);
}

#endif // SHARED_MEM_HPP