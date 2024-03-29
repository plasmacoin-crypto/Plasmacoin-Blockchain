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
	m_Heading->setGeometry(QRect(690, 80, 551, 41));

	// The hash of the mined block
	m_HashView->setObjectName(QString::fromUtf8("hashView"));
	m_HashView->setGeometry(QRect(690, 130, 551, 51));

	// A readout of the current nonce value
	m_NonceView->setObjectName(QString::fromUtf8("nonceView"));
	m_NonceView->setGeometry(QRect(690, 190, 271, 41));

	// A readout of the elapsed mining time
	m_ElapsedTime->setObjectName(QString::fromUtf8("elapsedTime"));
	m_ElapsedTime->setGeometry(QRect(980, 190, 261, 41));

	m_Heading->setVisible(false);
	m_HashView->setVisible(false);
	m_NonceView->setVisible(false);
	m_ElapsedTime->setVisible(false);
}

Status::~Status() {
	delete m_Heading;
	delete m_HashView;
	delete m_NonceView;
	delete m_ElapsedTime;
}

// Render the mining status visuals on the screen
void Status::LoadVisuals() {
	m_HashView->setVisible(true);
	m_NonceView->setVisible(true);
	m_ElapsedTime->setVisible(true);
}

void Status::HideVisuals() {
	m_HashView->setVisible(false);
	m_NonceView->setVisible(false);
	m_ElapsedTime->setVisible(false);
}

// Set the heading
void Status::SetHeading(const string& text) {
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
void Status::SetHash(const string& text) {
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
void Status::SetTime(std::chrono::seconds elapsedTime) {
	m_ElapsedTime->setHtml(
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
							"Elapsed Time: " + std::to_string(elapsedTime.count()) +
						"</p>"
					"</body>"
				"</html>"
			).c_str()
		)
	);
}
