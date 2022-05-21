//
// FILENAME: mining-status.h | Plasmacoin Cryptocurrency
// DESCRIPTION: Display some info boxes while a block is being mined
// CREATED: 2021-04-02 @ 4:22 PM
// COPYRIGHT: Copyright (c) 2021 by Ryan Smith <rysmith2113@gmail.com>
//

#include <QtWidgets/QMainWindow>
#include <QString>
#include <QTextBrowser>
#include <QRect>

#include <string>
#include <chrono>

#include "ui.h"

using std::string;

class Status : public QMainWindow, public Ui_MainWindow {
	Q_OBJECT

public:
	Status() = default;
	Status(QTextBrowser* qtbrowser1, QTextBrowser* qtbrowser2, QTextBrowser* qtbrowser3, QTextBrowser* qtbrowser4);
	~Status();

	void LoadVisuals(), HideVisuals();

	// Functions to modify the browser text
	void SetHeading(const string& text);
	void SetHash(const string& text);
	void SetNonce(int nonce);
	void SetTime(std::chrono::seconds elapsedTime);

signals:
	void FinishedMining();

public:
	QTextBrowser *m_Heading, *m_HashView, *m_NonceView, *m_ElapsedTime;
};
