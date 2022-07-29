//
// FILENAME: settings.h | Plasmacoin Cryptocurrency
// DESCRIPTION: An easier way to access the application settings
// CREATED: 2022-08-8 @ 10:43 PM
// COPYRIGHT: Copyright (c) 2022 by Ryan Smith <rysmith2113@gmail.com>
//

#ifndef SETTINGS_H
#define SETTINGS_H

#include <string>

#include <QByteArray>
#include <QLocale>

#include "enums.h"
#include "support.h"

namespace settings {
	// Store data about the user's notification settings
	struct NotificationSettings {
		// Represent the notifications in a bit field
		enum struct Notifications: uint8_t {
			ENABLED 	  =	1 << 0,
			PENDING_TRXNS = 1 << 1,
			RECEIPTS	  = 1 << 2,
			MINING 		  = 1 << 3,
			SYNC 		  = 1 << 4
		};

		const static uint8_t ALL_CHECKED =  static_cast<uint8_t>(Notifications::ENABLED)  | static_cast<uint8_t>(Notifications::PENDING_TRXNS) |
										    static_cast<uint8_t>(Notifications::RECEIPTS) | static_cast<uint8_t>(Notifications::MINING) |
										    static_cast<uint8_t>(Notifications::SYNC);
		const static uint8_t NONE_CHECKED = 0;
		const static uint8_t CHILDREN_CHECKED = static_cast<uint8_t>(Notifications::PENDING_TRXNS) | static_cast<uint8_t>(Notifications::RECEIPTS) |
												static_cast<uint8_t>(Notifications::MINING) 	   | static_cast<uint8_t>(Notifications::SYNC);
		const static uint8_t CHILDREN_UNCHEKED = CHILDREN_CHECKED ^ ALL_CHECKED;

		uint8_t m_CheckedBoxes;

		// Store the state of the check boxes
		Qt::CheckState m_NotificationsEnabled;
		bool m_PendingTrxns;
		bool m_Receipts;
		bool m_MiningResults;
		bool m_SyncResults;
	};

	static std::string rsaKeyPath;
	static support::Territory territory;
	static QByteArray timezone;
	static bool autoDetect;
	static enums::NodeType nodeType;
	static enums::MiningMethod miningMethod;
	static NotificationSettings notificationSettings;
}

#endif // SETTINGS_H