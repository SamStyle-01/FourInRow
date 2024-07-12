#pragma once

#ifndef SAMCELLS_H
#define SAMCELLS_H

#include "pch.h"
#include "CellType.h"
#include "SamRow.h"
#include "SamWinLine.h"

extern int ROWS, COLS, WIN_CONDITION, NUM_PICTURES;

class SamCellsView : public QWidget {
    CellType** cells;
    QLabel** viewCells;
    QPixmap** playersCells;
    QPixmap* emptyCell;

    bool IsRowMade(unsigned row);
    bool IsColumnMade(unsigned col);
    bool IsBoardFull();

    int IsRowMadeIter(unsigned row);
    int IsColumnMadeIter(unsigned col);

public:
    bool bVictory;
    SamRow** cols;
    explicit SamCellsView(QWidget *parent = nullptr);
    SamCellsView(bool t);
    virtual ~SamCellsView();
    void InitIt(SamCellsView* board);
    int index;
    int web_index;
    void Show();
    void SetCell(int xpos, CellType ct);
    void ClearStart();
    bool CheckLegal(int xpos);
    bool CheckEndCondition();
    bool IsVictory();
    void ClearCell(int xpos);
    std::pair<int, int> GetSize() const;

    bool oneOnBoard() const;

    QGridLayout* fieldLayout;
    SamWinLine* line;

    QStack<int> stepsBack;
    QStack<int> stepsForward;

    bool checkMainDiags();
    bool checkSideDiags();

    int CheckEndConditionIter();
    int checkMainDiagsIter();
    int checkSideDiagsIter();

    int skin1;
    int skin2;

    void setCells();

    QPair<int, int> getEstimation();

    CellType** getCells();
};

#endif // SAMCELLS_H
