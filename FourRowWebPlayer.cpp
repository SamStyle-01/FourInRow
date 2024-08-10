#include "FourRowWebPlayer.h"

FourRowWebPlayer::FourRowWebPlayer() {}

FourRowWebPlayer::~FourRowWebPlayer() {}

int FourRowWebPlayer::MakeMove() {
    this->board->index = -1;
    if (this->board->web_index >= 0) {
        if (this->board->CheckLegal(this->board->web_index)) {
            this->board->SetCell(this->board->web_index, this->cellType);
            this->board->stepsBackPush(this->board->web_index);
            this->board->stepsForwardClear();

            return 1;
        }
    }

    return 2;
}
