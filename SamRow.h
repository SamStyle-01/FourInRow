#pragma once

#ifndef SAMROW_H
#define SAMROW_H

#include "pch.h"

class SamGame;

enum class ColorRow {
    TRANSPARENT,
    ORANGE
};

class SamRow : public QWidget {
    SamGame* game;
    int index;
    ColorRow color;
public:
    SamRow(QWidget* parent, int index, SamGame* game);
    void enterEvent(QEnterEvent *event);
    void leaveEvent(QEvent* event);
    void mousePressEvent(QMouseEvent* event);
    void setOrange();
    void setDefault();
};

#endif // SAMROW_H
