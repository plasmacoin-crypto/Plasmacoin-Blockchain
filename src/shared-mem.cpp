//
// FILENAME: shared-mem.cpp | Plasmacoin Cryptocurrency
// DESCRIPTION: The source file for shared-mem.hpp
// CREATED: 2022-01-10 @ 9:58 PM
// COPYRIGHT: Copyright (c) 2021 by Ryan Smith <rysmith2113@gmail.com>
//

#include "shared-mem.hpp"

#ifdef __APPLE__
	// Read from a block of shared memory
	std::string shared_mem::readMemory(bool immediate) {
		// Unlink any semaphores that may be left over
		sem_unlink(shared_mem::READER_FILENAME);
		sem_unlink(shared_mem::WRITER_FILENAME);

		// Initialize new semaphores
		sem_t* writer = sem_open(shared_mem::WRITER_FILENAME, shared_mem::CREATE, shared_mem::PERMISSIONS, 0);
		sem_t* reader = sem_open(shared_mem::READER_FILENAME, shared_mem::CREATE, shared_mem::PERMISSIONS, 1);

		std::cout << (writer == SEM_FAILED) << std::endl;

		key_t key = ftok(shared_mem::FILENAME, 0);
		int shmid = shmget(key, shared_mem::BLOCK_SIZE, shared_mem::PERMISSIONS | shared_mem::CREATE);

		// Read from the shared memory block. If `immediate` is true, only read if a semaphore
		// decrement is immediately possible.
		if (immediate) {
			int result = sem_trywait(writer);
			if (result == EAGAIN) {
				return shared_mem::NO_DATA;
			}
		}
		else {
			sem_wait(writer);
		}

		char* memory = reinterpret_cast<char*>(shmat(shmid, nullptr, 0));
		std::string strmem = const_cast<const char*>(memory);
		sem_post(reader);

		// Close the semaphores
		sem_close(reader);
		sem_close(writer);

		shared_mem::detatch(memory); // Detatch from the memory
		return strmem;
	}

	// Write to a block of shared memory
	void shared_mem::writeMemory(std::string data) {
		// Unlink any semaphores that may be left over
		sem_unlink(shared_mem::READER_FILENAME);
		sem_unlink(shared_mem::WRITER_FILENAME);

		// Access the semaphores
		sem_t* writer = sem_open(shared_mem::WRITER_FILENAME, 0);
		sem_t* reader = sem_open(shared_mem::READER_FILENAME, 0);

		key_t key = ftok(shared_mem::FILENAME, 0);
		int shmid = shmget(key, shared_mem::BLOCK_SIZE, shared_mem::PERMISSIONS | shared_mem::CREATE);
		char* memory = reinterpret_cast<char*>(shmat(shmid, nullptr, 0));

		// Write to the shared memory block
		sem_wait(reader);
		strncpy(memory, data.c_str(), shared_mem::BLOCK_SIZE);
		sem_post(writer);

		sem_close(writer);
		sem_close(reader);

		shared_mem::detatch(memory); // Detatch from the memory
	}

#elif defined(__linux__)
	// Read from a block of shared memory
	std::string shared_mem::readMemory(bool immediate) {
		std::cout << "Reading" << std::endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(100));

		// Access the semaphores
		sem_t* writer = sem_open(shared_mem::WRITER_FILENAME, 0);
		sem_t* reader = sem_open(shared_mem::READER_FILENAME, 0);

		std::cout << (writer == SEM_FAILED) << std::endl;

		// Read from the shared memory block. If `immediate` is true, only read if a semaphore
		// decrement is immediately possible.
		if (immediate) {
			int result = sem_trywait(writer);
			if (result == EAGAIN) {
				return shared_mem::NO_DATA;
			}
		}
		else {
			sem_wait(writer);
		}

		key_t key = ftok(shared_mem::FILENAME, 0);
		int shmid = shmget(key, shared_mem::BLOCK_SIZE, shared_mem::BLOCK_CREATE);

		// Read from the shared memory block
		char* shmem = static_cast<char*>(shmat(shmid, (void*)0, 0));
		std::string data = const_cast<const char*>(shmem);

		sem_post(reader);

		// Close the semaphores
		sem_close(reader);
		sem_close(writer);

		shared_mem::detatch(shmem); // Detatch from the memory

		// destroy the shared memory
		shmctl(shmid, IPC_RMID, nullptr);

		return data;
	}

	// Write to a block of shared memory
	void shared_mem::writeMemory(std::string data) {
		std::cout << "Writing" << std::endl;

		// Unlink any semaphores that may be left over
		sem_unlink(shared_mem::READER_FILENAME);
		sem_unlink(shared_mem::WRITER_FILENAME);

		// Initialize new semaphores
		sem_t* writer = sem_open(shared_mem::WRITER_FILENAME, shared_mem::SEM_CREATE, shared_mem::PERMISSIONS, 0);
		sem_t* reader = sem_open(shared_mem::READER_FILENAME, shared_mem::SEM_CREATE, shared_mem::PERMISSIONS, 1);

		std::cout << (writer == SEM_FAILED) << std::endl;

		key_t key = ftok(shared_mem::FILENAME, 0);
		int shmid = shmget(key, shared_mem::BLOCK_SIZE, shared_mem::BLOCK_CREATE);
		char* shmem = (char*)shmat(shmid, (void*)0, 0);

		// Write to the shared memory block
		sem_wait(reader);
		memcpy(shmem, (char*)data.c_str(), shared_mem::BLOCK_SIZE);
		sem_post(writer);

		sem_close(writer);
		sem_close(reader);

		std::cout << "Wrote: " << data << std::endl;

		shared_mem::detatch(shmem); // Detatch from the memory
	}

#endif

// Detatch from a block of shared memory
void shared_mem::detatch(void* block) {
	shmdt(block);
}

// Delete a block of shared memory
void shared_mem::deleteMemory(const char* const filename) {
	// Get the ID and a pointer to the memory itself
	key_t key = ftok(shared_mem::FILENAME, 0);
	int shmid = shmget(key, shared_mem::BLOCK_SIZE, shared_mem::BLOCK_CREATE);
	void* memory = shmat(shmid, nullptr, 0);

	shared_mem::detatch(memory);
	shmctl(shmid, IPC_RMID, nullptr);
}

// Delete a semaphore
void shared_mem::deleteSemaphore(const char* const sem) {
	sem_unlink(sem);
}
