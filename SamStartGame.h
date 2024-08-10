#pragma once

#ifndef SAMSTARTGAME_H
#define SAMSTARTGAME_H

#include "pch.h"

#include "SamSkinButton.h"
#include "SamBoardSize.h"
#include "GameModeButton.h"
#include "SamRules.h"
#include "SamWeb.h"

class SamStartGame : public QWidget {
    friend SamStack;

    QPushButton* toStart;
    QLabel* background;

    QLabel* lblNewGame;
    QRadioButton* humanPlayer1;
    QRadioButton* humanPlayer2;
    QRadioButton* karlPlayer1;
    QRadioButton* karlPlayer2;
    QRadioButton* randomPlayer1;
    QRadioButton* randomPlayer2;
    QRadioButton* stairsPlayer1;
    QRadioButton* stairsPlayer2;
    QRadioButton* alphaBetaPlayer1;
    QRadioButton* alphaBetaPlayer2;
    QLabel* lblPlayer1;
    QLabel* lblPlayer2;
    QWidget* playerFirst;
    QWidget* playerSecond;
    QGridLayout* layoutPlayer1;
    QGridLayout* layoutPlayer2;

    SamRules* rules;

    QWidget* options;
    QVBoxLayout* options_layout;
    QLabel* lblOptions;

    QPushButton* openRules;
    QPushButton* webGame;

    SamBoardSize* boardSize;
    QGridLayout* grid;

    QLineEdit* linePlayer1;
    QLineEdit* linePlayer2;
    QButtonGroup* player1;
    QButtonGroup* player2;

    SamSkinButton* skin1;
    SamSkinButton* skin2;

    int skinIndexes[2];

    GameModeButton* gameMode;
public:

    virtual ~SamStartGame();
    explicit SamStartGame(QWidget* parent = nullptr);
    bool formsFull();
};

#endif // SAMSTARTGAME_H
