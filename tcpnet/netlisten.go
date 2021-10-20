//
// FILENAME: netlisten.go | Plasmacoin Cryptocurrency
// DESCRIPTION: Listen for TCP/UDP connections
// CREATED: 2021-09-08 @ 9:19 PM
// COPYRIGHT: Copyright (c) 2021 by Ryan Smith <rysmith2113@gmail.com>
//

package tcpnet

import (
	"fmt"
	"net"
	"strconv"

	"github.com/plasmacoin-crypto/Plasmacoin-Blockchain/handler"
)

type Dialer struct{}

// Check for errors
func check(err error, line int) {
	if err != nil {
		var _ error = fmt.Errorf(err.Error(), " on line ", strconv.Itoa(line))
	}
}

// Listen for connections on a specified host and port
func Listen(protocol, host, port string) (net.Listener, error) {
	listener, err := net.Listen(protocol, net.JoinHostPort(host, port))

	if err != nil {
		return nil, err
	}

	return listener, nil
}

// Listen for and accept TCP/UDP connections
func (d *Dialer) Receive(protocol, host, port string) {
	fmt.Println(host)

	// Listen for a connection
	listener, err := Listen(protocol, host, port)
	check(err, 64)

	fmt.Println(listener == nil)

	defer listener.Close()

	for {
		// Wait for a connection.
		conn, err := listener.Accept()
		check(err, 73)

		// Handle the connection
		go handler.HandleConnection(conn)
	}
}
