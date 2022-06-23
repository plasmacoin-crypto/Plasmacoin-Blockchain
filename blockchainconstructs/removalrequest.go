//
// FILENAME: removalrequest.go | Plasmacoin Cryptocurrency
// DESCRIPTION: Express a removal request natively in Go
// CREATED: 2022-06-19 @ 7:26 PM
// COPYRIGHT: Copyright (c) 2022 by Ryan Smith <rysmith2113@gmail.com>
//

package blockchainconstructs

import (
	"strconv"
)

type RemovalRequest struct {
	PacketType int    `json:"type"`
	SenderIP   string `json:"senderIP"`
}

func MakeRemovalRequest(data []string) *RemovalRequest {
	//
	// About the data slice
	//
	// When this function receives the data, all data points will be strings and
	// are guaranteed be in the following order:
	//
	// 1.  The packet type (as an integer)		(data[0])
	// 2.  The sender's IP address 				(data[1])
	//

	packetType, _ := strconv.ParseInt(data[0], 10, 32)

	return &RemovalRequest{
		PacketType: int(packetType),
		SenderIP:   data[1],
	}
}
