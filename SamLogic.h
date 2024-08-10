#ifndef SAMLOGIC_H
#define SAMLOGIC_H

#include "pch.h"

extern int ROWS, COLS, WIN_CONDITION, NUM_PICTURES;

class SamLogic {
protected:
    CellType** cells;

    int IsRowMade(unsigned row);
    int IsColumnMade(unsigned col);
    bool IsBoardFull();
    bool bVictory;

    QStack<int> stepsBack;
    QStack<int> stepsForward;
public:
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

    void setBVictory(bool victory);

    void stepsBackPush(int step);
    void stepsBackReserve(int count);
    void stepsBackClear();
    int stepsBackTop() const;
    void stepsBackPop();
    bool stepsBackIsEmpty() const;

    void stepsForwardPush(int step);
    void stepsForwardReserve(int count);
    void stepsForwardClear();
    int stepsForwardTop() const;
    void stepsForwardPop();
    bool stepsForwardIsEmpty() const;

    int checkMainDiags();
    int checkSideDiags();

    SamLogic(SamLogic* board);

    void setCells();

    QPair<int, int> getEstimation();
};

#endif // SAMLOGIC_H
