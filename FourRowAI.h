#ifndef FOURROWAI_H

#define FOURROWAI_H

#include "pch.h"
#include "FourRowPlayer.h"
#include "AlphaBetaTree.h"

extern int ROWS;
extern int COLS;

class FourRowAI : public FourRowPlayer {
public:
    FourRowAI();
    ~FourRowAI();
    int MakeMove();
};

#endif // FOURROWAI_H
