#pragma once

#ifndef _FOURROWHUMANPLAYER_H_

#define _FOURROWHUMANPLAYER_H_

#include "SamCellsView.h"
#include "FourRowPlayer.h"

class FourRowHumanPlayer : public FourRowPlayer {
public:
	FourRowHumanPlayer();
	virtual ~FourRowHumanPlayer();
    int MakeMove();
};

#endif
