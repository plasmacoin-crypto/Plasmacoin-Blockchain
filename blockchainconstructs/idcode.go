//
// FILENAME: idcode.go | Plasmacoin Cryptocurrency
// DESCRIPTION: Express the code that is returned from a mining process
// CREATED: 2022-01-04 @ 8:29 PM
// COPYRIGHT: Copyright (c) 2021 by Ryan Smith <rysmith2113@gmail.com>
//

package blockchainconstructs

import "strconv"

type IDCode struct {
	PacketType int `json:"packetType"`
	Code       int `json:"code"`
}

func MakeIDCode(data []string) *IDCode {
	//
	// About the data slice
	//
	// When this function receives the data, all data points will be strings and
	// are guaranteed be in the following order:
	//
	// 1.  The packet type (as an integer)					(data[0])
	// 2.  The ID code			  							(data[1])
	//

	packetType, _ := strconv.ParseInt(data[0], 10, 32)
	code, _ := strconv.ParseInt(data[1], 10, 32)

	return &IDCode{
		PacketType: int(packetType),
		Code:       int(code),
	}
}
