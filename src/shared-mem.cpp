//
// FILENAME: shared-mem.cpp | Plasmacoin Cryptocurrency
// DESCRIPTION: The source file for shared-mem.hpp
// CREATED: 2022-01-10 @ 9:58 PM
// COPYRIGHT: Copyright (c) 2021 by Ryan Smith <rysmith2113@gmail.com>
//

#include "shared-mem.hpp"

// Read from a block of shared memory
std::string shared_mem::readMemory() {
	// Unlink any semaphores that may be left over
	sem_unlink(shared_mem::READER_FILENAME);
	sem_unlink(shared_mem::WRITER_FILENAME);

	// Initialize new semaphores
	sem_t* writer = sem_open(shared_mem::WRITER_FILENAME, IPC_CREAT, 0660, 0);
	sem_t* reader = sem_open(shared_mem::READER_FILENAME, IPC_CREAT, 0660, 1);

	key_t key = ftok(shared_mem::FILENAME, 0);
	int shmid = shmget(key, shared_mem::BLOCK_SIZE, 0666 | IPC_CREAT);

	// Read from the shared memory block
	sem_wait(writer);
	char* memory = reinterpret_cast<char*>(shmat(shmid, nullptr, 0));
	std::string strmem = const_cast<const char*>(memory);
	sem_post(reader);

	// Close the semaphores
	sem_close(reader);
	sem_close(writer);

	std::cout << "Read: " << strmem << std::endl;

	shared_mem::detatch(memory); // Detatch from the memory
	return strmem;
}

// Write to a block of shared memory
void shared_mem::writeMemory(std::string data) {
	// Access the semaphores
	sem_t* writer = sem_open(shared_mem::WRITER_FILENAME, 0);
	sem_t* reader = sem_open(shared_mem::READER_FILENAME, 0);

	key_t key = ftok(shared_mem::FILENAME, 0);
	int shmid = shmget(key, shared_mem::BLOCK_SIZE, 0666 | IPC_CREAT);
	char* memory = reinterpret_cast<char*>(shmat(shmid, nullptr, 0));

	// Write to the shared memory block
	sem_wait(reader);
	strncpy(memory, data.c_str(), shared_mem::BLOCK_SIZE);
	sem_post(writer);

	sem_close(writer);
	sem_close(reader);

	std::cout << "Wrote: " << data << std::endl;

	shared_mem::detatch(memory); // Detatch from the memory
}

// Detatch from a block of shared memory
void shared_mem::detatch(void* block) {
	shmdt(block);
}

// Delete a block of shared memory
void shared_mem::deleteMemory(const char* const filename) {
	// Get the ID and a pointer to the memory itself
	key_t key = ftok(shared_mem::FILENAME, 0);
	int shmid = shmget(key, shared_mem::BLOCK_SIZE, 0666);
	void* memory = shmat(shmid, nullptr, 0);

	shared_mem::detatch(memory);
	shmctl(shmid, IPC_RMID, nullptr);
}

// Delete a semaphore
void shared_mem::deleteSemaphore(const char* const sem) {
	sem_unlink(sem);
}

