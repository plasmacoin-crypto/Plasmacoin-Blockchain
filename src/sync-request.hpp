//
// FILENAME: sync-request.hpp | Plasmacoin Cryptocurrency
// DESCRIPTION: Request to sync data with another node
// CREATED: 2022-04-10 @ 10:03 PM
// COPYRIGHT: Copyright (c) 2022 by Ryan Smith <rysmith2113@gmail.com>
//

#ifndef SYNC_REQUEST_HPP
#define SYNC_REQUEST_HPP

struct SyncRequest {
	int m_SyncType;
	string m_Host;
};

#endif // SYNC_REQUEST_HPP