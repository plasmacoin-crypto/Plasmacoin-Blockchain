package main

import "C"

import (
	"fmt"
	"io/ioutil"
	"log"
	"net"
)

// Read the data from a connection
func handleConnection(conn net.Conn) {
	buf, err := ioutil.ReadAll(conn)

	if err != nil {
		log.Fatal("Error while reading.")
	}

	fmt.Println(string(buf))
}

// Listen for connections on a specified host and port
//
//export Listen
func Listen(protocol, host, port string) (net.Listener, error) {
	listener, err := net.Listen(protocol, net.JoinHostPort(host, port))

	if err != nil {
		return nil, err
	}

	return listener, nil
}

// Accept a TCP connection from a client
//
// export Accept
func Accept(listener net.Listener) {
	for {
		conn, err := listener.Accept()

		if err != nil {
			log.Fatal("An error occured while accepting a connection.")
		}

		go handleConnection(conn)
	}
}
