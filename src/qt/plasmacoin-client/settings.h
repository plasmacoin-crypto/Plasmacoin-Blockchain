//
// FILENAME: settings.h | Plasmacoin Cryptocurrency
// DESCRIPTION: An easier way to access the application settings
// CREATED: 2022-08-8 @ 10:43 PM
// COPYRIGHT: Copyright (c) 2022 by Ryan Smith <rysmith2113@gmail.com>
//

#ifndef SETTINGS_H
#define SETTINGS_H

#include <string>

#include <QByteArray>
#include <QLocale>

#include "enums.h"

namespace settings {
	static std::string rsaKeyPath;
	static QLocale::Territory territory;
	static QByteArray timezone;
	static bool autoDetect;
	static enums::NodeType nodeType;
	static enums::MiningMethod miningMethod;
}

#endif // SETTINGS_H