# The Makefile for the Plasmacoin Blockchain

CC = g++

# Compiler flags
CFLAGS = -Wall

TARGET = pcblkchn
SOURCE = main.cpp
INSTALL_LOC = /usr/bin

# Used to take ownership of the binary
USER = $(shell whoami)

# Some aliases and defaults
default: $(TARGET)
all: $(TARGET)
uninstall: clean
remake: clean default

# `make`
$(TARGET): src/$(SOURCE)
	# Build the blockchain
	$(CC) $(CFLAGS) src/$(SOURCE) -o $(TARGET)

# `make clean`
clean:
	# This removes the binary from this directory and from /usr/bin
	sudo $(RM) --verbose $(TARGET) $(INSTALL_LOC)/$(TARGET) /src/sha256/*.gch

# `make install`
install:
	sudo install --verbose --owner $(USER) $(TARGET) --target-directory $(INSTALL_LOC)
