//
// FILENAME: netlisten.go | Plasmacoin Cryptocurrency
// DESCRIPTION: Listen for TCP/UDP connections
// CREATED: 2021-08-28 @ 5:36 PM
// COPYRIGHT: Copyright (c) 2021 by Ryan Smith <rysmith2113@gmail.com>
//

package handler

import (
	"fmt"

	"github.com/plasmacoin-crypto/Plasmacoin-Blockchain/netdial"
	"github.com/plasmacoin-crypto/Plasmacoin-Blockchain/netutils"
)

const (
	ping int = iota
	finished
	transaction
	block
	sync
)

func Parse(signal int) {
	fmt.Println("Parsing signal", signal)

	switch signal {
	case 48:
		fmt.Println("Pinging...", netutils.Ping("localhost"))
		netdial.Dial("tcp", "192.168.1.3", "8080", 69)
	case finished:
		break
	}
}
