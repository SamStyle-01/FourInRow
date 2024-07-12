#ifndef GAMEMODEBUTTON_H
#define GAMEMODEBUTTON_H

#include "pch.h"

enum class GameMode {
    CLASSIC,
    Timer30s,
    Timer10s,
    Timer1minAll,
    Timer2minAll,
    Train
};

class GameModeButton : public QPushButton {
    GameMode state;
public:
    GameModeButton(QWidget* parent);
    void mousePressEvent(QMouseEvent *event);
    GameMode getState() const;
    void setClassic();
};

#endif // GAMEMODEBUTTON_H
