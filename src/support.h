//
// FILENAME: support.h | Plasmacoin Cryptocurrency
// DESCRIPTION: Help keep code backwards compatible with Qt 5
// CREATED: 2022-08-11 @ 1:36 PM
// COPYRIGHT: Copyright (c) 2022 by Ryan Smith <rysmith2113@gmail.com>
//

#ifndef SUPPORT_H
#define SUPPORT_H

#include <QLocale>

#define QT_6 6

namespace support {
	#if QT_VERSION_MAJOR == QT_6
		typedef QLocale::Territory Territory; // Use the same identifier for Qt5 and Qt6
	#else
		typedef QLocale::Country Territory; // Backwards compatability for Qt6's QLocale::Territory
	#endif
}

#endif // SUPPORT_H