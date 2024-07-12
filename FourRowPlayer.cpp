#include "FourRowPlayer.h"

FourRowPlayer::~FourRowPlayer() {}

void FourRowPlayer::SetupPlayer(QString name, CellType cellType) {
	this->name = name;
	this->cellType = cellType;
}

void FourRowPlayer::SetBoard(SamCellsView* board) {
	this->board = board;
}

QString FourRowPlayer::GetName() const {
	return this->name;
}
