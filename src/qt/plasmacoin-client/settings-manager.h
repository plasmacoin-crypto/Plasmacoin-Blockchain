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

class SettingsManager : public QMainWindow, public Ui_MainWindow {
public:
	SettingsManager(
		QSettings* settings, QTextBrowser* rsaKeyPath, QComboBox* territorySelector, QComboBox* timeZoneSelector,
		QComboBox* nodeTypeSelector, QComboBox* methodSelector, QCheckBox* autoDetect
	);
	~SettingsManager();

	void PopulateComboBoxes();

	void SaveSettings();
	void LoadSettings();

	void DetectLocale();

private:
	const QByteArray SYSTEM_TIME_ZONE = QTimeZone::systemTimeZoneId();
	const support::Territory SYSTEM_TERRITORY = QTimeZone(SYSTEM_TIME_ZONE).country();

	QSettings* m_Settings;
	QTextBrowser* m_RSAKeyPath;
	QComboBox *m_TerritorySelector, *m_TimeZoneSelector, *m_NodeTypeSelector, *m_MethodSelector;
	QCheckBox* m_AutoDetect;
};

#endif // SETTINGS_MANAGER_H