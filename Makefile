# The Makefile for the Plasmacoin Blockchain

CC = g++

CRYPTO_CPP = /usr/src/cryptocpp

# Compiler flags
CFLAGS = -Wall -I$(CRYPTO_CPP)
LINKS = -lcryptopp

TARGET = pcblkchn
SOURCE = main.cpp
OBJECTS = transaction.o node.o block.o blockchain.o
INSTALL_LOC = /usr/bin

# Used to take ownership of the binary
USER = $(shell whoami)

default: $(TARGET)
all: $(TARGET)
uninstall: clean
remake: clean default

# Objects
transaction.o: src/transaction.cpp src/transaction.hpp
	$(CC) -c $(CFLAGS) -o transaction.o src/transaction.cpp -L$(CRYPTO_CPP) $(LINKS)

node.o: src/node.cpp src/node.hpp src/cryptopp-sha256-libs.h src/transaction.hpp src/block.hpp
	$(CC) -c $(CFLAGS) -o node.o src/node.cpp -L$(CRYPTO_CPP) $(LINKS)

block.o: src/block.cpp src/block.hpp src/transaction.hpp
	$(CC) -c $(CFLAGS) -o block.o src/block.cpp -L$(CRYPTO_CPP) $(LINKS)

blockchain.o: src/blockchain.cpp src/blockchain.hpp src/cryptopp-sha256-libs.h src/block.hpp
	$(CC) -c $(CFLAGS) -o blockchain.o src/blockchain.cpp -L$(CRYPTO_CPP) $(LINKS)

# `make` (or `make pcblkchn`)
$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) src/$(SOURCE) -o $(TARGET) $(OBJECTS) -L$(CRYPTO_CPP) $(LINKS)
# `make clean`
clean:
	# This removes the binary from this directory and from /usr/bin
	sudo $(RM) --verbose $(TARGET) $(INSTALL_LOC)/$(TARGET)

# `make install`
install:
	sudo install --verbose --owner $(USER) $(TARGET) --target-directory $(INSTALL_LOC)
