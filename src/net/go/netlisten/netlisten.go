package main

/*
typedef const char* cchar_t;
*/
import "C"

import (
	"fmt"
	"io/ioutil"
	"log"
	"net"
	"strconv"
)

// Read the data from a connection
func handleConnection(conn net.Conn) {
	buf, err := ioutil.ReadAll(conn)

	if err != nil {
		log.Fatal("Error while reading.")
	}

	fmt.Println(string(buf))
}

// Check for errors
func check(err error, line int) {
	if err != nil {
		log.Fatal(err.Error() + " on line " + strconv.Itoa(line))
	}
}

// Listen for connections on a specified host and port
func listen(protocol, host, port string) (net.Listener, error) {
	listener, err := net.Listen(protocol, net.JoinHostPort(host, port))

	if err != nil {
		return nil, err
	}

	return listener, nil
}

// Accept a TCP connection from a client
func accept(listener net.Listener) {
	for {
		conn, err := listener.Accept()
		check(err, 49)

		go handleConnection(conn)
	}
}

// Recieve and accept TCP/UDP connections
//export Receive
func Receive(protocol, host, port C.cchar_t) {
	// Convert the C strings to Go strings
	var (
		goProtocol = C.GoString(protocol)
		goHost     = C.GoString(host)
		goPort     = C.GoString(port)
	)

	listener, err := listen(goProtocol, goHost, goPort)
	check(err, 66)

	accept(listener)
}

func main() {}
