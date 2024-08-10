#include "FourRowHumanPlayer.h"

FourRowHumanPlayer::FourRowHumanPlayer() {}

FourRowHumanPlayer::~FourRowHumanPlayer() {}

int FourRowHumanPlayer::MakeMove() {
    if (this->board->index >= 0) {
        if (this->board->CheckLegal(this->board->index)) {
            this->board->SetCell(this->board->index, this->cellType);
            this->board->stepsBackPush(this->board->index);
            this->board->stepsForwardClear();
            return 1;
        }
    }
    if (this->board->index == -2 || this->board->index == -1) {
        return 2;
    }

    return 0;
}
