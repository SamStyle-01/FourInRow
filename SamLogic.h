#ifndef SAMLOGIC_H
#define SAMLOGIC_H

#include "pch.h"

extern int ROWS, COLS, WIN_CONDITION, NUM_PICTURES;

class SamLogic {
    CellType** cells;

    int IsRowMade(unsigned row);
    int IsColumnMade(unsigned col);
    bool IsBoardFull();

public:
    bool bVictory;
    explicit SamLogic();
    SamLogic(CellType** view);
    virtual ~SamLogic();
    void SetCell(int xpos, CellType ct);
    void ClearStart();
    bool CheckLegal(int xpos);
    int CheckEndCondition();
    bool IsVictory();
    void ClearCell(int xpos);
    std::pair<int, int> GetSize() const;

    QStack<int> stepsBack;
    QStack<int> stepsForward;

    int checkMainDiags();
    int checkSideDiags();

    SamLogic(SamLogic* board);

    void setCells();

    QPair<int, int> getEstimation();
};

#endif // SAMLOGIC_H
