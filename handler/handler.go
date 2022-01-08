//
// FILENAME: handler.go | Plasmacoin Cryptocurrency
// DESCRIPTION: Handle TCP/UDP connections
// CREATED: 2021-10-17 @ 7:42 PM
// COPYRIGHT: Copyright (c) 2021 by Ryan Smith <rysmith2113@gmail.com>
//

package handler

import (
	"bufio"
	"encoding/json"
	"fmt"
	"net"
	"strconv"

	bccnstrx "github.com/plasmacoin-crypto/Plasmacoin-Blockchain/blockchainconstructs"
)

// Types of blockchain constructs
const (
	IDCode = uint8(iota)
	Transaction
	Block
)

// Check for errors
func check(err error, line int) {
	if err != nil {
		var _ error = fmt.Errorf(err.Error(), " on line ", strconv.Itoa(line))
	}
}

// Read the data from a connection
func HandleConnection(conn net.Conn) ([]byte, uint8) {
	data, _ := bufio.NewReader(conn).ReadBytes(0)

	var packet bccnstrx.PacketType

	// Isolate the packet type
	err := json.Unmarshal(data, &packet)
	check(err, 36)

	fullPacket := getStruct(data, packet.Type) // Convert the packet to the correct Go struct

	// Marshal the data
	jsonBytes, _ := json.Marshal(fullPacket)
	return jsonBytes, packet.Type
}

// Unmarshal a TCP packet (as JSON) into its corresponding Go struct
func getStruct(data []byte, packetType uint8) interface{} {
	switch packetType {
	case IDCode:
		var idCode bccnstrx.IDCode

		err := json.Unmarshal(data, &idCode)
		check(err, 68)

		return idCode
	case Transaction:
		var transaction bccnstrx.Transaction

		err := json.Unmarshal(data, &transaction)
		check(err, 75)

		return transaction
	default:
		break
	}

	return struct{}{}
}
