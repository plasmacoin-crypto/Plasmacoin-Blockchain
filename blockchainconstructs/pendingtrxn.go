//
// FILENAME: pendingtrxn.go | Plasmacoin Cryptocurrency
// DESCRIPTION: A way to send basic transaction data for pending transactions
// CREATED: 2022-06-16 @ 2:11 PM
// COPYRIGHT: Copyright (c) 2022 by Ryan Smith <rysmith2113@gmail.com>
//

package blockchainconstructs

import (
	"strconv"
)

type PendingTrxn struct {
	PacketType int     `json:"type"`
	Timestamp  int64   `json:"timestamp"`
	Hash       string  `json:"hash"`
	Amount     float64 `json:"amount"`
}

func MakePendingTrxn(data []string) *PendingTrxn {
	//
	// About the data slice
	//
	// When this function receives the data, all data points will be strings and
	// are guaranteed be in the following order:
	//
	// 1.  The packet type (as an integer)		(data[0])
	// 2.  The transaction's timestamp			(data[1])
	// 3.  The SHA-256 hash of the transaction 	(data[2])
	// 4.  Transaction amount 					(data[3])
	//

	packetType, _ := strconv.ParseInt(data[0], 10, 32)
	timestamp, _ := strconv.ParseInt(data[1], 10, 64)
	amount, _ := strconv.ParseFloat(data[3], 64)

	return &PendingTrxn{
		PacketType: int(packetType),
		Timestamp:  timestamp,
		Hash:       data[2],
		Amount:     amount,
	}
}
