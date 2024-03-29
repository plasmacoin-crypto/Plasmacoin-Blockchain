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
	Node
	NodeList
	Receipt
	UserQuery
	SyncRequest
	PendingTrxn
	RemovalRequest
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

	fmt.Println(data, packet.Type)

	fullPacket := getStruct(data, packet.Type) // Convert the packet to the correct Go struct

	if fullPacket == nil {
		return nil, 0
	}

	// Marshal the data
	jsonBytes, _ := json.Marshal(fullPacket)
	return jsonBytes, packet.Type
}

// Unmarshal a TCP packet (as JSON) into its corresponding Go struct
func getStruct(data []byte, packetType uint8) interface{} {
	if len(data) == 0 {
		return nil
	}

	switch packetType {
	case IDCode:
		var idCode bccnstrx.IDCode

		err := json.Unmarshal(data, &idCode)
		check(err, 60)

		return idCode
	case Transaction:
		var transaction bccnstrx.Transaction

		err := json.Unmarshal(data, &transaction)
		check(err, 67)

		return transaction
	case Block:
		var block bccnstrx.Block

		err := json.Unmarshal(data, &block)
		check(err, 76)

		return block
	case Node:
		var nodeData bccnstrx.NodeData

		err := json.Unmarshal(data, &nodeData)
		check(err, 74)

		return nodeData
	case NodeList:
		var nodeList bccnstrx.NodeList

		err := json.Unmarshal(data, &nodeList)
		check(err, 81)

		fmt.Println(nodeList)
		return nodeList
	case Receipt:
		var receipt bccnstrx.Receipt

		err := json.Unmarshal(data, &receipt)
		check(err, 86)

		return receipt
	case UserQuery:
		var userQuery bccnstrx.UserQuery

		err := json.Unmarshal(data, &userQuery)
		check(err, 89)

		return userQuery
	case SyncRequest:
		var syncRequest bccnstrx.SyncRequest

		err := json.Unmarshal(data, &syncRequest)
		check(err, 89)

		return syncRequest
	case PendingTrxn:
		var pendingTrxn bccnstrx.PendingTrxn

		err := json.Unmarshal(data, &pendingTrxn)
		check(err, 89)

		return pendingTrxn
	case RemovalRequest:
		var remRequest bccnstrx.RemovalRequest

		err := json.Unmarshal(data, &remRequest)
		check(err, 131)

		return remRequest
	default:
		break
	}

	return struct{}{}
}
