# The Makefile for the Plasmacoin Blockchain

CC = gcc
CXX = g++

CRYPTOPP = /usr/src/cryptopp

# Compiler flags
CFLAGS = -Wall -I$(CRYPTOPP)
CXXFLAGS = $(CFLAGS) -std=c++17
LIBS = -lcryptopp -lstdc++fs

TARGET = pcblkchn
SOURCE = main.cpp
OBJECTS = transaction.o node.o block.o blockchain.o merkle-helpers.o rsa-fs.o dat-fs.o
INSTALL_LOC = /usr/bin

# Used to take ownership of the binary
USER = $(shell whoami)

default: $(TARGET)
all: $(TARGET)
uninstall: clean
remake: clean default

# Objects
transaction.o: src/transaction.cpp src/transaction.hpp
	$(CXX) -c $(CXXFLAGS) -o transaction.o src/transaction.cpp -L$(CRYPTOPP) $(LIBS)

node.o: src/node.cpp src/node.hpp src/cryptopp-sha256-libs.h src/transaction.hpp \
		src/block.hpp src/blockchain.hpp src/rsa-fs.hpp src/dat-fs.hpp
	$(CXX) -c $(CXXFLAGS) -o node.o src/node.cpp -L$(CRYPTOPP) $(LIBS)

block.o: src/block.cpp src/block.hpp src/transaction.hpp
	$(CXX) -c $(CXXFLAGS) -o block.o src/block.cpp -L$(CRYPTOPP) $(LIBS)

blockchain.o: src/blockchain.cpp src/blockchain.hpp src/cryptopp-sha256-libs.h src/block.hpp \
			  src/merkle-helpers.h
	$(CXX) -c $(CXXFLAGS) -o blockchain.o src/blockchain.cpp -L$(CRYPTOPP) $(LIBS)

merkle-helpers.o: src/merkle-helpers.c src/merkle-helpers.h
	$(CXX) -c $(CXXFLAGS) -o merkle-helpers.o src/merkle-helpers.c $(LIBS)

rsa-fs.o: src/rsa-fs.cpp src/rsa-fs.hpp
	$(CXX) -c $(CXXFLAGS) -o rsa-fs.o src/rsa-fs.cpp -L$(CRYPTOPP) $(LIBS)

dat-fs.o: src/dat-fs.cpp src/dat-fs.hpp src/block.hpp
	$(CXX) -c $(CXXFLAGS) -o dat-fs.o src/dat-fs.cpp -L$(CRYPTOPP) $(LIBS)

# `make` (or `make pcblkchn`)
$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) src/$(SOURCE) -o $(TARGET) $(OBJECTS) -L$(CRYPTOPP) $(LIBS)

# `make clean`
clean:
	# This removes the binary from this directory and from /usr/bin
	sudo $(RM) --verbose $(TARGET) $(INSTALL_LOC)/$(TARGET)
	$(RM) $(OBJECTS)

# `make install`
install:
	sudo install --verbose --owner $(USER) $(TARGET) --target-directory $(INSTALL_LOC)
