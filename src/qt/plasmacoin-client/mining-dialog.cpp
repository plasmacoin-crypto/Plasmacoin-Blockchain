
#include "mining-dialog.h"

MiningDialog::MiningDialog(QWidget* parent) {
	Ui_MiningDialog::setupUi(this);
	this->setModal(true);

	m_BlockInfo = Ui::MiningDialog::blockInfo;
}

MiningDialog::~MiningDialog() {
	delete m_BlockInfo;
}

void MiningDialog::Display(Block* block) {
	m_BlockInfo->setRowCount(8);
	int rows = m_BlockInfo->rowCount();

	std::vector<std::pair<QTableWidgetItem, QTableWidgetItem>> table = {
		{
			QTableWidgetItem(QString("Block Index")),
			QTableWidgetItem(QString::number(block->m_Index))
		},
		{
			QTableWidgetItem(QString("Nonce")),
			QTableWidgetItem(QString::number(block->m_Nonce))
		},
		{
			QTableWidgetItem(QString("Difficulty")),
			QTableWidgetItem(QString::number(block->m_Difficulty, 'f', 10))
		},
		{
			QTableWidgetItem(QString("Block Hash (Merkle Tree Root)")),
			QTableWidgetItem(QString::fromStdString(block->m_Hash))
		},
		{
			QTableWidgetItem(QString("Previous Block Hash")),
			QTableWidgetItem(QString::fromStdString(block->m_PrevHash))
		},
		{
			QTableWidgetItem(QString("Created")),
			QTableWidgetItem(QString::fromStdString(utility::formatEpoch(block->m_CreationTime)))
		},
		{
			QTableWidgetItem(QString("Mined")),
			QTableWidgetItem(QString::fromStdString(utility::formatEpoch(block->m_MineTime)))
		},
		{
			QTableWidgetItem(QString("Transaction Count")),
			QTableWidgetItem(QString::number(block->m_Transactions.size()))
		},
		{
			QTableWidgetItem(QString("Block Size")),
			QTableWidgetItem(QString::number(dssize::size(*block)))
		},
	};

	for (auto row = table.begin(); row != table.end(); std::advance(row, 1)) {
		// Left-align all elements
		row->first.setData(Qt::TextAlignmentRole, Qt::AlignVCenter);
		row->second.setData(Qt::TextAlignmentRole, Qt::AlignVCenter);

		m_BlockInfo->setItem(std::distance(table.begin(), row), 0, new QTableWidgetItem(row->first));
		m_BlockInfo->setItem(std::distance(table.begin(), row), 1, new QTableWidgetItem(row->second));
	}

	m_BlockInfo->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
	m_BlockInfo->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);

	this->exec();
	this->setGeometry(m_BlockInfo->x(), m_BlockInfo->y(), this->width() + 100, this->height());
}
