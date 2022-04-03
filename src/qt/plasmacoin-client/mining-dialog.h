//
// FILENAME: mining-dialog.hpp | Plasmacoin Cryptocurrency
// DESCRIPTION: A dialog that provides a mining summary for the user
// CREATED: 2022-04-02 @ 9:17 PM
// COPYRIGHT: Copyright (c) 2022 by Ryan Smith <rysmith2113@gmail.com>
//

#ifndef MINING_DIALOG_H
#define MINING_DIALOG_H

#include <vector>
#include <utility>
#include <iterator>

#include <QDialog>
#include <QWidget>
#include <QTableWidget>
#include <QTableWidgetItem>

#include "block.hpp"
#include "dssize.hpp"

#include "ui_miningdialog.h"

namespace Ui {
	class MiningDialog;
}

class MiningDialog : public QDialog, public Ui::MiningDialog {
	//Q_OBJECT

public:
	explicit MiningDialog(QWidget* parent = nullptr);
	~MiningDialog();

	void Display(Block* block);

private:
	QTableWidget* m_BlockInfo;
};

#endif // MINING_DIALOG_H