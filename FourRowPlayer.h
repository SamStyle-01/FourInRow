#pragma once

#ifndef _FOURROWPLAYER_H_

#define _FOURROWPLAYER_H_

#include "SamCellsView.h"
#include "pch.h"

class FourRowPlayer {
protected:
    SamCellsView* board;
	CellType cellType;
    QString name;
public:
	virtual ~FourRowPlayer();
    void SetupPlayer(QString name, CellType cellType);
    void SetBoard(SamCellsView* board);
    virtual int MakeMove() = 0;
    QString GetName() const;
};

#endif
