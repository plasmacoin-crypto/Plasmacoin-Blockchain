//
// FILENAME: netdial.go | Plasmacoin Cryptocurrency
// DESCRIPTION: Make TCP/UDP connections
// CREATED: 2021-08-28 @ 5:36 PM
// COPYRIGHT: Copyright (c) 2021 by Ryan Smith <rysmith2113@gmail.com>
//

package tcpnet

import (
	"fmt"
	"log"
	"net"
)

// Attempt to send a message to a specified host and port
func Dial(protocol, host, port string, message byte) {
	fmt.Println("Dialing...")

	conn, err := net.Dial(protocol, net.JoinHostPort(host, port))

	if err != nil {
		log.Fatal(err)
	}

	_, err = conn.Write([]byte{message})
	check(err, 29)

	conn.Close()
}
