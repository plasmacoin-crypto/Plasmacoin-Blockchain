//
// FILENAME: notification.cpp | Plasmacoin Cryptocurrency
// DESCRIPTION: Display destop notifications
// CREATED: 2021-07-20 @ 12:14 PM
// COPYRIGHT: Copyright (c) 2022 by Ryan Smith <rysmith2113@gmail.com>
//

#include "notification.hpp"

#ifdef _WIN32
	// Windows definitions
#elif defined(__APPLE__)
	void notification::show(QSystemTrayIcon* sysTrayIcon, const QString& title, const QString& body, const QIcon& icon) {
		sysTrayIcon->showMessage(title, body, icon);
	}
#elif defined(__linux__)
	void notification::show(const char* title, const char* body, const char* iconPath) {
		notify_init(title);

		NotificationData data;
		NotifyNotification* notification = notify_notification_new(title, body, iconPath);

		data.m_Result = notify_notification_show(notification, data.m_Error);

		if (data.m_Error != nullptr) {
			throw std::runtime_error("Error: " + std::string(data.m_Error.msg));
		}
	}
#endif