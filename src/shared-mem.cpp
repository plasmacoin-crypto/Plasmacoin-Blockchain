//
// FILENAME: shared-mem.cpp | Plasmacoin Cryptocurrency
// DESCRIPTION: The source file for shared-mem.hpp
// CREATED: 2022-01-10 @ 9:58 PM
// COPYRIGHT: Copyright (c) 2021 by Ryan Smith <rysmith2113@gmail.com>
//

#include "shared-mem.hpp"
#include <iostream>

std::string shared_mem::readMemory() {
	sem_unlink("/tmp/sem");

	std::cout << "Reading memory" << std::endl;
	int shmid = shmget(shared_mem::KEY, shared_mem::MEM_SIZE, 0666);
	void* memory = shmat(shmid, nullptr, 0);

	sem_t* sem = sem_open("/tmp/sem", 0);
	//sem_t* consumer = sem_open("/tmp/consumer", IPC_CREAT, 0660, 1);

	sem_wait(sem);
	return std::string(reinterpret_cast<const char*>(memory));
	sem_post(sem);

	sem_close(sem);
	//sem_close(consumer);
}

void shared_mem::writeMemory(std::string data) {
	std::cout << "Writing memory" << std::endl;
	int shmid = shmget(shared_mem::KEY, shared_mem::MEM_SIZE, 0666 | IPC_CREAT);
	void* memory = shmat(shmid, nullptr, 0);

	sem_t* sem = sem_open("/tmp/sem", IPC_CREAT, 0660, 1);
	//sem_t* consumer = sem_open("/tmp/consumer", 0);

	sem_wait(sem);
	strcpy(reinterpret_cast<char*>(memory), data.c_str());
	sem_post(sem);

	sem_close(sem);
	//sem_close(consumer);
}
