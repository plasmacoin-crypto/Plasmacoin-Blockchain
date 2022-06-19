//
// FILENAME: packet-types.h | Plasmacoin Cryptocurrency
// DESCRIPTION: Types of packets the network can handle
// CREATED: 2022-01-14 @ 8:38 PM
// COPYRIGHT: Copyright (c) 2021 by Ryan Smith <rysmith2113@gmail.com>
//

#ifndef PACKET_TYPES_H
#define PACKET_TYPES_H

namespace go {
	enum class PacketTypes: uint8_t {
		ID_CODE,
		TRANSACTION,
		BLOCK,
		NODE,
		NODE_LIST,
		RECEIPT,
		USER_QUERY,
		SYNC_REQUEST,
		PENDING_TRXN
	};

	enum class IDCodes: uint8_t {
		START_SYNC,
		END_SYNC,
		ERROR
	};
}

#endif // PACKET_TYPES_H