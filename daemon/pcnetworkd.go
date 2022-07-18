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
	"strconv"
	"strings"
	"time"

	bccnstrx "github.com/plasmacoin-crypto/Plasmacoin-Blockchain/blockchainconstructs"
	"github.com/plasmacoin-crypto/Plasmacoin-Blockchain/handler"
	"github.com/plasmacoin-crypto/Plasmacoin-Blockchain/netlisten"
	"github.com/plasmacoin-crypto/Plasmacoin-Blockchain/netutils"

	"golang.org/x/net/ipv4"
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
//export dial
func dial(protocol, host, port C.cchar_t, dataType uint8, data []C.cchar_t) {
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

	conn, err := net.DialTimeout(goProtocol, net.JoinHostPort(goHost, goPort), time.Second * 5)

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
		ch <- struct {
			string
			uint8
		}{string(out), packetType}
	}(ch, conn)

	connData := <-ch

	return C.CString(connData.string)
}

//export joinGroup
func joinGroup(iface, host C.cchar_t, port uint16) {
	var (
		goIface = C.GoString(iface)
		goHost  = C.GoString(host)
	)

	connectMulticast(goIface, goHost, port)
}

//export sendMulticast
func sendMulticast(host C.cchar_t, port uint16, dataType uint8, data []C.cchar_t) {
	var (
		goHost = C.GoString(host)
		goData = make([]string, len(data))
	)

	for i, str := range data {
		goData[i] = C.GoString(str)
	}

	dialMulticast(goHost, port, dataType, goData)
}

// Attempt to join a multicast group
//export listenMulticast
func listenMulticast(iface, host C.cchar_t, port uint16) {
	var (
		goIface = C.GoString(iface)
		goHost  = C.GoString(host)
	)

	ipv4conn := connectMulticast(goIface, goHost, port)
	packet := make([]byte, 1500)

	type connData struct {
		NumBytes int
		Sender   *net.UDPAddr
		Err      error
	}

	var data connData

	//go func(ch chan<- connData, ipv4conn *net.UDPConn, packet []byte) {}(ch, ipv4conn, packet)

	fmt.Println("Here1")

	if n, sender, err := ipv4conn.ReadFromUDP(packet); err == nil && n > 0 {
		data = connData{n, sender, err}
	}

	if data.Err == nil && data.NumBytes > 0 {
		log.Printf("Recieved %d bytes from %s\n", data.NumBytes, data.Sender.String())
		fmt.Println(string(packet))
	}
}

// Attempt to join a multicast group
func connectMulticast(iface string, host string, port uint16) *net.UDPConn {
	en0, err := net.InterfaceByName(iface)
	if err != nil {
		log.Fatalf("Couldn't find interface %s", iface)
	}

	group := net.ParseIP(host)
	udpaddr := &net.UDPAddr{IP: group, Port: int(port)}

	ipv4conn, err := net.ListenMulticastUDP("udp", nil, udpaddr)
	if err != nil {
		log.Fatalf("Failed to bind to udp port: %d", udpaddr.Port)
	}

	packetConn := ipv4.NewPacketConn(ipv4conn)

	if err := packetConn.JoinGroup(en0, &net.UDPAddr{IP: group}); err != nil {
		log.Fatalf("Couldn't join multicast group %s", group.String())
	}

	return ipv4conn
}

// Send a multicast packet to a multicast group
func dialMulticast(host string, port uint16, dataType uint8, data []string) {
	// Get the recipient's multicast address
	group := net.ParseIP(host)
	udpaddr := &net.UDPAddr{IP: group, Port: int(port)}

	jsonData := makeStruct(dataType, data) // Get the structure

	// Marshall the struct to JSON
	jsonBytes, _ := json.Marshal(jsonData)
	fmt.Println(string(jsonBytes))

	// Send the data
	recipient, _ := net.ResolveUDPAddr("udp", udpaddr.String())
	udpconn, _ := net.DialUDP("udp", nil, recipient)
	udpconn.Write(jsonBytes)
}

func getInterface() *net.Interface {
	var ifaceNames []string

	// Get the user's network interfaces
	if interfaces, err := net.Interfaces(); err == nil {
		for _, inter := range interfaces {
			if strings.Contains(inter.Flags.String(), "multicast") {
				ifaceNames = append(ifaceNames, inter.Name)
			}
		}
	} else {
		fmt.Println(err)
	}

	ifaceName := ifaceNames[0]

	// Get the corresponding interface from the name
	ifaceFromName, err := net.InterfaceByName(ifaceName)
	if err != nil {
		panic(fmt.Sprintf("Couldn't find %s", ifaceName))
	}

	return ifaceFromName
}

//export getStrIface
func getStrIface() C.cchar_t {
	return C.CString(getInterface().Name)
}

// Convert a data slice into a struct that can be marshalled into JSON
func makeStruct(dataType uint8, data []string) interface{} {
	var jsonData interface{}

	switch dataType {
	case IDCode:
		id, _ := strconv.ParseInt(data[1], 10, 32)
		jsonData = &struct {
			Code int `json:"code"`
		}{Code: int(id)}
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

// Get the user's local IP address
//export getLocalIP
func getLocalIP() C.cchar_t {
	ifaces, err := net.Interfaces()

	if err != nil {
		return C.CString("")
	}

	for _, iface := range ifaces {
		// Avoid iterfaces that are down or are loopback interfaces
		if (iface.Flags & net.FlagUp == 0) || (iface.Flags & net.FlagLoopback != 0) {
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

func main() {}
