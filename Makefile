# The Makefile for the Plasmacoin Blockchain
#
# Using this Makefile, you can build the blockchain source code as
# well as tests for the SHA-256 library implemented for this project.
#

CC = g++

# Compiler flags
CFLAGS = -Wall

TARGET = pcblkchn
SOURCE = main.cpp
INSTALL_LOC = /usr/bin

# Stuff for building the SHA-256 Library
SHA_256_LOC = src/sha256

SHA_256 = $(SHA_256_LOC)/sha256
SHA_256_SRC = $(SHA_256_LOC)/sha256.cpp
SHA_256_MF = SHA256-Makefile.mk

# Used to take ownership of the binary
USER = $(shell whoami)

# Some aliases and defaults
default: $(TARGET)
sha256: $(SHA_256)

# This will make the blockchain and the SHA-256 library tests
all: $(TARGET) $(SHA_256)

uninstall: clean

remake: clean default
remake-all: clean-all all

# `make` (or more specifically, `make pcblkchn`)
$(TARGET): src/$(SOURCE)
	# Build the blockchain
	$(CC) $(CFLAGS) src/$(SOURCE) -o $(TARGET)

# `make sha256`
$(SHA_256): $(SHA_256_SRC)
	make -C $(SHA_256_LOC) -f $(SHA_256_MF)

# `make clean`
clean:
	# This removes the binary from this directory and from /usr/bin
	sudo $(RM) --verbose $(TARGET) $(INSTALL_LOC)/$(TARGET)

# `make clean_all`
clean-all: clean
	# Clean the blockchain and the SHA-256 executables
	make -C $(SHA_256_LOC) -f $(SHA_256_MF) clean

# `make install`
install:
	sudo install --verbose --owner $(USER) $(TARGET) --target-directory $(INSTALL_LOC)
