# The Makefile for the SHA-256 hashing algorithm used on the blockchain.
# The final generated executable will run a set of tests on the code (i.e.,
# hash a bunch of example words).
#
# Note that this Makefile can be used by the main Makefile in the root
# directory. You can use this functionality by running `make sha256`
# with the root Makefile.
#

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
	# Build the SHA-256 tests
	$(CC) $(CFLAGS) $(SOURCE) -g -o $(TARGET)

# `make clean`
clean:
	# This removes the binary from this directory
	sudo $(RM) --verbose $(TARGET)
