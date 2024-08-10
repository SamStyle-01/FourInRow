#ifndef SAMSKINBUTTON_H
#define SAMSKINBUTTON_H

#include "pch.h"
#include "SamCellsView.h"

class SamStartGame;

class SamSkinButton : public QPushButton {
    int* index;
    int* index_2;
public:
    SamSkinButton(int* index, int* index_2, QWidget* parent = nullptr);
    explicit SamSkinButton(int* index, QWidget* parent = nullptr);
    void mousePressEvent(QMouseEvent *event);
    int getIndex() const;
};

#endif // SAMSKINBUTTON_H
