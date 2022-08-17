//
// FILENAME: nodedata.go | Plasmacoin Cryptocurrency
// DESCRIPTION: Store data about a node
// CREATED: 2021-12-26 @ 6:14 PM
// COPYRIGHT: Copyright (c) 2021 by Ryan Smith <rysmith2113@gmail.com>
//

package blockchainconstructs

import (
	"strconv"
)

type NodeData struct {
	PacketType int    `json:"type"`
	SenderIP   string `json:"senderIP"`
	SenderPort int    `json:"senderPort"`
	IP         string `json:"ip"`
	Port       int    `json:"port"`
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
	// 3. The sender's port 							 	 (data[2])
	// 4. The node's IP Address 							 (data[3])
	// 5. The node's port 								 	 (data[4])
	// 6. The node's Plasmacoin address 					 (data[5])
	// 7. The type of node 									 (data[6])
	// 8. If the node should be added to the lookup database (data[7])
	//

	// Convert some stringified numeric values back to numeric values
	packetType, _ := strconv.ParseInt(data[0], 10, 32)
	senderPort, _ := strconv.ParseInt(data[2], 10, 16)
	port, _ := strconv.ParseInt(data[4], 10, 16)
	nodeType, err := strconv.ParseInt(data[6], 10, 32)
	register, _ := strconv.ParseBool(data[7])

	// In case the node type is a text string (rather than an integer as a string),
	// assign nodeType the correct value.
	if err != nil {
		switch data[6] {
		case "light":
			nodeType = 0
		case "full":
			nodeType = 1
		case "mining":
			nodeType = 2
		case "addrlookup":
			nodeType = 3
		}
	}

	// Construct the node data
	return &NodeData{
		PacketType: int(packetType),
		SenderIP:   data[1],
		SenderPort: int(senderPort),
		IP:         data[3],
		Port:       int(port),
		Address:    data[5],
		NodeType:   int(nodeType),
		Register:   register,
	}
}
