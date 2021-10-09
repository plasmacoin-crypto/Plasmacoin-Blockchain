package main

import "C"

import (
	"log"
	"net"
)

// Attempt to send a message to a specified host and port
// 
//export Dial
func Dial(protocol, host, port, message string) {
	conn, err := net.Dial(protocol, net.JoinHostPort(host, port))

	if err != nil {
		log.Fatal(err)
	}

	_, writeErr := conn.Write([]byte(message))

	if writeErr != nil {
		log.Fatal("Error while writing")
	}

	conn.Close()
}

func main() {}
