#pragma once

#ifndef SAMSTACK_H
#define SAMSTACK_H

#include "pch.h"
#include "SamGame.h"
#include "SamStartGame.h"
#include "SamWeb.h"
#include "SamError.h"

enum class CurrentWidget {
    MENU,
    GAME,
    WEB
};

class SamStack : public QStackedWidget {
    friend SamGame;
    friend SamWeb;
    friend SamHost;
    friend SamClient;

    CurrentWidget currWidget;
    bool isFullScreen;
    QApplication* app;
    SamStartGame* startGame;
    SamWeb* web;
    SamGame* game;
    SamError* error;
    SamHost* host;
    SamClient* client;
    bool wasStoppedWeb;
public:

    explicit SamStack(QApplication* app, QWidget* parent = nullptr);
    virtual ~SamStack();
    void init(SamStartGame* startGame, SamGame* game, SamWeb* web);
    void changeWidget(CurrentWidget widget);

    void keyPressEvent(QKeyEvent *event) override;
    void closeEvent(QCloseEvent *event) override;

    void startGameResetState();

    void setNullError();
};

#endif // SAMSTACK_H
