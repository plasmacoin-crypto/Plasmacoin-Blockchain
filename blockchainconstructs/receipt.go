//
// FILENAME: receipt.go | Plasmacoin Cryptocurrency
// DESCRIPTION: Express a transaction receipt natively in Go
// CREATED: 2021-02-13 @ 12:49 PM
// COPYRIGHT: Copyright (c) 2022 by Ryan Smith <rysmith2113@gmail.com>
//

package blockchainconstructs

import "strconv"

type Receipt struct {
	PacketType      int       `json:"type"`
	SenderAddr      string    `json:"senderAddr"`
	RecipientAddr   string    `json:"recipientAddr"`
	TransactionTime int64     `json:"trxnCreated"`
	SigningTime     int64     `json:"signed"`
	Amount          float64   `json:"amount"`
	Fee             float64   `json:"fee"`
	Signature       Signature `json:"sigfield"`
	Hash            string    `json:"hash"`
}

func MakeReceipt(data []string) *Receipt {
	//
	// About the data slice
	//
	// When this function receives the data, all data points will be strings and
	// are guaranteed be in the following order:
	//
	// 1.  The packet type (as an integer)		(data[0])
	// 2.  Address of sender 					(data[1])
	// 3.  Address of recipient 				(data[2])
	// 4.  The time the transaction was created (data[3])
	// 5.  The time the receipt was signed 		(data[4])
	// 6.  Transaction amount 					(data[5])
	// 7.  Transaction fee 						(data[6])
	// 8.  The receipt signature 				(data[7])
	// 9.  The sender's public key 				(data[8])
	// 10. The length of the signature 			(data[9])
	// 11. The SHA-256 hash of the transaction 	(data[10])
	//

	packetType, _ := strconv.ParseInt(data[0], 10, 32)
	transactionTime, _ := strconv.ParseInt(data[3], 10, 64)
	signingTime, _ := strconv.ParseInt(data[4], 10, 64)
	amount, _ := strconv.ParseFloat(data[5], 64)
	fee, _ := strconv.ParseFloat(data[6], 64)
	siglen, _ := strconv.ParseInt(data[9], 10, 32)

	// Construct the signature field
	signature := Signature{
		Signature: data[7],
		PublicKey: data[8],
		Length:    int(siglen),
	}

	return &Receipt{
		PacketType:      int(packetType),
		SenderAddr:      data[1],
		RecipientAddr:   data[2],
		TransactionTime: transactionTime,
		SigningTime:     signingTime,
		Amount:          float64(amount),
		Fee:             float64(fee),
		Signature:       signature,
		Hash:            data[10],
	}
}
