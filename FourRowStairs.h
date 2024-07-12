#ifndef FOURROWSTAIRS_H
#define FOURROWSTAIRS_H

#include "FourRowPlayer.h"

extern int ROWS;
extern int COLS;

class FourRowStairs : public FourRowPlayer
{
public:
    FourRowStairs();
    ~FourRowStairs();
    int MakeMove();
};

#endif // FOURROWSTAIRS_H
