#pragma once

#ifndef _FOURROWBOARDMONTECARLOEVALUATOR_H_

#define _FOURROWBOARDMONTECARLOEVALUATOR_H_

#include "SamCellsView.h"
#include "FourRowRandomIterPlayer.h"

class FourRowBoardMonteCarloEvaluator {
private:
    SamCellsView* board;
	int numGames;
	int numVictories;
	int numLosses;
	int numDraws;
	unsigned int xpos;
	CellType startCellType;
public:
    FourRowBoardMonteCarloEvaluator(SamCellsView* board, int numIterations, CellType startCellType, unsigned int xpos);
	~FourRowBoardMonteCarloEvaluator();
	void Evaluate();
	void EvaluateBoard();
	int GetVictories() const;
	int GetLosses() const;
	int GetDraws() const;
	int GetXPos() const;
};

#endif
