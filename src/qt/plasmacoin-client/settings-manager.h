//
// FILENAME: settings-manager.h | Plasmacoin Cryptocurrency
// DESCRIPTION: The app's settings page
// CREATED: 2022-07-8 @ 2:42 AM
// COPYRIGHT: Copyright (c) 2022 by Ryan Smith <rysmith2113@gmail.com>
//

#ifndef SETTINGS_MANAGER_H
#define SETTINGS_MANAGER_H

#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <condition_variable>

#include <QMainWindow>
#include <QString>
#include <QSettings>
#include <QLocale>
#include <QTimeZone>
#include <QCheckBox>
#include <QDebug>

#include "ui.h"
#include "rsa-fs.hpp"
#include "settings.h"
#include "support.h"
#include "upnp.hpp"

using settings::NotificationSettings;

class SettingsManager : public QMainWindow, public Ui_MainWindow {
public:
	SettingsManager(Ui_MainWindow* window, QSettings* settings);
	~SettingsManager();

	void PopulateComboBoxes();

	void SaveSettings();
	void LoadSettings();

	uint8_t GetNotificationSettings() const;
	void DetectLocale();

	mutable std::mutex m_SettingsMutex;
	std::condition_variable m_CondVar;

private:
	void SetNotifications(uint8_t settings);

	const QByteArray SYSTEM_TIME_ZONE = QTimeZone::systemTimeZoneId();
	const support::Territory SYSTEM_TERRITORY = QTimeZone(SYSTEM_TIME_ZONE).country();

	Ui_MainWindow* m_Window;
	QSettings* m_Settings;
};

#endif // SETTINGS_MANAGER_H