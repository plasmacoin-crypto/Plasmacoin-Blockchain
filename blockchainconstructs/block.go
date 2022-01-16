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
	Nonce        int           `json:"nonce"`
	Hash         string        `json:"hash"`
	PrevHash     string        `json:"prevhash"`
	Timestamp    string        `json:"timestamp"`
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
	// 1. The packet type (as an integer)					(data[0])
	// 2. The index of the block  							(data[1])
	// 3. The correct nonce 								(data[2])
	// 4. The block's Merkle Root hash 						(data[3])
	// 5. The previous block's hash 						(data[4])
	// 6. The timestamp 									(data[5])
	// 7. Whether or not the block is the genesis block 	(data[6])
	// 8. A list of transactions on the block				(data[7])
	//
	// The transaction data comes in sets of 10. This means that data[7] - data[16] are
	// all part of the same transaction.
	//
	// For more information on what makes up a transaction, see `MakeTransaction` in
	// `transaction.go`.
	//

	// Convert some stringified numeric values back to numeric values
	packetType, _ := strconv.ParseInt(data[0], 10, 32)
	index, _ := strconv.ParseInt(data[1], 10, 32)
	nonce, _ := strconv.ParseInt(data[2], 10, 32)
	isGenesis, _ := strconv.ParseBool(data[6])

	trxnCount := (len(data) - 7) / 10 // Find the number of transactions in the block
	transactions := make([]Transaction, 0, trxnCount)

	for i := 7; i < len(data); i += 10 {
		// Get the current indices of transaction data. Using these in a slice selects
		// 10 elements in the interval [min, max).
		min, max := i, i + 10

		transactions = append(transactions, *MakeTransaction(data[min:max]))
	}

	return &Block{
		PacketType:   int(packetType),
		Index:        int(index),
		Nonce:        int(nonce),
		Hash:         data[3],
		PrevHash:     data[4],
		Timestamp:    data[5],
		IsGenesis:    isGenesis,
		Transactions: transactions,
	}
}
