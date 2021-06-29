//
// FILENAME: mining-status.cpp | Plasmacoin Cryptocurrency
// DESCRIPTION: The source file for mining-status.h
// CREATED: 2021-04-02 @ 4:22 PM
// COPYRIGHT: Copyright (c) 2021 by Ryan Smith <rysmith2113@gmail.com>
//

#include "mining-status.h"

Status::Status(QTextBrowser* qtbrowser1, QTextBrowser* qtbrowser2, QTextBrowser* qtbrowser3, QTextBrowser* qtbrowser4):
	m_Heading(qtbrowser1),
	m_HashView(qtbrowser2),
	m_NonceView(qtbrowser3),
	m_ElapsedTime(qtbrowser4)
{
	// Main display
	m_Heading->setObjectName(QString::fromUtf8("heading"));
	m_Heading->setGeometry(QRect(380, 31, 391, 51));
}

// Render the mining status visuals on the screen
void Status::LoadVisuals() {
	// The hash of the mined block
	m_HashView->setObjectName(QString::fromUtf8("hashView"));
	m_HashView->setGeometry(QRect(380, 91, 391, 51));

	// A readout of the current nonce value
	m_NonceView->setObjectName(QString::fromUtf8("nonceView"));
	m_NonceView->setGeometry(QRect(380, 151, 191, 51));

	// A readout of the elapsed mining time
	m_ElapsedTime->setObjectName(QString::fromUtf8("elapsedTime"));
	m_ElapsedTime->setGeometry(QRect(580, 151, 191, 51));
}

// Modify the heading
void Status::SetHeading(string text) {
	m_Heading->setHtml(
		QString(
			string(
				"<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">"
				"<html>"
					"<head>"
						"<meta name=\"qrichtext\" content=\"1\" />"
						"<style type=\"text/css\">"
							"p, li {"
								"white-space: pre-wrap;"
							"}"
						"</style>"
					"</head>"
					"<body style=\"font-family:\'Noto Sans\'; font-size:10pt; font-weight:400; font-style:normal;\">"
						"<p align=\"center\" style=\"margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">"
							+ text +
						"</p>"
					"</body>"
				"</html>"
			).c_str()
		)
	);
}

// Set the hash
void Status::SetHash(string text) {
	m_HashView->setHtml(
		QString(
			string(
				"<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">"
				"<html>"
					"<head>"
						"<meta name=\"qrichtext\" content=\"1\" />"
						"<style type=\"text/css\">"
							"p, li {"
								"white-space: pre-wrap;"
							"}"
						"</style>"
					"</head>"
					"<body style=\"font-family:\'Noto Sans\'; font-size:10pt; font-weight:400; font-style:normal;\">"
						"<p align=\"center\" style=\"margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">"
							"Block Hash: " + text +
						"</p>"
					"</body>"
				"</html>"
			).c_str()
		)
	);
}

// Display the current nonce value
void Status::SetNonce(int nonce) {
	m_NonceView->setHtml(
		QString(
			string(
				"<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">"
				"<html>"
					"<head>"
						"<meta name=\"qrichtext\" content=\"1\" />"
						"<style type=\"text/css\">"
							"p, li {"
								"white-space: pre-wrap;"
							"}"
						"</style>"
					"</head>"
					"<body style=\"font-family:\'Noto Sans\'; font-size:10pt; font-weight:400; font-style:normal;\">"
						"<p align=\"center\" style=\"margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">"
							"Current Nonce: " + std::to_string(nonce) +
						"</p>"
					"</body>"
				"</html>"
			).c_str()
		)
	);
}

// Set the current elapsed mining time
void Status::SetTime(std::chrono::duration<float> elaspedTime) {}
