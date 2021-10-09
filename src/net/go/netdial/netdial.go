package main

/*
typedef const char* cchar_t;
*/
import "C"

import (
	"log"
	"net"
)

// Attempt to send a message to a specified host and port
//export Dial
func Dial(protocol, host, port, message C.cchar_t) {
	// Convert the C strings to Go strings
	var (
		goProtocol = C.GoString(protocol)
		goHost     = C.GoString(host)
		goPort     = C.GoString(port)
		goMessage  = C.GoString(message)
	)

	conn, err := net.Dial(goProtocol, net.JoinHostPort(goHost, goPort))

	if err != nil {
		log.Fatal(err)
	}

	_, writeErr := conn.Write([]byte(goMessage))

	if writeErr != nil {
		log.Fatal("Error while writing")
	}

	conn.Close()
}

func main() {}
