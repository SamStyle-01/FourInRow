#include "FourRowBoardMonteCarloEvaluator.h"

FourRowBoardMonteCarloEvaluator::~FourRowBoardMonteCarloEvaluator() {}

FourRowBoardMonteCarloEvaluator::FourRowBoardMonteCarloEvaluator(SamCellsView* board, int numIterations,
	CellType startCellType, unsigned int xpos) {
	this->board = board;
	this->numGames = numIterations;
	this->numDraws = 0;
	this->numVictories = 0;
	this->numLosses = 0;
	this->xpos = xpos;
	this->startCellType = startCellType;
}

void FourRowBoardMonteCarloEvaluator::EvaluateBoard() {
    SamLogic* b = new SamLogic(board->getCells());
    FourRowRandomIterPlayer* player1 = new FourRowRandomIterPlayer();
    FourRowRandomIterPlayer* player2 = new FourRowRandomIterPlayer();
    FourRowRandomIterPlayer* currentPlayer;
	bool bGameFinished = false;

	player1->SetupPlayer("RandomX", CELLTYPE_X);
	player2->SetupPlayer("RandomO", CELLTYPE_O);
	player1->SetBoard(b);
	player2->SetBoard(b);
	currentPlayer = (this->startCellType == CELLTYPE_X) ? player1 : player2;

    if (b->CheckEndCondition()) {
		if (b->IsVictory()) {
			if (currentPlayer == player1)
				numLosses++;
			else
				numVictories++;
		}
		else
            numDraws++;
		return;
	}

	while (!bGameFinished) {
        while (!currentPlayer->MakeMove());

        if (b->CheckEndCondition()) {
			if (b->IsVictory()) {
				if (currentPlayer == player1)
					numVictories++;
				else
					numLosses++;
			}
			else
				numDraws++;
			bGameFinished = true;
		}
		currentPlayer = (currentPlayer == player1) ? player2 : player1;
    }
    delete player1;
    delete player2;
    delete b;
}

void FourRowBoardMonteCarloEvaluator::Evaluate() {
	for (int i = 0; i < numGames; i++)
		EvaluateBoard();
}

int FourRowBoardMonteCarloEvaluator::GetVictories() const {
	return numVictories;
}

int FourRowBoardMonteCarloEvaluator::GetLosses() const {
	return numLosses;
}

int FourRowBoardMonteCarloEvaluator::GetDraws() const {
	return numDraws;
}

int FourRowBoardMonteCarloEvaluator::GetXPos() const {
	return xpos;
}
