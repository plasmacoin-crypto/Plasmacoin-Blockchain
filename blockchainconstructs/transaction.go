//
// FILENAME: transaction.go | Plasmacoin Cryptocurrency
// DESCRIPTION: Express Plasmacoin transaction data natively in Go
// CREATED: 2021-12-24 @ 10:08 PM
// COPYRIGHT: Copyright (c) 2021 by Ryan Smith <rysmith2113@gmail.com>
//

package blockchainconstructs

import "strconv"

type Signature struct {
	Signature string `json:"signature"`
	PublicKey []byte `json:"publicKey"`
	Length    int    `json:"length"`
}

type Transaction struct {
	PacketType    int       `json:"type"`
	SenderAddr    string    `json:"senderAddr"`
	RecipientAddr string    `json:"recipientAddr"`
	Amount        float32   `json:"amount"`
	Fee           float32   `json:"fee"`
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
	// 1. The packet type (as an integer)		(data[0])
	// 2. Address of sender 					(data[1])
	// 3. Address of recipient 					(data[2])
	// 4. Transaction amount 					(data[3])
	// 5. Transaction fee 						(data[4])
	// 6. The transaction content 				(data[5])
	// 7. The transaction signature 			(data[6])
	// 8. The sender's public key 				(data[7])
	// 9. The length of the signature 			(data[8])
	// 10. The SHA-256 hash of the transaction 	(data[9])
	//

	// Convert some stringified numeric values back to numeric values
	packetType, _ := strconv.ParseInt(data[0], 10, 32)
	amount, _ := strconv.ParseFloat(data[3], 32)
	fee, _ := strconv.ParseFloat(data[4], 32)
	siglen, _ := strconv.ParseInt(data[8], 10, 32)

	// Construct the signature field
	signature := Signature{
		Signature: data[6],
		PublicKey: []byte(data[7]),
		Length:    int(siglen),
	}

	// Construct the transaction
	return &Transaction{
		PacketType:    int(packetType),
		SenderAddr:    data[1],
		RecipientAddr: data[2],
		Amount:        float32(amount),
		Fee:           float32(fee),
		Content:       data[5],
		Signature:     signature,
		Hash:          data[9],
	}
}
