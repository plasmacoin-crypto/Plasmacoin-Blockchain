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
func Dial(protocol, host, port C.cchar_t, message byte) {
	// Convert the C strings to Go strings
	var (
		goProtocol = C.GoString(protocol)
		goHost     = C.GoString(host)
		goPort     = C.GoString(port)
	)

	conn, err := net.Dial(goProtocol, net.JoinHostPort(goHost, goPort))

	if err != nil {
		log.Fatal(err)
	}

	_, writeErr := conn.Write([]byte{message})

	if writeErr != nil {
		log.Fatal("Error while writing")
	}

	conn.Close()
}

func main() {
	//Dial(C.CString("tcp"), C.CString("192.168.1.6"), C.CString("8080"), 1)
}
