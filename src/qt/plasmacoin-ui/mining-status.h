//
// FILENAME: mining-status.h | Plasmacoin Cryptocurrency
// DESCRIPTION: Display some info boxes while a block is being mined
// CREATED: 2021-04-02 @ 4:22 PM
// COPYRIGHT: Copyright (c) 2021 by Ryan Smith <rysmith2113@gmail.com>
//

#include <QString>
#include <QTextBrowser>
#include <QRect>

#include <string>
#include <chrono>

using std::string;

class Status {
public:
	Status() = default;
	Status(QTextBrowser* qtbrowser1, QTextBrowser* qtbrowser2, QTextBrowser* qtbrowser3, QTextBrowser* qtbrowser4);

	void LoadVisuals();

	// Functions to modify the browser text
	void SetHeading(string text), SetHash(string text), SetNonce(int nonce);
	void SetTime(std::chrono::seconds elapsedTime);

private:
	QTextBrowser *m_Heading, *m_HashView, *m_NonceView, *m_ElapsedTime;
};
