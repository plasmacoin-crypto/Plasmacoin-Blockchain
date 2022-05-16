//
// FILENAME: bcdata.go | Plasmacoin Cryptocurrency
// DESCRIPTION: Any blockchain data a user wants to send to another user
// CREATED: 2022-04-10 @ 12:51 PM
// COPYRIGHT: Copyright (c) 2022 by Ryan Smith <rysmith2113@gmail.com>
//

package blockchainconstructs

import (
	"strconv"
)

type BlockchainData struct {
	PacketType int             `json:"type"`
	DataType   int             `json:"datatype"`
	Data       [](interface{}) `json:"data"`
}

func MakeBlockchainData(data []string) *BlockchainData {
	//
	// About the data slice
	//
	// When this function receives the data, all data points will be strings and
	// are guaranteed be in the following order:
	//
	// 1.  The packet type (as an integer)		(data[0])
	// 2.  The type of data to send 			(data[1])
	// 3.  The data to send						(data[2])
	//

	// Convert some stringified numeric values back to numeric values
	packetType, _ := strconv.ParseInt(data[0], 10, 32)
	dataType, _ := strconv.ParseInt(data[1], 10, 32)

	const (
		transaction uint8 = 1
		block       uint8 = 2
		minIndex          = 2
		trxnLen           = 12
		blockLen          = 10 + trxnLen
	)
	maxIndex := len(data)

	var length int

	// Determine the number of fields in the data structure(s) being transmitted
	if uint8(dataType) == transaction {
		length = trxnLen
	} else if uint8(dataType) == block {
		length = blockLen
	}

	dataLen := (maxIndex - minIndex) / length // Find the number of data structures being returned
	returnData := make([](interface{}), 0, dataLen)

	// Construct data structures from the data slice
	for i := minIndex; i < maxIndex; i += length {
		// Get the current indices of the data. Using these in a slice selects
		// All the elements in the interval [min, max).
		min, max := i, i+length

		if uint8(packetType) == transaction {
			returnData = append(returnData, MakeTransaction(data[min:max]))
		} else if uint8(packetType) == block {
			returnData = append(returnData, MakeBlock(data[min:max]))
		}
	}

	return &BlockchainData{
		PacketType: int(packetType),
		DataType:   int(dataType),
		Data:       returnData,
	}
}
