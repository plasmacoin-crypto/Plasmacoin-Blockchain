//
// FILENAME: settings-manager.cpp | Plasmacoin Cryptocurrency
// DESCRIPTION: The source file for settings-manager.hpp
// CREATED: 2022-07-8 @ 2:42 AM
// COPYRIGHT: Copyright (c) 2022 by Ryan Smith <rysmith2113@gmail.com>
//

#include "settings-manager.h"

SettingsManager::SettingsManager(
	QSettings* settings, QTextBrowser* rsaKeyPath, QComboBox* territorySelector, QComboBox* timeZoneSelector,
	QComboBox* nodeTypeSelector, QComboBox* methodSelector, QCheckBox* alwaysDetect
):
	m_Settings(settings),
	m_RSAKeyPath(rsaKeyPath),
	m_TerritorySelector(territorySelector),
	m_TimeZoneSelector(timeZoneSelector),
	m_NodeTypeSelector(nodeTypeSelector),
	m_MethodSelector(methodSelector),
	m_AlwaysDetect(alwaysDetect)
{
	PopulateComboBoxes();
}

SettingsManager::~SettingsManager() {
	delete m_Settings;
}

void SettingsManager::SaveSettings() {
	m_Settings->setValue("account/rsaKeyPath", m_RSAKeyPath->toPlainText());

	m_Settings->setValue("locale/territory", static_cast<QLocale::Territory>(m_TerritorySelector->currentIndex()));
	m_Settings->setValue("locale/timezone", m_TimeZoneSelector->currentData());
	m_Settings->setValue("locale/autoDetect", m_AlwaysDetect->isChecked());

	m_Settings->setValue("node/nodeType", m_NodeTypeSelector->currentIndex());
	m_Settings->setValue("node/miningMethod", m_MethodSelector->currentIndex());
}

void SettingsManager::LoadSettings() {
	m_Settings->beginGroup("account");
	settings::rsaKeyPath = m_Settings->value("rsaKeyPath", QString::fromStdString(rsafs::RSA_KEY_PATH)).toString().toStdString();
	m_Settings->endGroup();

	m_Settings->beginGroup("locale");
	settings::territory = static_cast<QLocale::Territory>(m_Settings->value("territory", QLocale::Territory::AnyTerritory).toInt());
	settings::timezone = m_Settings->value("timezone", QTimeZone::utc().id()).toByteArray();
	settings::autoDetect = m_Settings->value("autoDetect", false).toBool();
	m_Settings->endGroup();

	m_Settings->beginGroup("node");
	settings::nodeType = static_cast<enums::NodeType>(m_Settings->value("nodeType", static_cast<int>(enums::NodeType::LIGHT)).toInt());
	settings::miningMethod = static_cast<enums::MiningMethod>(m_Settings->value("miningMethod", static_cast<int>(enums::MiningMethod::CPU)).toInt());
	m_Settings->endGroup();
}

void SettingsManager::PopulateComboBoxes() {
	// Fill the territory selector with territory names. This can be done
	// by iterating from 0 to 261 and converting each integer to
	// QLocale::Territory. The territory name as a string is then added
	// to the combo box.
	//
	// If the user has used the app before and they chose to auto-detect locale
	// information, the time zone list will only show relavant time zones for their
	// territory.
	//

	std::vector<QLocale::Territory> territories;
	const QByteArray SYSTEM_TIME_ZONE = QTimeZone::systemTimeZoneId();
	const QLocale::Territory SYSTEM_TERRITORY = QTimeZone(SYSTEM_TIME_ZONE).territory();

	const int FIRST_TERRITORY = QLocale::AnyTerritory;
	const int LAST_TERRITORY  = QLocale::Zimbabwe;

	// Fill the territory list
	for (int i = FIRST_TERRITORY; i <= LAST_TERRITORY; i++) {
		QLocale::Territory territory = static_cast<QLocale::Territory>(i);
		m_TerritorySelector->addItem(QLocale::territoryToString(territory), territory);
		territories.push_back(territory);
	}

	if (m_Settings->value("locale/autoDetect").toBool()) {
		m_TerritorySelector->setCurrentIndex(static_cast<int>(SYSTEM_TERRITORY));

		// Fill the time zone selector with relevant time zones for the current territory
		auto timezones = QTimeZone::availableTimeZoneIds(SYSTEM_TERRITORY);
		for (const auto& tz: timezones) {
			m_TimeZoneSelector->addItem(QString(tz), tz);
		}

		// If the system's detected timezone is in the list of known time zones for
		// the detected territory, set it as the current time zone.
		int thisTzIndex = timezones.indexOf(SYSTEM_TIME_ZONE);
		if (thisTzIndex != -1) {
			m_TimeZoneSelector->setCurrentIndex(thisTzIndex);
		}
	}
	else {
		// Fill the time zone selector from the system's list of known IANA time zones
		auto timeZoneIDs = QTimeZone::availableTimeZoneIds();
		for (const auto& tzid: timeZoneIDs) {
			m_TimeZoneSelector->addItem(QString(tzid), tzid);
		}

		// Set UTC as the default time zone
		QByteArray utc = QTimeZone::availableTimeZoneIds(QLocale::Territory::AnyTerritory)[0];
		int utcIndex = timeZoneIDs.indexOf(utc);
		m_TimeZoneSelector->setCurrentIndex(utcIndex);
	}
}