#include "FourRowStairs.h"

FourRowStairs::FourRowStairs() {}

FourRowStairs::~FourRowStairs() {}

int FourRowStairs::MakeMove() {
    this->board->index = -1;
    for (int i = 0; i < COLS; i++) {
        if (this->board->CheckLegal(i)) {
            this->board->SetCell(i, this->cellType);
            if (dynamic_cast<SamLogic*>(this->board)->CheckEndCondition()) {
                board->setBVictory(false);
                this->board->stepsBackPush(i);
                this->board->stepsForwardClear();
                return 1;
            }
            this->board->ClearCell(i);
        }
    }

    CellType opponentFigure = (this->cellType == CELLTYPE_O ? CELLTYPE_X : CELLTYPE_O);

    for (int i = 0; i < COLS; i++) {
        if (this->board->CheckLegal(i)) {
            this->board->SetCell(i, opponentFigure);
            if (dynamic_cast<SamLogic*>(this->board)->CheckEndCondition()) {
                this->board->ClearCell(i);
                this->board->SetCell(i, this->cellType);
                board->setBVictory(false);
                this->board->stepsBackPush(i);
                this->board->stepsForwardClear();
                return 1;
            }
            this->board->ClearCell(i);
        }
    }

    for (int i = 0; i < COLS - 3; i++) {
        if (this->board->CheckLegal(i) && this->board->CheckLegal(i + 3)) {
            this->board->SetCell(i, opponentFigure);
            this->board->SetCell(i + 3, opponentFigure);
            if (dynamic_cast<SamLogic*>(this->board)->CheckEndCondition()) {
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

                this->board->stepsBackPush(final);
                this->board->stepsForwardClear();

                board->setBVictory(false);
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
                if (dynamic_cast<SamLogic*>(this->board)->CheckEndCondition() != opponentWin)
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

    QVector<int> estimations;
    estimations.reserve(PossibleSteps.size());
    int maxMove = -1;
    for (int i = 0; i < COLS; i++) {
        if (this->board->CheckLegal(PossibleSteps[i])) {
            board->SetCell(PossibleSteps[i], this->cellType);
            QPair<int, int> est = this->board->getEstimation();
            estimations.push_back((cellType == CELLTYPE_X) ? est.first - est.second : est.second - est.first);
            if (maxMove == -1 || estimations[PossibleSteps[i]] > estimations[maxMove]) {
                maxMove = PossibleSteps[i];
            }
            board->ClearCell(PossibleSteps[i]);
        }
        else estimations.push_back(-1000000);
    }

    for (int i = 0; i < 10; i++) {
        int finalMove = rand() % PossibleSteps.size();
        if (estimations[maxMove] - estimations[finalMove] <= 10 && estimations[finalMove] != -1000000) {
            if (!(rand() % 3))
                maxMove = PossibleSteps[finalMove];
            break;
        }
    }

    board->SetCell(maxMove, cellType);
    board->setBVictory(false);

    this->board->stepsBackPush(maxMove);
    this->board->stepsForwardClear();
    return 1;
}
