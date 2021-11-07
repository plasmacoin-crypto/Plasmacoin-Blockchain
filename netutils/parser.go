//
// FILENAME: netlisten.go | Plasmacoin Cryptocurrency
// DESCRIPTION: Listen for TCP/UDP connections
// CREATED: 2021-08-28 @ 5:36 PM
// COPYRIGHT: Copyright (c) 2021 by Ryan Smith <rysmith2113@gmail.com>
//

package netutils

import (
	"fmt"
)

const (
	ping int = iota
	finished
	transaction
	block
)

type dialer interface {
	Dial(protocol, host, port string, message byte)
	parse(signal int)
}

type DialInstance struct {
	Dialer dialer
}

func (d DialInstance) Parse(signal int) {
	switch signal {
	case ping:
		fmt.Println(Ping("localhost"))
	case finished:
		fmt.Println("Detected finished mining")
	}
}
