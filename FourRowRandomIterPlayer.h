#pragma once

#ifndef _FOURROWRANDOMITERPLAYER_H_

#define _FOURROWRANDOMITERPLAYER_H_

#include "SamLogic.h"
#include "FourRowPlayer.h"

class FourRowRandomIterPlayer {
    SamLogic* board;
    CellType cellType;
    QString name;
public:
    ~FourRowRandomIterPlayer();
    void SetupPlayer(QString name, CellType cellType);
    void SetBoard(SamLogic* board);
    int MakeMove();
    QString GetName() const;
    FourRowRandomIterPlayer();
};

#endif
