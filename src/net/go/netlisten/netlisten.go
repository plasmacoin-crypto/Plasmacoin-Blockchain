package main

/*
typedef const char* cchar_t;
*/
import "C"

import (
	"fmt"
	"io/ioutil"
	"net"
	"strconv"
	"sync"
)

// Read the data from a connection
func handleConnection(conn net.Conn) {
	buf, err := ioutil.ReadAll(conn)
	check(err, 20)

	fmt.Println(buf)
}

// Check for errors
func check(err error, line int) {
	if err != nil {
		var _ error = fmt.Errorf(err.Error(), " on line ", strconv.Itoa(line))
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
	var wg sync.WaitGroup
	wg.Add(1)

	conn, err := listener.Accept()
	check(err, 53)

	go func(wg *sync.WaitGroup) {
		handleConnection(conn)
		wg.Done()
	}(&wg)

	wg.Wait()
}

// Listen for and accept TCP/UDP connections
//export Receive
func Receive(protocol, host, port C.cchar_t) {
	// Convert the C strings to Go strings
	var (
		goProtocol = C.GoString(protocol)
		goHost     = C.GoString(host)
		goPort     = C.GoString(port)
	)

	fmt.Println(goHost)

	// Listen for a connection
	listener, err := listen(goProtocol, goHost, goPort)
	check(err, 77)

	defer listener.Close()

	for {
		// Wait for a connection.
		conn, err := listener.Accept()
		check(err, 84)

		// Handle the connection
		go handleConnection(conn)
	}
}

func main() {
	Receive(C.CString("tcp"), C.CString("192.168.1.6"), C.CString("8080"))

	// l, _ := listen("tcp", "192.168.1.6", "8080")
	// accept(l)
	// Receive(C.CString("tcp"), C.CString("192.168.1.6"), C.CString("8080"))
	// Dial(C.CString("tcp"), C.CString("192.168.1.6"), C.CString("8080"), C.CString("Hello, World!"))
	// accept(l)
}

//func main() {}
