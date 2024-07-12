#ifndef FOURROWWEBPLAYER_H
#define FOURROWWEBPLAYER_H

#include "FourRowPlayer.h"

class FourRowWebPlayer : public FourRowPlayer {
public:
    FourRowWebPlayer();
    virtual ~FourRowWebPlayer();
    int MakeMove();
};

#endif
