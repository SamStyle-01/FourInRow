#pragma once

#ifndef _FOURROWRANDOMPLAYER_H_

#define _FOURROWRANDOMPLAYER_H_

#include "SamCellsView.h"
#include "FourRowPlayer.h"

class FourRowRandomPlayer : public FourRowPlayer {
public:
	FourRowRandomPlayer();
	virtual ~FourRowRandomPlayer();
    int MakeMove();
};

#endif
