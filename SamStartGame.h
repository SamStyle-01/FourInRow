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
private:
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
public:
    SamBoardSize* boardSize;
    QGridLayout* grid;
    virtual ~SamStartGame();
    QLineEdit* linePlayer1;
    QLineEdit* linePlayer2;
    QButtonGroup* player1;
    QButtonGroup* player2;
    explicit SamStartGame(QWidget* parent = nullptr);
    bool formsFull();

    SamSkinButton* skin1;
    SamSkinButton* skin2;

    int skinIndexes[2];

    GameModeButton* gameMode;
};

#endif // SAMSTARTGAME_H
