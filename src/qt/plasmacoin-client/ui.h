//
// FILENAME: ui.h | Plasmacoin Cryptocurrency
// DESCRIPTION: Include the correct UI header for each operating system
// CREATED: 2021-05-21 @ 3:06 PM
// COPYRIGHT: Copyright (c) 2022 by Ryan Smith <rysmith2113@gmail.com>
//

#ifdef __linux__
	#include "ui_linux.h"
#elif defined(__APPLE__)
	#include "ui_macos.h"
#elif defined(_WIN32)
	// Include Windows UI header
#endif
