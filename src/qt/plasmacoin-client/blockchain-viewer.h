//
// FILENAME: blockchain-viewer.h | Plasmacoin Cryptocurrency
// DESCRIPTION: The blockchain viewer
// CREATED: 2021-05-28 @ 10:19 AM
// COPYRIGHT: Copyright (c) 2022 by Ryan Smith <rysmith2113@gmail.com>
//

#ifndef BLOCKCHAIN_VIEWER_H
#define BLOCKCHAIN_VIEWER_H

#include <QMainWindow>
#include <QTableWidget>
#include <QTableWidgetItem>

#include <tuple>

#include "ui.h"

#include "transaction-view.h"
#include "block-view.h"

#include "blockchain.hpp"
#include "transaction.hpp"

class BlockchainViewer : public QMainWindow, public Ui_MainWindow {
public:
	BlockchainViewer(Blockchain* blockchain, QTableWidget* blockView, QTableWidget* transactionView);
	~BlockchainViewer();

	uint64_t GetIndex() const;

	void View(int index = 0);

	void Next();
	void Previous();

	void Genesis();
	void Latest();

	void ShowTransaction(Transaction* transaction);

	std::tuple<bool, bool, bool, bool> GetBtnStates();

private:
	uint64_t m_CurrentBlock = 0;

	Blockchain* m_BlockchainCopy;

	TransactionView* m_TransactionView;
	BlockView* m_BlockView;
};

inline uint64_t BlockchainViewer::GetIndex() const {
	return m_CurrentBlock;
}

#endif // BLOCKCHAIN_VIEWER_H