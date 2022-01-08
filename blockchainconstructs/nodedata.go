//
// FILENAME: nodedata.go | Plasmacoin Cryptocurrency
// DESCRIPTION: Store data about a node
// CREATED: 2021-12-26 @ 6:14 PM
// COPYRIGHT: Copyright (c) 2021 by Ryan Smith <rysmith2113@gmail.com>
//

package blockchainconstructs

type NodeData struct {
	IP       string
	Address  string
	NodeType uint8
}
