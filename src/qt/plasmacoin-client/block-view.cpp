//
// FILENAME: block-view.h | Plasmacoin Cryptocurrency
// DESCRIPTION: Manage a table of block data
// CREATED: 2022-05-28 @ 10:59 AM
// COPYRIGHT: Copyright (c) 2022 by Ryan Smith <rysmith2113@gmail.com>
//

#include "block-view.h"

BlockView::BlockView(QTableWidget* blockView):
	m_BlockView(blockView)
{}

BlockView::~BlockView() {
	delete m_BlockView;
}

void BlockView::Display(Block* block) {
	//
	// Out of the Plasmacoin block fields, 9 of them are known regardless of the number
	// of transactions on the block. If we choose to omit the data about the genesis block
	// here, we will know 8 of them. Additional rows will be added based on the number of
	// transactions on the block.
	//
	const int KNOWN_ROWS = 8;
	m_BlockView->setRowCount(KNOWN_ROWS + block->m_Transactions.size());

	std::vector<std::pair<QTableWidgetItem, QTableWidgetItem>> table = {
		{
			QTableWidgetItem(QString("Index")),
			QTableWidgetItem(QString::number(block->m_Index))
		},
		{
			QTableWidgetItem(QString("Nonce")),
			QTableWidgetItem(QString::number(block->m_Nonce))
		},
		{
			QTableWidgetItem(QString("Difficulty")),
			QTableWidgetItem(QString::number(block->m_Difficulty))
		},
		{
			QTableWidgetItem(QString("Hash")),
			QTableWidgetItem(QString::fromStdString(block->m_Hash))
		},
		{
			QTableWidgetItem(QString("Previous Hash")),
			QTableWidgetItem(QString::fromStdString(block->m_PrevHash))
		},
		{
			QTableWidgetItem(QString("Miner")),
			QTableWidgetItem(QString::fromStdString(block->m_MinerAddr))
		},
		{
			QTableWidgetItem(QString("Created")),
			QTableWidgetItem(QString::fromStdString(utility::formatEpoch(block->m_CreationTime)))
		},
		{
			QTableWidgetItem(QString("Mined")),
			QTableWidgetItem(QString::fromStdString(utility::formatEpoch(block->m_MineTime)))
		},
	};

	// Add the transactions to the table
	for (auto trxn: block->m_Transactions) {
		table.push_back(
			{
				QTableWidgetItem(QString("Transaction")),
				QTableWidgetItem(QString::fromStdString(trxn->m_Hash))
			}
		);
	}

	for (auto row = table.begin(); row != table.end(); std::advance(row, 1)) {
		// Center-align all elements
		row->first.setData(Qt::TextAlignmentRole, Qt::AlignCenter);
		row->second.setData(Qt::TextAlignmentRole, Qt::AlignCenter);

		m_BlockView->setItem(std::distance(table.begin(), row), 0, new QTableWidgetItem(row->first));
		m_BlockView->setItem(std::distance(table.begin(), row), 1, new QTableWidgetItem(row->second));
	}
}

void BlockView::Clear() {
	m_BlockView->setRowCount(0);
}