//
// FILENAME: packettype.go | Plasmacoin Cryptocurrency
// DESCRIPTION: Help identify packets recieved by the daemon
// CREATED: 2022-01-04 @ 8:43 PM
// COPYRIGHT: Copyright (c) 2021 by Ryan Smith <rysmith2113@gmail.com>
//

package blockchainconstructs

type PacketType struct {
	Type uint8 `json:"type"`
}