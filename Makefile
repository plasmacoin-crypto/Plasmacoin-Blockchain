# The Makefile for the Plasmacoin Blockchain

CC = g++

CRYPTOPP = /usr/src/cryptopp

# Compiler flags
CFLAGS = -Wall -I$(CRYPTOPP)
LIBS = -lcryptopp

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
	$(CC) -c $(CFLAGS) -o transaction.o src/transaction.cpp -L$(CRYPTOPP) $(LINKS)

node.o: src/node.cpp src/node.hpp src/cryptopp-sha256-libs.h src/transaction.hpp \
		src/block.hpp src/blockchain.hpp
	$(CC) -c $(CFLAGS) -o node.o src/node.cpp -L$(CRYPTOPP) $(LINKS)

block.o: src/block.cpp src/block.hpp src/transaction.hpp
	$(CC) -c $(CFLAGS) -o block.o src/block.cpp -L$(CRYPTOPP) $(LINKS)

blockchain.o: src/blockchain.cpp src/blockchain.hpp src/cryptopp-sha256-libs.h src/block.hpp
	$(CC) -c $(CFLAGS) -o blockchain.o src/blockchain.cpp -L$(CRYPTOPP) $(LINKS)

# `make` (or `make pcblkchn`)
$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) src/$(SOURCE) -o $(TARGET) $(OBJECTS) -L$(CRYPTOPP) $(LINKS)

# `make clean`
clean:
	# This removes the binary from this directory and from /usr/bin
	sudo $(RM) --verbose $(TARGET) $(INSTALL_LOC)/$(TARGET)
	$(RM) $(OBJECTS)

# `make install`
install:
	sudo install --verbose --owner $(USER) $(TARGET) --target-directory $(INSTALL_LOC)
