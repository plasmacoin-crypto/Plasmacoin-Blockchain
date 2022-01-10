//
// FILENAME: nodelist.go | Plasmacoin Cryptocurrency
// DESCRIPTION: A list of IP addresses sent to nodes when they connect to a DNS Seeder
// CREATED: 2021-01-09 @ 8:06 PM
// COPYRIGHT: Copyright (c) 2021 by Ryan Smith <rysmith2113@gmail.com>
//

package blockchainconstructs

import (
	"strconv"
)

type NodeList struct {
	PacketType int      `json:"type"`
	Nodes      []string `json:"nodes"`
}

func MakeNodeList(data []string) *NodeList {
	//
	// About the data slice
	//
	// When this function receives the data, all data points will be strings and
	// are guaranteed be in the following order:
	//
	// 1. The packet type (as an integer)	(data[0])
	// 2. A list of IP addresses 			(data[1])
	//

	// Convert some stringified numeric values back to numeric values
	packetType, _ := strconv.ParseInt(data[0], 10, 32)

	numNodes := len(data) - 1
	nodes := make([]string, 0, numNodes)

	for i := 1; i <= numNodes; i++ {
		nodes = append(nodes, data[i])
	}

	// Construct the node list
	return &NodeList{
		PacketType: int(packetType),
		Nodes:      nodes,
	}
}
