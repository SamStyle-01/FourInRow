#include "SamStack.h"

SamStack::SamStack(QApplication* app, QWidget* parent) : QStackedWidget(parent) {
    this->setWindowTitle("Четыре в ряд");
    this->isFullScreen = false;

    error = nullptr;

    client = nullptr;
    host = nullptr;

    this->app = app;
}

void SamStack::init(SamStartGame* startGame, SamGame* game, SamWeb* web) {
    currWidget = CurrentWidget::MENU;

    this->addWidget(startGame);
    this->addWidget(game);
    this->addWidget(web);

    this->game = game;
    this->startGame = startGame;
    this->web = web;

    this->setCurrentIndex(0);
    this->resize(startGame->width(), startGame->height());
}

void SamStack::changeWidget(CurrentWidget widget) {
    if (this->currWidget == CurrentWidget::MENU && widget == CurrentWidget::GAME) {

        if (this->startGame->formsFull() && (this->startGame->linePlayer1->text() != this->startGame->linePlayer2->text())
            && !((this->startGame->gameMode->getState() != GameMode::CLASSIC) && (this->startGame->player1->checkedId() != 1)
                 && (this->startGame->player2->checkedId() != 1))) {

            this->currWidget = widget;
            this->setCurrentIndex(1);

            if (this->startGame->player1->checkedId() == 1) {
                this->game->setPlayer1(this->startGame->linePlayer1->text(), TypePlayer::HUMAN, this->game->board);
                this->game->isHumanic = true;
            }
            else if (this->startGame->player1->checkedId() == 2) {
                this->game->setPlayer1(this->startGame->linePlayer1->text(), TypePlayer::RANDOM, this->game->board);
            }
            else if (this->startGame->player1->checkedId() == 3) {
                this->game->setPlayer1(this->startGame->linePlayer1->text(), TypePlayer::KARL, this->game->board);
            }
            else if (this->startGame->player1->checkedId() == 4) {
                this->game->setPlayer1(this->startGame->linePlayer1->text(), TypePlayer::STAIRS, this->game->board);
            }
            else if (this->startGame->player1->checkedId() == 5) {
                this->game->setPlayer1(this->startGame->linePlayer1->text(), TypePlayer::ALPHABETA, this->game->board);
            }

            if (this->startGame->player2->checkedId() == 1) {
                this->game->setPlayer2(this->startGame->linePlayer2->text(), TypePlayer::HUMAN, this->game->board);
                this->game->isHumanic = true;
            }
            else if (this->startGame->player2->checkedId() == 2) {
                this->game->setPlayer2(this->startGame->linePlayer2->text(), TypePlayer::RANDOM, this->game->board);
            }
            else if (this->startGame->player2->checkedId() == 3) {
                this->game->setPlayer2(this->startGame->linePlayer2->text(), TypePlayer::KARL, this->game->board);
            }
            else if (this->startGame->player2->checkedId() == 4) {
                this->game->setPlayer2(this->startGame->linePlayer2->text(), TypePlayer::STAIRS, this->game->board);
            }
            else if (this->startGame->player2->checkedId() == 5) {
                this->game->setPlayer2(this->startGame->linePlayer2->text(), TypePlayer::ALPHABETA, this->game->board);
            }

            this->game->currentPlayer = this->game->player1;

            this->game->lblCurrentStep->setText(QString("Ходит:\n") + this->game->getDataPlayer(1));
            if ((dynamic_cast<FourRowHumanPlayer*>(this->game->player1) != nullptr)
                || (dynamic_cast<FourRowHumanPlayer*>(this->game->player2) != nullptr))
                this->game->timer->start(50);
            else
                this->game->timer->start(500);
            this->game->player1Wins = this->game->player2Wins = 0;

            this->game->board->stepsBack.reserve(COLS * ROWS);
            this->game->board->stepsForward.reserve(COLS * ROWS);

            this->game->WinsLosses->setText("1 игрок | 2 игрок\n0 : 0");

            this->game->board->skin1 = *this->startGame->skin1->index - 1;
            this->game->board->skin2 = *this->startGame->skin2->index - 1;
            this->game->board->setCells();
            this->game->gameMode = this->startGame->gameMode->getState();

            if (this->game->gameMode == GameMode::Timer10s || this->game->gameMode == GameMode::Timer30s
                || this->game->gameMode == GameMode::Timer1minAll || this->game->gameMode == GameMode::Timer2minAll)
                this->game->setCommonTimer();

            if (this->game->gameMode == GameMode::Train) {
                this->game->setTrain();
                this->game->isBluredScore = false;
            }
        }
        else if ((this->startGame->gameMode->getState() != GameMode::CLASSIC) && (this->startGame->player1->checkedId() != 1)
                    && (this->startGame->player2->checkedId() != 1) && (this->startGame->player1->checkedId() != -1)
                    && (this->startGame->player2->checkedId() != -1)) {
            error = new SamError("Боты могут играть только в классическом режиме", this, this->startGame);
            this->startGame->grid->addWidget(error, 45, 26, 18, 48);
        }
        else if (this->startGame->linePlayer1->text() == this->startGame->linePlayer2->text() && !this->startGame->linePlayer1->text().isEmpty()) {
            error = new SamError("Имена игроков не могут быть одинаковыми", this, this->startGame);
            this->startGame->grid->addWidget(error, 45, 26, 15, 48);
        }
        else {
            error = new SamError("Вы не завершили ввод данных", this, this->startGame);
            this->startGame->grid->addWidget(error, 45, 26, 15, 48);
        }
    }
    else if (this->currWidget == CurrentWidget::GAME && widget == CurrentWidget::MENU) {
        this->setCurrentIndex(0);
        this->currWidget = widget;
        this->game->timer->stop();
        this->game->resetGame();
        this->game->board->ClearStart();
        this->game->currClue = -1;

        if (this->game->isWeb) {
            this->startGame->boardSize->resetState();
            this->game->isWeb = false;
            if (this->host != nullptr) {
                host->sockDisc();
                delete host;
                host = nullptr;
            }
            if (this->client != nullptr) {
                client->sockDisc();
                delete client;
                client = nullptr;
            }

            this->removeWidget(web);
            delete web;
            web = new SamWeb(this);
            this->addWidget(web);
        }
    }
    else if (this->currWidget == CurrentWidget::MENU && widget == CurrentWidget::WEB) {
        this->setCurrentIndex(2);
        this->currWidget = widget;
        this->web->boardSize->resetState();
    }
    else if (this->currWidget == CurrentWidget::WEB && widget == CurrentWidget::MENU) {
        this->setCurrentIndex(0);
        this->currWidget = widget;
        this->startGame->boardSize->resetState();
    }
    if (this->currWidget == CurrentWidget::WEB && widget == CurrentWidget::GAME) {
        this->currWidget = widget;
        this->setCurrentIndex(1);

        this->game->isHumanic = true;
        if (this->web->HostState) {
            if (this->web->playerNum == 1) {
                this->game->setPlayer1(this->web->playerName->text(), TypePlayer::HUMAN, this->game->board);
                this->game->board->skin1 = this->web->skin_index - 1;

                this->game->setPlayer2(this->host->inputMessage.name, TypePlayer::WEB_HUMAN, this->game->board);
                this->game->board->skin2 = this->host->inputMessage.numSkin - 1;
            }
            else {
                this->game->setPlayer1(this->host->inputMessage.name, TypePlayer::WEB_HUMAN, this->game->board);
                this->game->board->skin1 = this->host->inputMessage.numSkin - 1;

                this->game->board->skin2 = this->web->skin_index - 1;
                this->game->setPlayer2(this->web->playerName->text(), TypePlayer::HUMAN, this->game->board);
            }
        }
        else {
            if (this->client->inputMessage.numStep == 2) {
                this->game->setPlayer1(this->web->playerName->text(), TypePlayer::HUMAN, this->game->board);
                this->game->board->skin1 = this->web->skin_index - 1;

                this->game->setPlayer2(this->client->inputMessage.name, TypePlayer::WEB_HUMAN, this->game->board);
                this->game->board->skin2 = this->client->inputMessage.numSkin - 1;
            }
            else {
                this->game->setPlayer1(this->client->inputMessage.name, TypePlayer::WEB_HUMAN, this->game->board);
                this->game->board->skin1 = this->client->inputMessage.numSkin - 1;

                this->game->board->skin2 = this->web->skin_index - 1;
                this->game->setPlayer2(this->web->playerName->text(), TypePlayer::HUMAN, this->game->board);
            }

            if (this->client->inputMessage.sizeBoard == BoardSizeState::s7x6) {
                ROWS = 7;
                COLS = 6;
            }
            else if (this->client->inputMessage.sizeBoard == BoardSizeState::s8x7) {
                ROWS = 8;
                COLS = 7;
            }
            else if (this->client->inputMessage.sizeBoard == BoardSizeState::s8x8) {
                ROWS = 8;
                COLS = 8;
            }
            else if (this->client->inputMessage.sizeBoard == BoardSizeState::s9x7) {
                ROWS = 9;
                COLS = 7;
            }
            else if (this->client->inputMessage.sizeBoard == BoardSizeState::s9x9) {
                ROWS = 9;
                COLS = 9;
            }
        }

        this->game->currentPlayer = this->game->player1;

        this->game->lblCurrentStep->setText(QString("Ходит:\n") + this->game->getDataPlayer(1));
        this->game->timer->start(50);

        this->game->player1Wins = this->game->player2Wins = 0;

        this->game->board->stepsBack.reserve(COLS * ROWS);
        this->game->board->stepsForward.reserve(COLS * ROWS);

        this->game->WinsLosses->setText("1 игрок | 2 игрок\n0 : 0");

        this->game->board->setCells();
        this->game->gameMode = GameMode::CLASSIC;
        this->game->isWeb = true;
    }
}

void SamStack::keyPressEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key_F11) {
        if (isFullScreen) {
            showNormal();
        } else {
            showFullScreen();
        }
        isFullScreen = !isFullScreen;
    }
    QStackedWidget::keyPressEvent(event);
}

void SamStack::closeEvent(QCloseEvent *event) {
    app->quit();
    if (game->isWeb) {
        if (host != nullptr) {
            host->sendStep(40);
        }
        else if (client != nullptr) {
            client->sendStep(40);
        }
    }
    delete game;
    delete startGame;
    delete web;
    if (error != nullptr) {
        delete error;
    }
    QWidget::closeEvent(event);
}

SamStack::~SamStack() {
    delete game;
    delete startGame;
    delete web;
    if (error != nullptr) {
        delete error;
    }
}
