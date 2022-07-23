//
// FILENAME: notification.cpp | Plasmacoin Cryptocurrency
// DESCRIPTION: Display destop notifications
// CREATED: 2021-07-20 @ 12:14 PM
// COPYRIGHT: Copyright (c) 2022 by Ryan Smith <rysmith2113@gmail.com>
//

#include "notification.hpp"

NotifyNotification* notification::create(const char* title, const char* body, const char* iconPath) {
	notify_init(title);
	return notify_notification_new(title, body, iconPath);
}

notification::NotificationData notification::show(NotifyNotification* notification) {
	NotificationData data;

	data.m_Result = notify_notification_show(notification, nullptr);
	return data;
}