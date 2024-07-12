#include "FourRowRandomPlayer.h"

FourRowRandomPlayer::FourRowRandomPlayer() {}

FourRowRandomPlayer::~FourRowRandomPlayer() {}

int FourRowRandomPlayer::MakeMove() {
    unsigned col;

    this->board->index = -1;
    do {
        col = (unsigned)(rand() % board->GetSize().second);
    } while(!this->board->CheckLegal(col));
    this->board->SetCell(col, this->cellType);
    this->board->stepsBack.push(col);
    this->board->stepsForward.clear();

    return 1;
}
