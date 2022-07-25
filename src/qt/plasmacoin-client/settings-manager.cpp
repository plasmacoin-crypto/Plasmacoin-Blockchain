//
// FILENAME: settings-manager.cpp | Plasmacoin Cryptocurrency
// DESCRIPTION: The source file for settings-manager.hpp
// CREATED: 2022-07-8 @ 2:42 AM
// COPYRIGHT: Copyright (c) 2022 by Ryan Smith <rysmith2113@gmail.com>
//

#include "settings-manager.h"

SettingsManager::SettingsManager(
	QSettings* settings, QTextBrowser* rsaKeyPath, QComboBox* territorySelector, QComboBox* timeZoneSelector,
	QComboBox* nodeTypeSelector, QComboBox* methodSelector, QCheckBox* autoDetect, QCheckBox* enableNotifs,
	QCheckBox* pendingTrxnNotifs, QCheckBox* receiptNotifs, QCheckBox* miningNotifs, QCheckBox* syncNotifs
):
	m_Settings(settings),
	m_RSAKeyPath(rsaKeyPath),
	m_TerritorySelector(territorySelector),
	m_TimeZoneSelector(timeZoneSelector),
	m_NodeTypeSelector(nodeTypeSelector),
	m_MethodSelector(methodSelector),
	m_AutoDetect(autoDetect),
	m_EnableNotifs(enableNotifs),
	m_PendingTrxnNotifs(pendingTrxnNotifs),
	m_ReceiptNotifs(receiptNotifs),
	m_MiningNotifs(miningNotifs),
	m_SyncNotifs(syncNotifs)
{}

SettingsManager::~SettingsManager() {
	delete m_Settings;
	delete m_RSAKeyPath;
	delete m_TerritorySelector;
	delete m_TimeZoneSelector;
	delete m_NodeTypeSelector;
	delete m_MethodSelector;
	delete m_AutoDetect;
	delete m_EnableNotifs;
	delete m_PendingTrxnNotifs;
	delete m_ReceiptNotifs;
	delete m_MiningNotifs;
	delete m_SyncNotifs;
}

void SettingsManager::PopulateComboBoxes() {
	// Fill the territory selector with territory names. This can be done
	// by iterating from 0 to 261 and converting each integer to
	// support::Territory. The territory name as a string is then added
	// to the combo box.
	//
	// If the user has used the app before and they chose to auto-detect locale
	// information, the time zone list will only show relavant time zones for their
	// territory.
	//

	std::vector<support::Territory> territories;

	const int FIRST_TERRITORY = QLocale::AnyCountry;
	const int LAST_TERRITORY  = QLocale::Zimbabwe;

	// Fill the territory list
	for (int i = FIRST_TERRITORY; i <= LAST_TERRITORY; i++) {
		support::Territory territory = static_cast<support::Territory>(i);
		m_TerritorySelector->addItem(QLocale::countryToString(territory), territory);
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
		m_TimeZoneSelector->setCurrentIndex(thisTzIndex);
	}
	else {
		// Fill the time zone selector from the system's list of known IANA time zones
		auto timeZoneIDs = QTimeZone::availableTimeZoneIds();
		for (const auto& tzid: timeZoneIDs) {
			m_TimeZoneSelector->addItem(QString(tzid), tzid);
		}

		// Set UTC as the default time zone
		QByteArray utc = QTimeZone::availableTimeZoneIds(support::Territory::AnyCountry)[0];
		int utcIndex = timeZoneIDs.indexOf(utc);
		m_TimeZoneSelector->setCurrentIndex(utcIndex);
	}
}

void SettingsManager::SaveSettings() {
	m_Settings->setValue("account/rsaKeyPath", m_RSAKeyPath->toPlainText());

	m_Settings->setValue("locale/territory", static_cast<support::Territory>(m_TerritorySelector->currentIndex()));
	m_Settings->setValue("locale/timezone", m_TimeZoneSelector->currentData());
	m_Settings->setValue("locale/autoDetect", m_AutoDetect->isChecked());

	m_Settings->setValue("node/nodeType", m_NodeTypeSelector->currentIndex());
	m_Settings->setValue("node/miningMethod", m_MethodSelector->currentIndex());

	m_Settings->setValue("notifications/checkedData", GetNotificationSettings());
	m_Settings->setValue("notifications/enabled", m_EnableNotifs->isChecked());
	m_Settings->setValue("notifications/pendingTrxns", m_PendingTrxnNotifs->isChecked());
	m_Settings->setValue("notifications/receipts", m_ReceiptNotifs->isChecked());
	m_Settings->setValue("notifications/mining", m_MiningNotifs->isChecked());
	m_Settings->setValue("notifications/syncResults", m_SyncNotifs->isChecked());
}

void SettingsManager::LoadSettings() {
	m_Settings->beginGroup("account");

	settings::rsaKeyPath = m_Settings->value("rsaKeyPath", QString::fromStdString(rsafs::RSA_KEY_PATH)).toString().toStdString();

	if (settings::rsaKeyPath != rsafs::RSA_KEY_PATH) {
		m_RSAKeyPath->setPlainText(QString::fromStdString(settings::rsaKeyPath));
	}

	m_Settings->endGroup();

	m_Settings->beginGroup("locale");
	settings::territory = static_cast<support::Territory>(m_Settings->value("territory", support::Territory::AnyCountry).toInt());
	settings::timezone = m_Settings->value("timezone", QTimeZone::utc().id()).toByteArray();
	settings::autoDetect = m_Settings->value("autoDetect", false).toBool();

	// Display any previously checked boxes as checked
	if (settings::autoDetect) {
		m_AutoDetect->setChecked(true);
	}

	// Load the user's territory and time zone in the combo boxes
	auto timezones = QTimeZone::availableTimeZoneIds();
	m_TerritorySelector->setCurrentIndex(static_cast<int>(settings::territory));
	m_TimeZoneSelector->setCurrentIndex(timezones.indexOf(settings::timezone));

	m_Settings->endGroup();

	m_Settings->beginGroup("node");
	settings::nodeType = static_cast<enums::NodeType>(m_Settings->value("nodeType", static_cast<int>(enums::NodeType::LIGHT)).toInt());
	settings::miningMethod = static_cast<enums::MiningMethod>(m_Settings->value("miningMethod", static_cast<int>(enums::MiningMethod::CPU)).toInt());
	m_Settings->endGroup();

	m_Settings->beginGroup("notifications");
	settings::notificationSettings.m_CheckedBoxes = m_Settings->value("checkedData", 0).toInt();
	settings::notificationSettings.m_NotificationsEnabled = static_cast<Qt::CheckState>(m_Settings->value("enabled", false).toInt());
	settings::notificationSettings.m_PendingTrxns = m_Settings->value("pendingTrxns", false).toBool();
	settings::notificationSettings.m_Receipts = m_Settings->value("receipts", false).toBool();
	settings::notificationSettings.m_MiningResults = m_Settings->value("mining", false).toBool();
	settings::notificationSettings.m_SyncResults = m_Settings->value("syncResults", false).toBool();

	std::cout << "Enabled: " << settings::notificationSettings.m_NotificationsEnabled << std::endl;
	std::cout << "Settings field: " << (uint)settings::notificationSettings.m_CheckedBoxes << std::endl;

	if (settings::notificationSettings.m_NotificationsEnabled) {
		//
		// Determine if the box is checked or partially checked based on the data saved
		// about the user's settings:
		//		* If the user has no boxes checked, disable everything
		//		* If the user has all the boxes checked, or just the "enable" box checked, enable everything
		//		* Otherwise, mark the box as partially checked
		//

		if (settings::notificationSettings.m_CheckedBoxes == settings::NotificationSettings::NONE_CHECKED) {
			std::cout << "None" << std::endl;
			m_EnableNotifs->setCheckState(Qt::CheckState::Unchecked);
		}
		else if (
			settings::notificationSettings.m_CheckedBoxes == settings::NotificationSettings::ALL_CHECKED ||
			settings::notificationSettings.m_CheckedBoxes == settings::NotificationSettings::CHILDREN_CHECKED
		) {
			std::cout << "All" << std::endl;
			m_EnableNotifs->setCheckState(Qt::CheckState::Checked);
		}
		else {
			std::cout << "Partial" << std::endl;
			m_EnableNotifs->setCheckState(Qt::CheckState::PartiallyChecked);
		}
	}
	else {
		m_EnableNotifs->setCheckState(Qt::CheckState::Unchecked);
	}
	m_Settings->endGroup();
}

// Return a number representing what notification settings are checked
uint8_t SettingsManager::GetNotificationSettings() const {
	uint8_t result = 0;

	// States larger than zero represent Qt::PartiallyChecked and Qt::Checked
	if (static_cast<int>(m_EnableNotifs->checkState()) > 0) {
		result |= static_cast<uint8_t>(NotificationSettings::Notifications::ENABLED);
	}

	if (m_PendingTrxnNotifs->isChecked()) {
		result |= static_cast<uint8_t>(NotificationSettings::Notifications::PENDING_TRXNS);
	}

	if (m_ReceiptNotifs->isChecked()) {
		result |= static_cast<uint8_t>(NotificationSettings::Notifications::RECEIPTS);
	}

	if (m_MiningNotifs->isChecked()) {
		result |= static_cast<uint8_t>(NotificationSettings::Notifications::MINING);
	}

	if (m_SyncNotifs->isChecked()) {
		result |= static_cast<uint8_t>(NotificationSettings::Notifications::SYNC);
	}

	return result;
}

// Detect the user's territory and time zone from the system settings
void SettingsManager::DetectLocale() {
	m_TerritorySelector->setCurrentIndex(static_cast<int>(SYSTEM_TERRITORY));
	auto timezones = QTimeZone::availableTimeZoneIds();
	m_TimeZoneSelector->setCurrentIndex(timezones.indexOf(SYSTEM_TIME_ZONE));
}