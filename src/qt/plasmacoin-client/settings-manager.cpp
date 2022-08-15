//
// FILENAME: settings-manager.cpp | Plasmacoin Cryptocurrency
// DESCRIPTION: The source file for settings-manager.hpp
// CREATED: 2022-07-8 @ 2:42 AM
// COPYRIGHT: Copyright (c) 2022 by Ryan Smith <rysmith2113@gmail.com>
//

#include "settings-manager.h"

SettingsManager::SettingsManager(Ui_MainWindow* window, QSettings* settings):
	m_Window(window),
	m_Settings(settings)
{}

SettingsManager::~SettingsManager() {
	delete m_Settings;
}

void SettingsManager::PopulateComboBoxes() {
	// Fill the UPnP device list with service IDs. Because this process tends to
	// be computationally expensive, perform this operation on a separate thread.
	std::thread getSIDs([=] {
		for (const string& serviceID: upnp::getServiceIDs()) {
			std::cout << serviceID << std::endl;
			this->m_Window->upnpDevSelector->addItem(QString::fromStdString(serviceID));
		}

		this->m_Window->upnpDevSelector->setCurrentIndex(0); // Auto-select the first service ID
		settings::serviceIDIndex = this->m_Window->upnpDevSelector->currentIndex();

		std::cout << "In thread: " << settings::upnpServiceID << std::endl;
		this->m_CondVar.notify_all();
	});
	getSIDs.detach();

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
	const int LAST_TERRITORY = QLocale::Zimbabwe;

	// Fill the territory list
	for (int i = FIRST_TERRITORY; i <= LAST_TERRITORY; i++) {
		support::Territory territory = static_cast<support::Territory>(i);
		m_Window->territorySelector->addItem(QLocale::countryToString(territory), territory);
		territories.push_back(territory);
	}

	// Fill the time zone selector from the system's list of known IANA time zones
	auto timeZoneIDs = QTimeZone::availableTimeZoneIds();
	for (const auto& tzid: timeZoneIDs) {
		m_Window->timeZoneSelector->addItem(QString(tzid), tzid);
	}

	if (m_Settings->value("locale/autoDetect").toBool()) {
		m_Window->territorySelector->setCurrentIndex(static_cast<int>(SYSTEM_TERRITORY));

		// Fill the time zone selector with relevant time zones for the current territory
		// auto timezones = QTimeZone::availableTimeZoneIds(SYSTEM_TERRITORY);
		// for (const auto& tz: timezones) {
		// 	m_Window->timeZoneSelector->addItem(QString(tz), tz);
		// }

		// If the system's detected timezone is in the list of known time zones for
		// the detected territory, set it as the current time zone.
		int thisTzIndex = timeZoneIDs.indexOf(SYSTEM_TIME_ZONE);
		m_Window->timeZoneSelector->setCurrentIndex(thisTzIndex);
	}
	else {
		// Set UTC as the default time zone
		QByteArray utc = QTimeZone::availableTimeZoneIds(support::Territory::AnyCountry)[0];
		int utcIndex = timeZoneIDs.indexOf(utc);
		m_Window->timeZoneSelector->setCurrentIndex(utcIndex);
	}
}

void SettingsManager::SaveSettings() {
	m_Settings->setValue("account/rsaKeyPath", m_Window->rsaKeyPath->toPlainText());

	m_Settings->setValue("network/portMappingProtocol", m_Window->portMapSelector->currentIndex());
	m_Settings->setValue("network/upnpServiceID", m_Window->upnpDevSelector->currentIndex());

	m_Settings->setValue("wallet/paddingType", m_Window->padTypeSelector->currentIndex());
	m_Settings->setValue("wallet/customPadAmount", m_Window->paddingSelector->value());
	m_Settings->setValue("wallet/walletView", m_Window->walletViewSelector->currentIndex());

	m_Settings->setValue("locale/territory", static_cast<support::Territory>(m_Window->territorySelector->currentIndex()));
	m_Settings->setValue("locale/timezone", m_Window->timeZoneSelector->currentData());
	m_Settings->setValue("locale/alwaysDetect", m_Window->alwaysDetect->isChecked());

	m_Settings->setValue("node/nodeType", m_Window->nodeTypeSelector->currentIndex());
	m_Settings->setValue("node/miningMethod", m_Window->methodSelector->currentIndex());

	m_Settings->setValue("notifications/checkedData", GetNotificationSettings());
	m_Settings->setValue("notifications/enabled", m_Window->enableNotifs->checkState());
	m_Settings->setValue("notifications/pendingTrxns", m_Window->pendingTrxnNotifs->isChecked());
	m_Settings->setValue("notifications/receipts", m_Window->receiptNotifs->isChecked());
	m_Settings->setValue("notifications/mining", m_Window->miningNotifs->isChecked());
	m_Settings->setValue("notifications/syncResults", m_Window->syncNotifs->isChecked());
}

void SettingsManager::LoadSettings() {
	m_Settings->beginGroup("account");

	settings::rsaKeyPath = m_Settings->value("rsaKeyPath", QString::fromStdString(rsafs::RSA_KEY_PATH)).toString().toStdString();

	if (settings::rsaKeyPath != rsafs::RSA_KEY_PATH) {
		m_Window->rsaKeyPath->setPlainText(QString::fromStdString(settings::rsaKeyPath));
	}

	m_Settings->endGroup();

	m_Settings->beginGroup("network");

	settings::portMappingProtocol = static_cast<enums::PortMappingProtocol>(m_Settings->value("portMappingProtocol", 0).toInt());
	settings::upnpServiceID = m_Settings->value("upnpServiceID", m_Window->upnpDevSelector->itemText(0)).toString().toStdString();

	switch (settings::portMappingProtocol) {
		case enums::PortMappingProtocol::UPNP:
			m_Window->portMapSelector->setCurrentIndex(1);
			m_Window->portMapSelector->setCurrentIndex(static_cast<int>(settings::portMappingProtocol));
			break;

		case enums::PortMappingProtocol::PORT_FORWARDING:
			m_Window->portMapSelector->setCurrentIndex(0);
			m_Window->portMapSelector->setCurrentIndex(static_cast<int>(settings::portMappingProtocol));
			break;
	}

	if (int index = m_Window->upnpDevSelector->findText(QString::fromStdString(settings::upnpServiceID)); index != -1) {
		m_Window->upnpDevSelector->setCurrentIndex(index);
		settings::upnpServiceID = m_Window->upnpDevSelector->currentText().toStdString();
	}

	m_Settings->endGroup();

	m_Settings->beginGroup("wallet");

	settings::paddingType = static_cast<enums::PaddingType>(m_Settings->value("paddingType", 0).toInt());
	settings::customPadAmount = m_Settings->value("customPadAmount", 0).toInt();
	settings::walletView = m_Settings->value("walletView", 0).toInt();

	m_Window->padTypeSelector->setCurrentIndex(static_cast<int>(settings::paddingType));
	m_Window->paddingSelector->setValue(settings::customPadAmount);
	m_Window->walletViewSelector->setCurrentIndex(settings::walletView);

	switch (settings::paddingType) {
		case enums::PaddingType::MAXIMUM:
			m_Window->padTypeSelector->setCurrentIndex(1);
			m_Window->padTypeSelector->setCurrentIndex(static_cast<int>(enums::PaddingType::MAXIMUM));
			break;

		case enums::PaddingType::NONE:
			m_Window->padTypeSelector->setCurrentIndex(0);
			m_Window->padTypeSelector->setCurrentIndex(static_cast<int>(enums::PaddingType::NONE));
			break;

		case enums::PaddingType::CUSTOM:
			m_Window->padTypeSelector->setCurrentIndex(1);
			m_Window->padTypeSelector->setCurrentIndex(static_cast<int>(enums::PaddingType::CUSTOM));
			break;
	}

	m_Settings->endGroup();

	m_Settings->beginGroup("locale");
	settings::territory = static_cast<support::Territory>(m_Settings->value("territory", support::Territory::AnyCountry).toInt());
	settings::timezone = m_Settings->value("timezone", QTimeZone::utc().id()).toByteArray();
	settings::alwaysDetect = m_Settings->value("alwaysDetect", false).toBool();

	// Display any previously checked boxes as checked
	if (settings::alwaysDetect) {
		m_Window->alwaysDetect->setChecked(true);
	}

	// Load the user's territory and time zone in the combo boxes
	auto timezones = QTimeZone::availableTimeZoneIds();
	m_Window->territorySelector->setCurrentIndex(static_cast<int>(settings::territory));
	m_Window->timeZoneSelector->setCurrentIndex(timezones.indexOf(settings::timezone));
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
			m_Window->enableNotifs->setCheckState(Qt::CheckState::Unchecked);
		}
		else if (
			settings::notificationSettings.m_CheckedBoxes == settings::NotificationSettings::ALL_CHECKED ||
			settings::notificationSettings.m_CheckedBoxes == settings::NotificationSettings::CHILDREN_CHECKED
		) {
			std::cout << "All" << std::endl;
			m_Window->enableNotifs->setCheckState(Qt::CheckState::Checked);
		}
		else {
			std::cout << "Partial" << std::endl;
			m_Window->enableNotifs->setCheckState(Qt::CheckState::PartiallyChecked);
			SetNotifications(settings::notificationSettings.m_CheckedBoxes);
		}
	}
	else {
		std::cout << "Disabled" << std::endl;

		m_Window->enableNotifs->setCheckState(Qt::CheckState::Checked);
		m_Window->enableNotifs->setCheckState(Qt::CheckState::Unchecked);
	}
	m_Settings->endGroup();
}

// Return a number representing what notification settings are checked
uint8_t SettingsManager::GetNotificationSettings() const {
	uint8_t result = 0;

	// States larger than zero represent Qt::PartiallyChecked and Qt::Checked
	if (static_cast<int>(m_Window->enableNotifs->checkState()) > 0) {
		result |= static_cast<uint8_t>(NotificationSettings::Notifications::ENABLED);
	}

	if (m_Window->pendingTrxnNotifs->isChecked()) {
		result |= static_cast<uint8_t>(NotificationSettings::Notifications::PENDING_TRXNS);
	}

	if (m_Window->receiptNotifs->isChecked()) {
		result |= static_cast<uint8_t>(NotificationSettings::Notifications::RECEIPTS);
	}

	if (m_Window->miningNotifs->isChecked()) {
		result |= static_cast<uint8_t>(NotificationSettings::Notifications::MINING);
	}

	if (m_Window->syncNotifs->isChecked()) {
		result |= static_cast<uint8_t>(NotificationSettings::Notifications::SYNC);
	}

	return result;
}

// Detect the user's territory and time zone from the system settings
void SettingsManager::DetectLocale() {
	m_Window->territorySelector->setCurrentIndex(static_cast<int>(SYSTEM_TERRITORY));
	auto timezones = QTimeZone::availableTimeZoneIds();

	qDebug() << timezones.indexOf(SYSTEM_TIME_ZONE);
	m_Window->timeZoneSelector->setCurrentIndex(timezones.indexOf(SYSTEM_TIME_ZONE));
	qDebug() << m_Window->timeZoneSelector->currentIndex();
}

void SettingsManager::SetNotifications(uint8_t settings) {
	if (settings & static_cast<uint8_t>(NotificationSettings::Notifications::PENDING_TRXNS)) {
		m_Window->pendingTrxnNotifs->setChecked(true);
	}

	if (settings & static_cast<uint8_t>(NotificationSettings::Notifications::RECEIPTS)) {
		m_Window->receiptNotifs->setChecked(true);
	}

	if (settings & static_cast<uint8_t>(NotificationSettings::Notifications::MINING)) {
		m_Window->miningNotifs->setChecked(true);
	}

	if (settings & static_cast<uint8_t>(NotificationSettings::Notifications::SYNC)) {
		m_Window->syncNotifs->setChecked(true);
	}
}