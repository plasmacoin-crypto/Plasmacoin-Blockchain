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

#include <sys/ipc.h>
#include <sys/shm.h>
#include <semaphore.h>

namespace shared_mem {
	const int32_t MEM_SIZE = 1024;
	const key_t KEY = ftok("/", 97);

	std::string readMemory();
	void writeMemory(std::string data);
}

#endif // SHARED_MEM_HPP