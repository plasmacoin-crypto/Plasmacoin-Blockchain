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

// Check for errors
func check(err error, line int) {
	if err != nil {
		var _ error = fmt.Errorf(err.Error(), " on line ", strconv.Itoa(line))
	}
}

// Read the data from a connection
func HandleConnection(conn net.Conn) []byte {
	data, _ := bufio.NewReader(conn).ReadBytes(0)

	var transaction bccnstrx.Transaction

	// Convert the packet to JSON data
	err := json.Unmarshal(data, &transaction)
	check(err, 35)

	// Marshal the data
	jsonBytes, _ := json.Marshal(transaction)
	return jsonBytes
}
