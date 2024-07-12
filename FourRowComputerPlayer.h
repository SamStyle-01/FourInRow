#pragma once

#ifndef _FOURROWCOMPUTERPLAYER_H

#define _FOURROWCOMPUTERPLAYER_H

#include "pch.h"
#include "SamCellsView.h"
#include "FourRowPlayer.h"
#include "FourRowBoardMonteCarloEvaluator.h"

extern int ROWS;
extern int COLS;

class FourRowKarlPlayer : public FourRowPlayer {
public:
    FourRowKarlPlayer();
    virtual ~FourRowKarlPlayer();
    int MakeMove();
};

#endif
