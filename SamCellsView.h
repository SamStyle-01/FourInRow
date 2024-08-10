#pragma once

#ifndef SAMCELLS_H
#define SAMCELLS_H

#include "pch.h"
#include "CellType.h"
#include "SamRow.h"
#include "SamWinLine.h"
#include "SamLogic.h"

extern int ROWS, COLS, WIN_CONDITION, NUM_PICTURES;

class SamCellsView : public QWidget, public SamLogic {
    friend SamGame;

    QLabel** viewCells;
    QPixmap** playersCells;
    QPixmap* emptyCell;

    bool IsRowMade(unsigned row);
    bool IsColumnMade(unsigned col);
    bool IsBoardFull();

    QGridLayout* fieldLayout;
    SamWinLine* line;
public:
    SamRow** cols;
    explicit SamCellsView(QWidget *parent = nullptr);
    SamCellsView(bool t);
    virtual ~SamCellsView();
    void InitIt(SamCellsView* board);
    int index;
    int web_index;
    void Show();
    void ClearStart();
    bool CheckEndCondition();

    bool oneOnBoard() const;

    bool checkMainDiags();
    bool checkSideDiags();

    int skin1;
    int skin2;

    void setCells();

    CellType** getCells();
};

#endif // SAMCELLS_H
