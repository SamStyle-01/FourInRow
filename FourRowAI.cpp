#include "FourRowAI.h"
#include "SamLogic.h"

FourRowAI::FourRowAI() {}

FourRowAI::~FourRowAI() {}

int FourRowAI::MakeMove() {
    this->board->index = -1;

    for (int i = 0; i < COLS; i++) {
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

    for (int i = 0; i < COLS; i++) {
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

    for (int i = 0; i < COLS - 3; i++) {
        if (this->board->CheckLegal(i) && this->board->CheckLegal(i + 3)) {
            this->board->SetCell(i, opponentFigure);
            this->board->SetCell(i + 3, opponentFigure);
            if (this->board->CheckEndConditionIter()) {
                this->board->ClearCell(i);
                this->board->ClearCell(i + 3);

                this->board->SetCell(i, this->cellType);
                QPair<int, int> est1 = this->board->getEstimation();
                int estimation1 = (cellType == CELLTYPE_X) ? est1.first - est1.second : est1.second - est1.first;
                this->board->ClearCell(i);

                this->board->SetCell(i + 3, this->cellType);
                QPair<int, int> est2 = this->board->getEstimation();
                int estimation2 = (cellType == CELLTYPE_X) ? est2.first - est2.second : est2.second - est2.first;
                this->board->ClearCell(i + 3);

                int final;
                estimation1 > estimation2 ? final = i: final = i + 3;
                this->board->SetCell(final, this->cellType);

                this->board->stepsBack.push(final);
                this->board->stepsForward.clear();

                board->bVictory = false;
                return 1;
            }
            this->board->ClearCell(i);
            this->board->ClearCell(i + 3);
        }
    }

    QVector<int> PossibleSteps;
    PossibleSteps.reserve(COLS);
    int opponentWin = (opponentFigure == CELLTYPE_X ? 1 : 2);
    for (int i = 0; i < COLS; i++) {
        if (this->board->CheckLegal(i)) {
            this->board->SetCell(i, this->cellType);
            if (this->board->CheckLegal(i)) {
                this->board->SetCell(i, opponentFigure);
                if (this->board->CheckEndConditionIter() != opponentWin)
                    PossibleSteps.push_back(i);
                this->board->ClearCell(i);
            }
            else PossibleSteps.push_back(i);
            this->board->ClearCell(i);
        }
    }

    if (!PossibleSteps.size()) {
        for (int i = 0; i < COLS; i++) {
            PossibleSteps.push_back(i);
        }
    }

    SamLogic* cells = new SamLogic(board->getCells());
    AlphaBetaTree tree(cells, cellType, PossibleSteps);

    int col = tree.getNextMove();

    this->board->SetCell(col, this->cellType);
    this->board->stepsBack.push(col);
    this->board->stepsForward.clear();

    return 1;
}
