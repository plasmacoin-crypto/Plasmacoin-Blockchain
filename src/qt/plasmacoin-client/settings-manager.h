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

class SettingsManager : public QMainWindow, public Ui_MainWindow {
public:
	SettingsManager(
		QSettings* settings, QTextBrowser* rsaKeyPath, QComboBox* territorySelector, QComboBox* timeZoneSelector,
		QComboBox* nodeTypeSelector, QComboBox* methodSelector, QCheckBox* alwaysDetect
	);
	~SettingsManager();

	void SaveSettings();
	void LoadSettings();

private:
	void PopulateComboBoxes();

	QSettings* m_Settings;
	QTextBrowser* m_RSAKeyPath;
	QComboBox *m_TerritorySelector, *m_TimeZoneSelector, *m_NodeTypeSelector, *m_MethodSelector;
	QCheckBox* m_AlwaysDetect;
};

#endif // SETTINGS_MANAGER_H