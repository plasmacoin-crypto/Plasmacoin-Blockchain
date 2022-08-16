//
// FILENAME: blockchain-viewer.cpp | Plasmacoin Cryptocurrency
// DESCRIPTION: The source file for blockchain-viewer.h
// CREATED: 2021-05-28 @ 10:19 AM
// COPYRIGHT: Copyright (c) 2022 by Ryan Smith <rysmith2113@gmail.com>
//

#include "blockchain-viewer.h"

BlockchainViewer::BlockchainViewer(Ui_MainWindow* window, Blockchain* blockchain):
	m_Window(window),
	m_BlockchainCopy(blockchain)
{
	m_BlockView = new BlockView(window->blockView);
	m_TransactionView = new TransactionView(window->blockTrxnView);
}

BlockchainViewer::~BlockchainViewer() {
	delete m_BlockView;
}

// View a block on the blockchain
void BlockchainViewer::View(int index) {
	// Make sure the index is valid
	const auto MAX_INDEX = (m_BlockchainCopy->Size() == 0)? 0 : m_BlockchainCopy->Size() - 1;

	if (index < 0 || static_cast<uint64_t>(index) > MAX_INDEX || m_BlockchainCopy->Empty()) {
		return;
	}

	m_CurrentBlock = index;
	m_BlockView->Display(m_BlockchainCopy->Get(m_CurrentBlock));
}

// View the next block
void BlockchainViewer::Next() {
	View(m_CurrentBlock + 1);
}

// View the previous block
void BlockchainViewer::Previous() {
	View(m_CurrentBlock - 1);
}

// View the genesis block
void BlockchainViewer::Genesis() {
	View(0);
}

// View the latest block
void BlockchainViewer::Latest() {
	View(m_BlockchainCopy->Size() - 1);
}

void BlockchainViewer::ShowTransaction(Transaction* transaction) {
	m_TransactionView->Display(transaction);
}

// Determine what blockchain viewer buttons are enabled based on what block the user is viewing
std::tuple<bool, bool, bool, bool> BlockchainViewer::GetBtnStates() {
	bool genesis = false, previous = false, next = false, latest = false;
	const auto MAX_INDEX = (m_BlockchainCopy->Size() == 0)? 0 : m_BlockchainCopy->Size() - 1;

	if (m_CurrentBlock == 0) {
		//
		// The current index is the genesis block
		//
		// If the blockchain has more than one block, the user can navigate forward
		// one block or to the latest block. If the current index is the max index
		// (i.e., the blockchain only has one block), then all the buttons should be
		// disabled.
		//

		if (MAX_INDEX > 0) {
			next = true;
			latest = true;
		}
	}
	else if (m_CurrentBlock == MAX_INDEX) {
		//
		// The current index is the index of the latest block in the blockchain, and
		// number of blocks in the chain is more than one.
		//
		// In this case, the user can navigate backward, but not forward.
		//

		genesis = true;
		previous = true;
	}
	else {
		// The index is somewhere in the middle, so every button is enabled
		genesis = true;
		previous = true;
		next = true;
		latest = true;
	}

	return std::make_tuple(genesis, previous, next, latest);
}