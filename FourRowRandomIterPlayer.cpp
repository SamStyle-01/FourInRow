#include "FourRowRandomIterPlayer.h"

FourRowRandomIterPlayer::FourRowRandomIterPlayer() {}

FourRowRandomIterPlayer::~FourRowRandomIterPlayer() {}

int FourRowRandomIterPlayer::MakeMove() {
	unsigned col;

	col = (unsigned)(rand() % board->GetSize().second);

	if (this->board->CheckLegal(col)) {
        this->board->SetCell(col, this->cellType);
        return 1;
	}
    return 0;
}

void FourRowRandomIterPlayer::SetupPlayer(QString name, CellType cellType) {
    this->name = name;
    this->cellType = cellType;
}

void FourRowRandomIterPlayer::SetBoard(SamLogic* board) {
    this->board = board;
}

QString FourRowRandomIterPlayer::GetName() const {
    return this->name;
}
