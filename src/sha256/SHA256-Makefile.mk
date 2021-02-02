# The Makefile for the Plasmacoin Blockchain

CC = g++

# Compiler flags
CFLAGS = -Wall

TARGET = sha256
SOURCE = sha256.cpp

# Some aliases and defaults
default: $(TARGET)
remake: clean default

# `make`
$(TARGET): $(SOURCE)
	# Build the blockchain
	$(CC) $(CFLAGS) $(SOURCE) -g -o $(TARGET)

# `make clean`
clean:
	# This removes the binary from this directory and from /usr/bin
	sudo $(RM) --verbose $(TARGET)
