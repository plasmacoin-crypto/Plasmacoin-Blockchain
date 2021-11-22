//
// FILENAME: goexports.go | Plasmacoin Cryptocurrency
// DESCRIPTION: Go functions to be exported as C functions
// CREATED: 2021-10-16 @ 9:28 PM
// COPYRIGHT: Copyright (c) 2021 by Ryan Smith <rysmith2113@gmail.com>
//

package main

/*
typedef const char* cchar_t;
*/
import "C"

import (
	"bufio"
	"bytes"
	"compress/gzip"
	"encoding/json"
	"errors"
	"fmt"
	"io"
	"io/ioutil"
	"log"
	"net"
	"net/http"
	"os"
	"strings"
	"time"

	"github.com/plasmacoin-crypto/Plasmacoin-Blockchain/handler"
	"github.com/plasmacoin-crypto/Plasmacoin-Blockchain/netutils"
	"github.com/plasmacoin-crypto/Plasmacoin-Blockchain/tcpnet"
)

// Attempt to send a message to a specified host and port
//export dial
func dial(protocol, host, port C.cchar_t, message byte) {
	fmt.Println("Dialing...")
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

	_, err = conn.Write([]byte{message})
	netutils.Check(err, 41)

	conn.Close()
}

// Listen for and accept TCP/UDP connections
//export receive
func receive(protocol, host, port C.cchar_t) byte {
	// Convert the C strings to Go strings
	var (
		goProtocol = C.GoString(protocol)
		goHost     = C.GoString(host)
		goPort     = C.GoString(port)
	)

	//fmt.Println(goProtocol)

	// Listen for a connection
	listener, err := tcpnet.Listen(goProtocol, goHost, goPort)
	netutils.Check(err, 73)

	defer listener.Close()

	connChan := make(chan net.Conn)

	// Wait for a connection.
	go func(ch chan<- net.Conn, listener net.Listener) {
		conn, err := listener.Accept()
		netutils.Check(err, 82)

		ch <- conn
	}(connChan, listener)

	conn := <-connChan

	ch := make(chan byte)

	// Handle the connection
	go func(ch chan<- byte, conn net.Conn) {
		out := handler.HandleConnection(conn)
		ch <- out
	}(ch, conn)

	out := <-ch
	return out
}

// Compress a file using gzip
//export gzipCompress
func gzipCompress(filename C.cchar_t) C.cchar_t {
	goFilename := C.GoString(filename) // Convert from a C string to a Go string

	// Open the file
	file, err := os.Open(goFilename)
	netutils.Check(err, 108)

	// Read the contents of the file
	reader := bufio.NewReader(file)
	contents, err := ioutil.ReadAll(reader)
	netutils.Check(err, 113)

	// Create the compressed file (.gz)
	comp, err := os.Create(goFilename + ".gz")
	netutils.Check(err, 117)

	// Make a new writer
	gzwriter := gzip.NewWriter(comp)
	defer gzwriter.Close()

	// Set the header fields
	gzwriter.Name = goFilename
	gzwriter.Comment = ""
	gzwriter.ModTime = time.Now()

	// Write the compressed data to the file
	_, err = gzwriter.Write(contents)
	netutils.Check(err, 130)

	return C.CString(comp.Name())
}

// Decompress a gzip-compressed file
//export gzipDecompress
func gzipDecompress(filename C.cchar_t) C.cchar_t {
	goFilename := C.GoString(filename) // Convert from a C string to a Go string

	// Open the file for reading and writing
	input, err := os.OpenFile(goFilename, os.O_RDONLY, 0)
	netutils.Check(err, 142)

	defer input.Close()

	// Read the file as a byte slice
	b, err := ioutil.ReadFile(input.Name())
	netutils.Check(err, 148)

	// Create a byte reader and use it to make a gzip reader
	breader := bytes.NewReader(b)
	gzreader, err := gzip.NewReader(breader)

	netutils.Check(err, 154)
	defer gzreader.Close()

	// Create a destination file
	output, err := os.Create(strings.SplitAfterN(goFilename, ".gz", 1)[0])
	netutils.Check(err, 159)

	// Copy the decompressed data from the gzip reader to the destination file
	if _, err = io.Copy(output, gzreader); err != nil {
		netutils.Check(err, 163)
	}

	os.Remove(goFilename) // Delete the compressed data

	return C.CString(output.Name())
}

// Check if a port is open on a certain host
//export portIsOpen
func portIsOpen(host, port C.cchar_t) bool {
	var (
		goHost = C.GoString(host)
		goPort = C.GoString(port)
	)

	addr := net.JoinHostPort(goHost, goPort)

	if conn, err := net.DialTimeout("tcp", addr, time.Second); conn != nil && err == nil {
		defer conn.Close()
		return true
	}

	return false
}

// Get the user's global IP address by making a call to http://ip-api.com/json/.
//export getGlobalIP
func getGlobalIP() C.cchar_t {
	resp, err := http.Get("http://ip-api.com/json/") // make a GET request
	body, _ := ioutil.ReadAll(resp.Body)             // Get the response as JSON

	// Convert the JSON string to a map
	responseMap := make(map[string]string)
	json.Unmarshal(body, &responseMap)

	if err != nil || responseMap["status"] == "fail" {
		panic(errors.New("could not get user's global IP address: " + responseMap["message"]))
	}

	defer resp.Body.Close()
	return C.CString(responseMap["query"])
}

func main() {}
