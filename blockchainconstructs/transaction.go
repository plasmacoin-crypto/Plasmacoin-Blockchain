//
// FILENAME: transaction.go | Plasmacoin Cryptocurrency
// DESCRIPTION: Express Plasmacoin transaction data natively in Go
// CREATED: 2021-12-24 @ 10:08 PM
// COPYRIGHT: Copyright (c) 2021 by Ryan Smith <rysmith2113@gmail.com>
//

package blockchainconstructs

import (
	"strconv"
)

type Transaction struct {
	PacketType    int       `json:"type"`
	SenderAddr    string    `json:"senderAddr"`
	RecipientAddr string    `json:"recipientAddr"`
	CreationTime  int64     `json:"created"`
	SigningTime   int64     `json:"signed"`
	Amount        float64   `json:"amount"`
	Fee           float64   `json:"fee"`
	Content       string    `json:"content"`
	Signature     Signature `json:"sigfield"`
	Hash          string    `json:"hash"`
}

func MakeTransaction(data []string) *Transaction {
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
	// 5.  The time the transaction was signed 	(data[4])
	// 6.  Transaction amount 					(data[5])
	// 7.  Transaction fee 						(data[6])
	// 8.  The transaction content 				(data[7])
	// 9.  The transaction signature 			(data[8])
	// 10. The sender's public key 				(data[9])
	// 11. The length of the signature 			(data[10])
	// 12. The SHA-256 hash of the transaction 	(data[11])
	//

	// Convert some stringified numeric values back to numeric values
	packetType, _ := strconv.ParseInt(data[0], 10, 32)
	creationTime, _ := strconv.ParseInt(data[3], 10, 64)
	signingTime, _ := strconv.ParseInt(data[4], 10, 64)
	amount, _ := strconv.ParseFloat(data[5], 64)
	fee, _ := strconv.ParseFloat(data[6], 64)
	siglen, _ := strconv.ParseInt(data[10], 10, 32)

	// Construct the signature field
	signature := Signature{
		Signature: data[8],
		PublicKey: data[9],
		Length:    int(siglen),
	}

	// Construct the transaction
	return &Transaction{
		PacketType:    int(packetType),
		SenderAddr:    data[1],
		RecipientAddr: data[2],
		CreationTime:  creationTime,
		SigningTime:   signingTime,
		Amount:        float64(amount),
		Fee:           float64(fee),
		Content:       data[7],
		Signature:     signature,
		Hash:          data[11],
	}
}
