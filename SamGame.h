#pragma once

#ifndef SAMGAME_H
#define SAMGAME_H

#include "pch.h"
#include "SamCellsView.h"

#include "FourRowPlayer.h"
#include "FourRowHumanPlayer.h"
#include "FourRowWebPlayer.h"
#include "FourRowComputerPlayer.h"
#include "FourRowRandomPlayer.h"
#include "FourRowStairs.h"
#include "FourRowAI.h"
#include "SamWinLine.h"
#include "GameModeButton.h"

enum class TypePlayer {
    KARL,
    RANDOM,
    HUMAN,
    WEB_HUMAN,
    STAIRS,
    ALPHABETA
};

class SamStack;

class SamGame : public QWidget {
    QLabel* background;
    bool bGameFinished = false;
    SamStack* stack;
    void getClue();

public:
    explicit SamGame(SamStack* parent = nullptr);
    virtual ~SamGame();
    SamCellsView* board;

    QGridLayout* grid;
    void setCommonTimer();
    void setTrain();
    QLabel* lblCommonTimer;

    GameMode gameMode;
    int commonTimer;
    int stepsToLose;

    bool isHumanic;
    bool isWeb;

    QWidget* formNextPrevStep;
    QGridLayout* layoutNextPrevStep;

    int timerPl1;
    int timerPl2;

    QStack<int> wins;

    QPushButton* startNewGame;
    QPushButton* goHome;

    QPushButton* stepNext;
    QPushButton* stepPrev;
    QPushButton* clue;
    int currClue;
    QLabel* score;
    QPushButton* blurScore;
    bool isBluredScore;

    QLabel* WinsLosses;
    int player1Wins;
    int player2Wins;

    QLabel* lblCurrentStep;

    void resetGame();

    FourRowPlayer* currentPlayer;
    FourRowPlayer* player1;
    FourRowPlayer* player2;
    
    void setPlayer1(QString name, TypePlayer type, SamCellsView* board);
    void setPlayer2(QString name, TypePlayer type, SamCellsView* board);
    QString getDataPlayer(int index) const;

    void ShowBoard() const;
    void NextStep();
    void MakeMove();
    bool IsGameFinished();
    QTimer* timer;

    void stepBack();
    void stepForward();

    void startGameAgain();
};

#endif // SAMGAME_H
