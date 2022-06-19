//
// FILENAME: nodedata.go | Plasmacoin Cryptocurrency
// DESCRIPTION: Store data about a node
// CREATED: 2021-12-26 @ 6:14 PM
// COPYRIGHT: Copyright (c) 2021 by Ryan Smith <rysmith2113@gmail.com>
//

package blockchainconstructs

import "strconv"

type NodeData struct {
	PacketType int    `json:"type"`
	SenderIP   string `json:"senderIP"`
	IP         string `json:"ip"`
	Address    string `json:"address"`
	NodeType   int    `json:"nodetype"`
	Register   bool   `json:"register"`
}

func MakeNode(data []string) *NodeData {
	//
	// About the data slice
	//
	// When this function receives the data, all data points will be strings and
	// are guaranteed be in the following order:
	//
	// 1. The packet type (as an integer)					 (data[0])
	// 2. The sender's IP address 							 (data[1])
	// 2. The node's IP Address 							 (data[2])
	// 3. The node's Plasmacoin address 					 (data[3])
	// 3. The type of node 									 (data[4])
	// 4. If the node should be added to the lookup database (data[5])
	//

	// Convert some stringified numeric values back to numeric values
	packetType, _ := strconv.ParseInt(data[0], 10, 32)
	nodeType, _ := strconv.ParseInt(data[4], 10, 32)
	register, _ := strconv.ParseBool(data[5])

	// Construct the node data
	return &NodeData{
		PacketType: int(packetType),
		SenderIP:   data[1],
		IP:         data[2],
		Address:    data[3],
		NodeType:   int(nodeType),
		Register:   register,
	}
}
