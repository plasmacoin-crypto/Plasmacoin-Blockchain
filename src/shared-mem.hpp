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
#include <new>
#include <iostream>
#include <unistd.h>

#include <sys/ipc.h>
#include <sys/shm.h>
#include <semaphore.h>

namespace shared_mem {
	const int32_t BLOCK_SIZE = 4096;
	const char* const FILENAME = "shared-memory";
	const char* const READER_FILENAME = "/reader";
	const char* const WRITER_FILENAME = "/writer";
	const char* const NO_DATA = "";

	std::string readMemory(bool immediate = false);
	void writeMemory(std::string data);
	void detatch(void* block);
	void deleteMemory(const char* const filename);
	void deleteSemaphore(const char* const sem);
}

#endif // SHARED_MEM_HPP