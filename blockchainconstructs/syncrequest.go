//
// FILENAME: syncqrequest.go | Plasmacoin Cryptocurrency
// DESCRIPTION: Request to sync data with another node
// CREATED: 2022-04-10 @ 11:59 AM
// COPYRIGHT: Copyright (c) 2022 by Ryan Smith <rysmith2113@gmail.com>
//

package blockchainconstructs

import "strconv"

type SyncRequest struct {
	PacketType int    `json:"type"`
	SyncType   int    `json:"synctype"`
	Host       string `json:"host"`
}

func MakeSyncRequest(data []string) *SyncRequest {
	//
	// About the data slice
	//
	// When this function receives the data, all data points will be strings and
	// are guaranteed be in the following order:
	//
	// 1.  The packet type (as an integer)		(data[0])
	// 2.  The type of data to sync 			(data[1])
	// 3.  The sender's IP address 				(data[2])
	//

	packetType, _ := strconv.ParseInt(data[0], 10, 32)
	syncType, _ := strconv.ParseInt(data[1], 10, 32)

	return &SyncRequest{
		PacketType: int(packetType),
		SyncType:   int(syncType),
		Host:       data[2],
	}
}
