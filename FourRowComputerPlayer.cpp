#include "FourRowComputerPlayer.h"

FourRowKarlPlayer::FourRowKarlPlayer() {}

FourRowKarlPlayer::~FourRowKarlPlayer() {}

int FourRowKarlPlayer::MakeMove() {
    this->board->index = -1;
    for (int i = 0; i < board->GetSize().second; i++) {
        if (this->board->CheckLegal(i)) {
            this->board->SetCell(i, this->cellType);
            if (this->board->CheckEndConditionIter()) {
                board->bVictory = false;
                this->board->stepsBack.push(i);
                this->board->stepsForward.clear();
                return 1;
            }
            this->board->ClearCell(i);
        }
    }

    CellType opponentFigure = (this->cellType == CELLTYPE_O ? CELLTYPE_X : CELLTYPE_O);

    for (int i = 0; i < board->GetSize().second; i++) {
        if (this->board->CheckLegal(i)) {
            this->board->SetCell(i, opponentFigure);
            if (this->board->CheckEndConditionIter()) {
                this->board->ClearCell(i);
                this->board->SetCell(i, this->cellType);
                board->bVictory = false;
                this->board->stepsBack.push(i);
                this->board->stepsForward.clear();
                return 1;
            }
            this->board->ClearCell(i);
        }
    }

    QVector<FourRowBoardMonteCarloEvaluator*> evaluators;
    evaluators.reserve(board->GetSize().second);
    for (int j = 0; j < board->GetSize().second; j++) {
        if (this->board->CheckLegal(j)) {
            this->board->SetCell(j, this->cellType);
            evaluators.push_back(new FourRowBoardMonteCarloEvaluator(this->board, 1000,
                (this->cellType == CELLTYPE_X) ? CELLTYPE_O : CELLTYPE_X, j));
            this->board->ClearCell(j);
        }
    }

    for (auto evaluator = evaluators.begin(); evaluator != evaluators.end(); ++evaluator)
        (*evaluator)->Evaluate();

    int biggestVictories = -1;

    for (auto evaluator = evaluators.begin(); evaluator != evaluators.end(); ++evaluator) {
        if (this->cellType == CELLTYPE_X) {
            if ((*evaluator)->GetVictories() > biggestVictories)
                biggestVictories = (*evaluator)->GetVictories();
        }
        else {
            if ((*evaluator)->GetLosses() > biggestVictories)
                biggestVictories = (*evaluator)->GetLosses();
        }
    }

    QVector<FourRowBoardMonteCarloEvaluator*> biggestWinEvaluations;
    biggestWinEvaluations.reserve(evaluators.end() - evaluators.begin());
    for (auto evaluator = evaluators.begin(); evaluator != evaluators.end(); ++evaluator) {
        int numVictories;
        if (this->cellType == CELLTYPE_X)
            numVictories = (*evaluator)->GetVictories();
        else
            numVictories = (*evaluator)->GetLosses();
        if (numVictories == biggestVictories)
            biggestWinEvaluations.push_back((*evaluator));
    }

    this->board->SetCell(biggestWinEvaluations[0]->GetXPos(), this->cellType);
    this->board->stepsBack.push(biggestWinEvaluations[0]->GetXPos());
    this->board->stepsForward.clear();
    for (auto evaluator = evaluators.begin(); evaluator != evaluators.end(); ++evaluator) {
        delete (*evaluator);
    }
    evaluators.clear();
    biggestWinEvaluations.clear();
    board->bVictory = false;

    return 1;
}
