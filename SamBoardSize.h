#ifndef SAMBOARDSIZE_H
#define SAMBOARDSIZE_H

#include "pch.h"
#include "SamCellsView.h"

enum class BoardSizeState {
    s7x6,
    s8x7,
    s8x8,
    s9x7,
    s9x9,
    none
};

class SamBoardSize : public QPushButton {
    BoardSizeState state;
public:
    explicit SamBoardSize(QWidget* parent);
    void mousePressEvent(QMouseEvent *event);
    void resetState();
    BoardSizeState getState() const;
};

#endif // SAMBOARDSIZE_H
