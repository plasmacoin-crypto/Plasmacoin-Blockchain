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
	// 1. Address of sender
	// 2. Address of recipient
	// 3. Transaction amount
	// 4. Transaction fee
	// 5. The transaction signature
	// 6. The sender's public key
	// 7. The length of the signature
	// 8. The SHA-256 hash of the transaction
	//

	// Convert some stringified numeric values back to numeric values
	amount, _ := strconv.ParseFloat(data[2], 32)
	fee, _ := strconv.ParseFloat(data[3], 32)
	siglen, _ := strconv.ParseInt(data[6], 10, 32)

	// Construct the signature field
	signature := Signature {
		Signature: data[4],
		PublicKey: []byte(data[5]),
		Length:    int(siglen),
	}

	// Construct the transaction
	return &Transaction {
		SenderAddr:    data[0],
		RecipientAddr: data[1],
		Amount:        float32(amount),
		Fee:           float32(fee),
		Content:       data[4],
		Signature:     signature,
		Hash:          data[7],
	}
}
