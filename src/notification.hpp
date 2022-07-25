//
// FILENAME: notification.hpp | Plasmacoin Cryptocurrency
// DESCRIPTION: Display destop notifications
// CREATED: 2021-07-20 @ 12:14 PM
// COPYRIGHT: Copyright (c) 2022 by Ryan Smith <rysmith2113@gmail.com>
//

#ifndef NOTIFICATION_H
#define NOTIFICATION_H

#ifdef _WIN32
	// Windows notifications
#elif defined(__APPLE__)
	#include <QSystemTrayIcon>
	#include <QIcon>
	#include <QString>

	namespace notification {
		void show(QSystemTrayIcon* sysTrayIcon, const QString& title, const QString& body, const QIcon& icon);
	}
#elif defined(__linux__)
	#define QT_NO_KEYWORDS
	#undef signals

	#include <stdexcept>
	#include <string>

	#include <libnotify/notify.h>

	namespace notification {
		struct NotificationData {
			gboolean m_Result;
			GError*  m_Error;
		};

		void show(NotifyNotification* notification);
	}

	#undef QT_NO_KEYWORDS
	#define signals Q_SIGNALS
#endif

#endif //NOTIFICATION_H