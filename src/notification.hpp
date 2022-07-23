//
// FILENAME: notification.hpp | Plasmacoin Cryptocurrency
// DESCRIPTION: Display destop notifications
// CREATED: 2021-07-20 @ 12:14 PM
// COPYRIGHT: Copyright (c) 2022 by Ryan Smith <rysmith2113@gmail.com>
//

#ifndef NOTIFICATION_H
#define NOTIFICATION_H

#define QT_NO_KEYWORDS
#undef signals

#include <libnotify/notify.h>

namespace notification {
	struct NotificationData {
		gboolean m_Result;
		GError*  m_Error;
	};

	NotifyNotification* create(const char* title, const char* body, const char* iconPath);
	NotificationData show(NotifyNotification* notification);
}

#undef QT_NO_KEYWORDS
#define signals Q_SIGNALS

#endif //NOTIFICATION_H