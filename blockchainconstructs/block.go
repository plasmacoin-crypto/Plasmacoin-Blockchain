//
// FILENAME: block.go | Plasmacoin Cryptocurrency
// DESCRIPTION: Express a block
// CREATED: 2022-01-15 @ 9:25 PM
// COPYRIGHT: Copyright (c) 2021 by Ryan Smith <rysmith2113@gmail.com>
//

package blockchainconstructs

import "strconv"

type Block struct {
	PacketType   int           `json:"type"`
	Index        int           `json:"index"`
	Difficulty   int64         `json:"difficulty"`
	Nonce        int           `json:"nonce"`
	Hash         string        `json:"hash"`
	PrevHash     string        `json:"prevhash"`
	MinerAddr    string        `json:"miner"`
	CreationTime string        `json:"created"`
	MineTime     string        `json:"mined"`
	IsGenesis    bool          `json:"genesis"`
	Transactions []Transaction `json:"transactions"`
}

func MakeBlock(data []string) *Block {
	//
	// About the data slice
	//
	// When this function receives the data, all data points will be strings and
	// are guaranteed be in the following order:
	//
	// 1.  The packet type (as an integer)					(data[0])
	// 2.  The index of the block  							(data[1])
	// 3.  The difficulty for the block 					(data[2])
	// 4.  The correct nonce 								(data[3])
	// 5.  The block's Merkle Root hash 					(data[4])
	// 6.  The previous block's hash 						(data[5])
	// 7.  The block miner 									(data[6])
	// 8.  The time the block was created 					(data[7])
	// 9.  The time the block was mined 					(data[8])
	// 10. Whether or not the block is the genesis block 	(data[9])
	// 11. A list of transactions on the block				(data[10])
	//
	// The transaction data comes in sets of 12. This means that data[10] - data[21] are
	// all part of the same transaction.
	//
	// For more information on what makes up a transaction, see `MakeTransaction` in
	// `transaction.go`.
	//

	const (
		trxnLen  = 12
		minIndex = 10
	)
	maxIndex := len(data)

	// Convert some stringified numeric values back to numeric values
	packetType, _ := strconv.ParseInt(data[0], 10, 32)
	index, _ := strconv.ParseInt(data[1], 10, 32)
	difficulty, _ := strconv.ParseInt(data[2], 10, 64)
	nonce, _ := strconv.ParseInt(data[3], 10, 32)
	isGenesis, _ := strconv.ParseBool(data[9])

	trxnCount := (maxIndex - minIndex) / trxnLen // Find the number of transactions in the block
	transactions := make([]Transaction, 0, trxnCount)

	for i := minIndex; i < maxIndex; i += trxnLen {
		// Get the current indices of transaction data. Using these in a slice selects
		// All the elements in the interval [min, max).
		min, max := i, i+trxnLen

		transactions = append(transactions, *MakeTransaction(data[min:max]))
	}

	return &Block{
		PacketType:   int(packetType),
		Index:        int(index),
		Difficulty:   int64(difficulty),
		Nonce:        int(nonce),
		Hash:         data[4],
		PrevHash:     data[5],
		MinerAddr:    data[6],
		CreationTime: data[7],
		MineTime:     data[8],
		IsGenesis:    isGenesis,
		Transactions: transactions,
	}
}
