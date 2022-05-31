//
// FILENAME: block-view.h | Plasmacoin Cryptocurrency
// DESCRIPTION: Manage a table of block data
// CREATED: 2022-05-28 @ 10:59 AM
// COPYRIGHT: Copyright (c) 2022 by Ryan Smith <rysmith2113@gmail.com>
//

#ifndef BLOCK_VIEW_H
#define BLOCK_VIEW_H

#include <vector>
#include <utility>
#include <iterator>

#include <QMainWindow>
#include <QTableWidget>
#include <QTableWidgetItem>

#include "ui.h"
#include "block.hpp"

class BlockView : public QMainWindow, public Ui_MainWindow {
public:
	BlockView(QTableWidget* blockView);
	~BlockView();

	void Display(Block* block);
	void Clear();

private:
	QTableWidget* m_BlockView;
};

#endif // BLOCK_VIEW_H