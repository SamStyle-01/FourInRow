#pragma once

#ifndef SAMWINLINE_H
#define SAMWINLINE_H

#include "pch.h"

enum class LineState {
    ROW,
    COL,
    DIAG_RIGHT,
    DIAG_LEFT,
    NONE
};

class SamWinLine : public QLabel {
    void paintEvent(QPaintEvent *event) override;
    LineState state;

public:
    explicit SamWinLine(QWidget *parent = nullptr);
    void Activate(LineState state);
    void DisActivate();
};

#endif
