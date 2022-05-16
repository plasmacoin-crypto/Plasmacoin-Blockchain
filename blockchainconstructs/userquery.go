//
// FILENAME: userquery.go | Plasmacoin Cryptocurrency
// DESCRIPTION: Return a list of relavant Plasamcoin users
// CREATED: 2022-04-09 @ 9:51 PM
// COPYRIGHT: Copyright (c) 2022 by Ryan Smith <rysmith2113@gmail.com>
//

package blockchainconstructs

import "strconv"

type UserQuery struct {
	PacketType int    `json:"type"`
	IP         string `json:"ip"`
	NodeType   string `json:"nodetype"`
}

func MakeUserQuery(data []string) *UserQuery {
	//
	// About the data slice
	//
	// When this function receives the data, all data points will be strings and
	// are guaranteed be in the following order:
	//
	// 1.  The packet type (as an integer)		(data[0])
	// 2.  IP Address of sender 				(data[1])
	// 3.  The type of nodes to return 			(data[2])
	//

	// Convert some stringified numeric values back to numeric values
	packetType, _ := strconv.ParseInt(data[0], 10, 32)

	return &UserQuery{
		PacketType: int(packetType),
		IP:         data[1],
		NodeType:   data[2],
	}
}
