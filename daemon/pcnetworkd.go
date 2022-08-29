//
// FILENAME: pcnetworkd.go | Plasmacoin Cryptocurrency
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
	"unsafe"

	bccnstrx "github.com/plasmacoin-crypto/Plasmacoin-Blockchain/blockchainconstructs"
	"github.com/plasmacoin-crypto/Plasmacoin-Blockchain/handler"
	"github.com/plasmacoin-crypto/Plasmacoin-Blockchain/netlisten"
	"github.com/plasmacoin-crypto/Plasmacoin-Blockchain/netutils"
)

const (
	IDCode = uint8(iota)
	Transaction
	Block
	Node
	NodeList
	Receipt
	UserQuery
	SyncRequest
	PendingTrxn
	RemovalRequest
)

// Attempt to send a message to a specified host and port
//
//export dial
func dial(protocol, host C.cchar_t, port C.cchar_t, dataType uint8, data []C.cchar_t) {
	// Convert the C strings to Go strings
	var (
		goProtocol = C.GoString(protocol)
		goHost     = C.GoString(host)
		goPort     = C.GoString(port)
		goData     = make([]string, len(data))
	)

	for i, str := range data {
		goData[i] = C.GoString(str)
	}

	// Determine what is being sent over TCP
	jsonData := makeStruct(dataType, goData)
	if jsonData == nil {
		return
	}

	conn, err := net.DialTimeout(goProtocol, net.JoinHostPort(goHost, goPort), time.Second*5)
	if err != nil {
		log.Println(err.Error())
		return
	}

	jsonBytes, _ := json.Marshal(jsonData)
	fmt.Printf("Packet: %s\n", string(jsonBytes))

	_, err = conn.Write(jsonBytes)
	netutils.Check(err, 81)

	conn.Close()
}

// Listen for and accept TCP/UDP connections
//
//export receive
func receive(protocol, host, port C.cchar_t) C.cchar_t {
	// Convert the C strings to Go strings
	var (
		goProtocol = C.GoString(protocol)
		goHost     = C.GoString(host)
		goPort     = C.GoString(port)
	)

	//fmt.Println(goProtocol)

	// Listen for a connection
	listener, err := netlisten.Listen(goProtocol, goHost, goPort)
	netutils.Check(err, 106)

	defer listener.Close()

	connChan := make(chan net.Conn)

	// Wait for a connection.
	go func(ch chan<- net.Conn, listener net.Listener) {
		conn, err := listener.Accept()
		netutils.Check(err, 115)

		ch <- conn
	}(connChan, listener)

	conn := <-connChan

	ch := make(chan struct {
		string
		uint8
	})

	// Handle the connection
	go func(ch chan<- struct {
		string
		uint8
	}, conn net.Conn) {
		out, packetType := handler.HandleConnection(conn)
		if out != nil {
			ch <- struct {
				string
				uint8
			}{string(out), packetType}
		}
	}(ch, conn)

	connData := <-ch

	return C.CString(connData.string)
}

// Convert a data slice into a struct that can be marshalled into JSON
func makeStruct(dataType uint8, data []string) interface{} {
	var jsonData interface{}

	switch dataType {
	case IDCode:
		jsonData = bccnstrx.MakeIDCode(data)
	case Transaction:
		jsonData = bccnstrx.MakeTransaction(data)
	case Block:
		jsonData = bccnstrx.MakeBlock(data)
	case Node:
		jsonData = bccnstrx.MakeNode(data)
	case NodeList:
		jsonData = bccnstrx.MakeNodeList(data)
	case Receipt:
		jsonData = bccnstrx.MakeReceipt(data)
	case UserQuery:
		jsonData = bccnstrx.MakeUserQuery(data)
	case SyncRequest:
		jsonData = bccnstrx.MakeSyncRequest(data)
	case PendingTrxn:
		jsonData = bccnstrx.MakePendingTrxn(data)
	case RemovalRequest:
		jsonData = bccnstrx.MakeRemovalRequest(data)
	}

	return jsonData
}

// Compress a file using gzip
//
//export gzipCompress
func gzipCompress(filename C.cchar_t) C.cchar_t {
	goFilename := C.GoString(filename) // Convert from a C string to a Go string

	// Open the file
	file, err := os.Open(goFilename)
	netutils.Check(err, 154)

	// Read the contents of the file
	reader := bufio.NewReader(file)
	contents, err := ioutil.ReadAll(reader)
	netutils.Check(err, 159)

	// Create the compressed file (.gz)
	comp, err := os.Create(goFilename + ".gz")
	netutils.Check(err, 163)

	// Make a new writer
	gzwriter := gzip.NewWriter(comp)
	defer gzwriter.Close()

	// Set the header fields
	gzwriter.Name = goFilename
	gzwriter.Comment = ""
	gzwriter.ModTime = time.Now()

	// Write the compressed data to the file
	_, err = gzwriter.Write(contents)
	netutils.Check(err, 75)

	return C.CString(comp.Name())
}

// Decompress a gzip-compressed file
//
//export gzipDecompress
func gzipDecompress(filename C.cchar_t) C.cchar_t {
	goFilename := C.GoString(filename) // Convert from a C string to a Go string

	// Open the file for reading and writing
	input, err := os.OpenFile(goFilename, os.O_RDONLY, 0)
	netutils.Check(err, 87)

	defer input.Close()

	// Read the file as a byte slice
	b, err := ioutil.ReadFile(input.Name())
	netutils.Check(err, 93)

	// Create a byte reader and use it to make a gzip reader
	breader := bytes.NewReader(b)
	gzreader, err := gzip.NewReader(breader)

	netutils.Check(err, 99)
	defer gzreader.Close()

	// Create a destination file
	output, err := os.Create(strings.SplitAfterN(goFilename, ".gz", 1)[0])
	netutils.Check(err, 104)

	// Copy the decompressed data from the gzip reader to the destination file
	if _, err = io.Copy(output, gzreader); err != nil {
		netutils.Check(err, 108)
	}

	os.Remove(goFilename) // Delete the compressed data

	return C.CString(output.Name())
}

// Check if a port is open on a certain host
//
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

// Get the user's public IP address by making a call to http://ip-api.com/json/.
//
//export getPublicIP
func getPublicIP() C.cchar_t {
	resp, err := http.Get("http://ip-api.com/json/") // make a GET request
	body, _ := ioutil.ReadAll(resp.Body)             // Get the response as JSON

	// Convert the JSON string to a map
	responseMap := make(map[string]string)
	json.Unmarshal(body, &responseMap)

	if err != nil || responseMap["status"] == "fail" {
		panic(errors.New("could not get user's public IP address: " + responseMap["message"]))
	}

	defer resp.Body.Close()
	return C.CString(responseMap["query"])
}

// Get the user's local IP address
//
//export getLocalIP
func getLocalIP() C.cchar_t {
	ifaces, err := net.Interfaces()

	if err != nil {
		return C.CString("")
	}

	for _, iface := range ifaces {
		// Avoid iterfaces that are down or are loopback interfaces
		if (iface.Flags&net.FlagUp == 0) || (iface.Flags&net.FlagLoopback != 0) {
			continue
		}

		addrs, err := iface.Addrs()

		if err != nil {
			return C.CString("")
		}

		for _, addr := range addrs {
			var ip net.IP

			switch v := addr.(type) {
			case *net.IPNet:
				ip = v.IP
			case *net.IPAddr:
				ip = v.IP
			}

			if ip == nil || ip.IsLoopback() {
				continue
			}

			ip = ip.To4()
			if ip == nil {
				continue // not an ipv4 address
			}

			return C.CString(ip.String())
		}
	}

	return C.CString("")
}

//export openUPnPPort
func openUPnPPort(serviceID, protocol C.cchar_t, port uint16, host C.cchar_t) {
	var (
		goServiceID = C.GoString(serviceID)
		goProtocol  = C.GoString(protocol)
		goHost      = C.GoString(host)
	)

	netutils.OpenPort(goServiceID, goProtocol, port, goHost)
}

//export getServiceIDs
func getServiceIDs() **C.char {
	ch := make(chan []string)
	go func(ch chan<- []string) {
		ch <- netutils.GetServiceIDs()
	}(ch)

	serviceIDs := <-ch

	ret := C.malloc(C.size_t(len(serviceIDs)) * C.size_t(unsafe.Sizeof(uintptr(0))))

	// convert to usable format so we are able to fill it with data
	pRet := (*[1<<30 - 1]*C.char)(ret)

	for i, item := range serviceIDs {
		pRet[i] = C.CString(item)
	}

	return (**C.char)(ret)
}

func main() {}
