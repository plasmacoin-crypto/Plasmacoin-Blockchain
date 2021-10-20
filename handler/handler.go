//
// FILENAME: netlisten.go | Plasmacoin Cryptocurrency
// DESCRIPTION: Listen for TCP/UDP connections
// CREATED: 2021-10-17 @ 7:42 PM
// COPYRIGHT: Copyright (c) 2021 by Ryan Smith <rysmith2113@gmail.com>
//

package handler

import (
	"fmt"
	"io/ioutil"
	"net"
	"strconv"

	"github.com/plasmacoin-crypto/Plasmacoin-Blockchain/netutils"
)

// Check for errors
func check(err error, line int) {
	if err != nil {
		var _ error = fmt.Errorf(err.Error(), " on line ", strconv.Itoa(line))
	}
}

// Read the data from a connection
func HandleConnection(conn net.Conn) {
	buf, err := ioutil.ReadAll(conn)
	check(err, 37)

	fmt.Println("Received")
	fmt.Println(buf)

	var d netutils.DialInstance
	d.Parse(int(buf[0]))
}
