//
// FILENAME: signature.go | Plasmacoin Cryptocurrency
// DESCRIPTION: Express a digital signature natively in Go
// CREATED: 2021-02-13 @ 12:47 PM
// COPYRIGHT: Copyright (c) 2022 by Ryan Smith <rysmith2113@gmail.com>
//

package blockchainconstructs

type Signature struct {
	Signature string `json:"signature"`
	PublicKey string `json:"publicKey"`
	Length    int    `json:"length"`
}