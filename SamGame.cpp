#include "SamGame.h"
#include "SamStack.h"

SamGame::SamGame(SamStack* stack_) : QWidget{stack_} {
    int height = 530;
    int width = 1000;
    this->setMinimumSize(width, height);
    this->timer = new QTimer(this);

    connect(timer, &QTimer::timeout, this, &SamGame::NextStep);

    gameMode = GameMode::CLASSIC;
    commonTimer = -1;
    stepsToLose = 4;
    timerPl1 = -1;
    timerPl2 = -1;
    lblCommonTimer = nullptr;

    isBluredScore = false;

    isHumanic = false;
    isWeb = false;

    formNextPrevStep = nullptr;
    layoutNextPrevStep = nullptr;

    grid = new QGridLayout();
    grid->setContentsMargins(0, 0, 0, 0);

    background = new QLabel(this);
    QPixmap background_pixmap;
    background->setScaledContents(true);
    background_pixmap.load("./BackgroundGame.png");
    background->setPixmap(background_pixmap);

    board = new SamCellsView(this);

    stepNext = nullptr;
    stepPrev = nullptr;
    clue = nullptr;
    currClue = -1;
    score = nullptr;

    goHome = new QPushButton(this);
    goHome->setFixedSize(65, 65);
    goHome->setIconSize(QSize(55, 55));
    goHome->setIcon(QIcon("./HomePicture.png"));
    goHome->setStyleSheet(
        "QPushButton { border: 2px solid #8f8f91; border-radius: 22px; }"
        "QPushButton:hover { background-color: rgba(150, 200, 251, 180); }"
        "QPushButton:disabled { background-color: rgba(81, 200, 251, 180); }"
        );
    stack = stack_;
    connect(goHome, &QPushButton::clicked, this, [this]() {
        if (isWeb) {
            if (stack->host != nullptr) {
                stack->host->sendStep(40);
            }
            else if (stack->client != nullptr) {
                stack->client->sendStep(40);
            }
        }

        stack->changeWidget(CurrentWidget::MENU);
        board->web_index = -1;
    });

    startNewGame = new QPushButton("Начать\nновую игру", this);
    startNewGame->setFont(QFont("Times New Roman", 18));
    startNewGame->setStyleSheet(
        "QPushButton { border: 2px solid #8f8f91; background-color: rgba(81, 200, 251, 180); border-radius: 15px; }"
        "QPushButton:hover { background-color: rgba(150, 200, 251, 180); }"
        "QPushButton:disabled { background-color: rgba(81, 200, 251, 180); }"
        );
    connect(startNewGame, &QPushButton::clicked, this, [this]() {
        startGameAgain();
        if (isWeb) {
            if (stack->web->HostState) {
                stack->host->sendStep(42);
            }
            else {
                stack->client->sendStep(42);
            }
        }
    });

    player1 = nullptr;
    player2 = nullptr;
    currentPlayer = nullptr;

    lblCurrentStep = new QLabel(this);
    lblCurrentStep->setFont(QFont("Times New Roman", 18));
    lblCurrentStep->setStyleSheet("background-color: rgba(81, 200, 251, 180); border: 2px solid rgba(200, 150, 100, 150); border-radius: 15px;");
    lblCurrentStep->setAlignment(Qt::AlignCenter);

    player1Wins = 0;
    player2Wins = 0;
    WinsLosses = new QLabel(this);
    WinsLosses->setFont(QFont("Times New Roman", 18));
    WinsLosses->setStyleSheet("background-color: rgba(81, 200, 251, 180); border: 2px solid rgba(200, 150, 100, 150); border-radius: 15px;");
    WinsLosses->setAlignment(Qt::AlignCenter);

    this->grid->addWidget(background, 0, 0, 100, 100);
    this->grid->addWidget(board, 1, 14, 98, 66);
    this->grid->addWidget(startNewGame, 10, 80, 20, 19);
    this->grid->addWidget(goHome, 90, 93, 5, 5);
    this->grid->addWidget(lblCurrentStep, 30, 80, 13, 19);
    this->grid->addWidget(WinsLosses, 45, 80, 13, 19);

    this->setLayout(grid);
}

void SamGame::startGameAgain() {
    bGameFinished = false;
    this->board->bVictory = false;
    this->board->index = -2;
    board->web_index = -1;

    board->ClearStart();
    commonTimer = -1;
    timerPl1 = -1;
    timerPl2 = -1;

    WinsLosses->setText("1 игрок | 2 игрок\n0 : 0");

    if (stack->error != nullptr) {
        this->grid->removeWidget(stack->error);
        delete stack->error;
        stack->error = nullptr;
    }

    if (gameMode == GameMode::Train) {
        if (!isBluredScore)
            score->setText("Очки:\n1 игрок: 0\n2 игрок: 0");
        currClue = -1;
    }

    timer->stop();
    if ((dynamic_cast<FourRowHumanPlayer*>(player1) != nullptr) || (dynamic_cast<FourRowHumanPlayer*>(player2) != nullptr))
        timer->start(50);
    else
        timer->start(500);
    currentPlayer = player1;
    lblCurrentStep->setText(QString("Ходит:\n") + getDataPlayer(1));
    WinsLosses->setText("1 игрок | 2 игрок\n" + QString::number(player1Wins) + " : " + QString::number(player2Wins));
    board->setCells();
    board->Show();

    if (lblCommonTimer != nullptr) {
        lblCommonTimer->setStyleSheet("background-color: rgba(81, 200, 251, 180);"
                                      "border: 2px solid rgba(200, 150, 100, 150); border-radius: 15px;");
        if (gameMode == GameMode::Timer10s || gameMode == GameMode::Timer30s)
            lblCommonTimer->setText("Таймер:\n10 секунд");
        else if (gameMode == GameMode::Timer1minAll)
            lblCommonTimer->setText("Таймер:\n1 игрок: 1:00\n2 игрок: 1:00");
        else if (gameMode == GameMode::Timer2minAll)
            lblCommonTimer->setText("Таймер:\n1 игрок: 2:00\n2 игрок: 2:00");
    }
}

void SamGame::getClue() {
    if (!this->board->CheckEndCondition()) {
        if (currClue == -1) {
            CellType cellType, opponentFigure;
            if (this->currentPlayer == player1) {
                cellType = CELLTYPE_X;
                opponentFigure = CELLTYPE_O;
            }
            else {
                cellType = CELLTYPE_O;
                opponentFigure = CELLTYPE_X;
            }

            for (int i = 0; i < COLS; i++) {
                if (this->board->CheckLegal(i)) {
                    this->board->SetCell(i, cellType);
                    if (this->board->CheckEndConditionIter()) {
                        board->bVictory = false;
                        this->board->cols[i]->setOrange();
                        currClue = i;
                        this->board->ClearCell(i);
                        return;
                    }
                    this->board->ClearCell(i);
                }
            }

            for (int i = 0; i < COLS; i++) {
                if (this->board->CheckLegal(i)) {
                    this->board->SetCell(i, opponentFigure);
                    if (this->board->CheckEndConditionIter()) {
                        this->board->ClearCell(i);
                        this->board->SetCell(i, cellType);
                        board->bVictory = false;
                        this->board->cols[i]->setOrange();
                        currClue = i;
                        this->board->ClearCell(i);
                        return;
                    }
                    this->board->ClearCell(i);
                }
            }

            for (int i = 0; i < COLS - 3; i++) {
                if (this->board->CheckLegal(i) && this->board->CheckLegal(i + 3)) {
                    this->board->SetCell(i, opponentFigure);
                    this->board->SetCell(i + 3, opponentFigure);
                    if (this->board->CheckEndConditionIter()) {
                        this->board->ClearCell(i);
                        this->board->ClearCell(i + 3);

                        this->board->SetCell(i, cellType);
                        QPair<int, int> est1 = this->board->getEstimation();
                        int estimation1 = (cellType == CELLTYPE_X) ? est1.first - est1.second : est1.second - est1.first;
                        this->board->ClearCell(i);

                        this->board->SetCell(i + 3, cellType);
                        QPair<int, int> est2 = this->board->getEstimation();
                        int estimation2 = (cellType == CELLTYPE_X) ? est2.first - est2.second : est2.second - est2.first;
                        this->board->ClearCell(i + 3);

                        int final;
                        estimation1 > estimation2 ? final = i: final = i + 3;

                        board->bVictory = false;
                        this->board->cols[final]->setOrange();
                        currClue = final;
                        return;
                    }
                    this->board->ClearCell(i);
                    this->board->ClearCell(i + 3);
                }
            }

            QVector<int> PossibleSteps;
            PossibleSteps.reserve(COLS);
            for (int i = 0; i < COLS; i++) {
                if (this->board->CheckLegal(i)) {
                    this->board->SetCell(i, cellType);
                    if (this->board->CheckLegal(i)) {
                        this->board->SetCell(i, opponentFigure);
                        if (!this->board->CheckEndConditionIter())
                            PossibleSteps.push_back(i);
                        this->board->ClearCell(i);
                    }
                    else PossibleSteps.push_back(i);
                    this->board->ClearCell(i);
                }
            }

            if (!PossibleSteps.size()) {
                for (int i = 0; i < COLS; i++) {
                    PossibleSteps.push_back(i);
                }
            }

            SamLogic* cells = new SamLogic(board->getCells());
            AlphaBetaTree tree(cells, cellType, PossibleSteps);

            int col = tree.getNextMove();

            this->board->cols[col]->setOrange();
            currClue = col;
        }
        else {
            this->board->cols[currClue]->setDefault();
            currClue = -1;
        }
    }
}

void SamGame::setCommonTimer() {
    lblCommonTimer = new QLabel(this);

    if (gameMode == GameMode::Timer10s) {
        lblCommonTimer->setText("Таймер:\n10 секунд");
    }
    else if (gameMode == GameMode::Timer30s) {
        lblCommonTimer->setText("Таймер:\n30 секунд");
    }
    else if (gameMode == GameMode::Timer1minAll) {
        lblCommonTimer->setText("Таймер:\n1 игрок: 1:00\n2 игрок: 1:00");
        lblCommonTimer->setMinimumHeight(90);
    }
    else if (gameMode == GameMode::Timer2minAll) {
        lblCommonTimer->setText("Таймер:\n1 игрок: 2:00\n2 игрок: 2:00");
        lblCommonTimer->setMinimumHeight(90);
    }

    lblCommonTimer->setFont(QFont("Times New Roman", 18));
    lblCommonTimer->setStyleSheet("background-color: rgba(81, 200, 251, 180); border: 2px solid rgba(200, 150, 100, 150); border-radius: 15px;");
    lblCommonTimer->setAlignment(Qt::AlignCenter);

    this->grid->addWidget(lblCommonTimer, 60, 80, 13, 19);
}

void SamGame::setTrain() {
    formNextPrevStep = new QWidget(this);
    layoutNextPrevStep = new QGridLayout(formNextPrevStep);

    stepNext = new QPushButton(formNextPrevStep);
    stepPrev = new QPushButton(formNextPrevStep);
    clue = new QPushButton(formNextPrevStep);

    stepNext->setIcon(QIcon("./StepNext.png"));
    stepPrev->setIcon(QIcon("./stepPrevious.png"));
    clue->setIcon(QIcon("./Clue.png"));

    clue->setFixedSize(70, 70);
    clue->setIconSize(QSize(60, 60));
    clue->setStyleSheet(
        "QPushButton { border: 2px solid #8f8f91; border-radius: 22px; }"
        "QPushButton:hover { background-color: rgba(150, 200, 251, 180); }"
        "QPushButton:disabled { background-color: rgba(81, 200, 251, 180); }"
        );
    connect(clue, &QPushButton::clicked, this, [this]() {
        getClue();
    });

    stepNext->setFixedSize(70, 70);
    stepNext->setIconSize(QSize(60, 60));
    stepNext->setStyleSheet(
        "QPushButton { border: 2px solid #8f8f91; border-radius: 22px; }"
        "QPushButton:hover { background-color: rgba(150, 200, 251, 180); }"
        "QPushButton:disabled { background-color: rgba(81, 200, 251, 180); }"
        );
    connect(stepNext, &QPushButton::clicked, this, [this]() {
        stepForward();

        if (currClue != -1) {
            this->board->cols[currClue]->setDefault();
            currClue = -1;
        }

        if (dynamic_cast<FourRowHumanPlayer*>(currentPlayer) == nullptr) {
            stepForward();
        }

        if (!isBluredScore) {
            QPair<int, int> scorePlayers = board->getEstimation();
            this->score->setText("Очки:\n1 игрок: " + QString::number(scorePlayers.first) + "\n2 игрок: " + QString::number(scorePlayers.second));
        }
    });

    stepPrev->setFixedSize(70, 70);
    stepPrev->setIconSize(QSize(60, 60));
    stepPrev->setStyleSheet(
        "QPushButton { border: 2px solid #8f8f91; border-radius: 22px; }"
        "QPushButton:hover { background-color: rgba(150, 200, 251, 180); }"
        "QPushButton:disabled { background-color: rgba(81, 200, 251, 180); }"
        );
    connect(stepPrev, &QPushButton::clicked, this, [this]() {
        bool condition = false;
        if (dynamic_cast<FourRowHumanPlayer*>(player1) == nullptr) condition = true;

        if (!condition || !board->oneOnBoard()) {
            stepBack();

            if (currClue != -1) {
                this->board->cols[currClue]->setDefault();
                currClue = -1;
            }

            if (dynamic_cast<FourRowHumanPlayer*>(currentPlayer) == nullptr) {
                stepBack();
            }

            if ((dynamic_cast<FourRowHumanPlayer*>(player1) != nullptr) || (dynamic_cast<FourRowHumanPlayer*>(player2) != nullptr))
                timer->start(50);
            else
                timer->start(500);

            if (!isBluredScore) {
                QPair<int, int> scorePlayers = board->getEstimation();
                this->score->setText("Очки:\n1 игрок: " + QString::number(scorePlayers.first) + "\n2 игрок: " + QString::number(scorePlayers.second));
            }
        }
    });

    score = new QLabel("Очки:\n1 игрок: 0\n2 игрок: 0", this);
    score->setFont(QFont("Times New Roman", 16));
    score->setAlignment(Qt::AlignCenter);
    score->setStyleSheet("background-color: rgba(81, 200, 251, 180); border: 2px solid rgba(200, 150, 100, 150); border-radius: 15px;");

    blurScore = new QPushButton(score);
    blurScore->setIconSize(QSize(60, 60));
    blurScore->setIcon(QIcon("./OpenedEye.png"));
    blurScore->setStyleSheet(
        "QPushButton { background-color: rgba(255, 255, 255, 0); border: 1px solid rgba(255, 255, 255, 0); }"
        );
    connect(blurScore, &QPushButton::clicked, this, [this]() {
        if (!isBluredScore) {
            blurScore->setIcon(QIcon("./ClosedEye.png"));
            score->setText("");

            score->setStyleSheet("background-color: rgba(125, 175, 200, 255); border: 2px solid rgba(200, 150, 100, 150); border-radius: 15px;");
        }
        else {
            blurScore->setIcon(QIcon("./OpenedEye.png"));
            QPair<int, int> scorePlayers = board->getEstimation();
            this->score->setText("Очки:\n1 игрок: " + QString::number(scorePlayers.first) + "\n2 игрок: " + QString::number(scorePlayers.second));
            score->setStyleSheet("background-color: rgba(81, 200, 251, 180); border: 2px solid rgba(200, 150, 100, 150); border-radius: 15px;");
        }
        isBluredScore = !isBluredScore;
    });

    layoutNextPrevStep->addWidget(clue, 0, 0);
    layoutNextPrevStep->addWidget(stepPrev, 0, 1);
    layoutNextPrevStep->addWidget(stepNext, 0, 2);
    formNextPrevStep->setLayout(layoutNextPrevStep);
    formNextPrevStep->setStyleSheet("margin-left: 4px;");

    this->grid->addWidget(blurScore, 60, 94, 5, 5);
    this->grid->addWidget(score, 59, 80, 15, 19);
    this->grid->addWidget(formNextPrevStep, 74, 79, 15, 21);
}

void SamGame::setPlayer1(QString name, TypePlayer type, SamCellsView* board) {
    switch (type) {
    case TypePlayer::HUMAN:
        this->player1 = new FourRowHumanPlayer();
        break;
    case TypePlayer::WEB_HUMAN:
        this->player1 = new FourRowWebPlayer();
        break;
    case TypePlayer::RANDOM:
        this->player1 = new FourRowRandomPlayer();
        break;
    case TypePlayer::KARL:
        this->player1 = new FourRowKarlPlayer();
        break;
    case TypePlayer::STAIRS:
        this->player1 = new FourRowStairs();
        break;
    case TypePlayer::ALPHABETA:
        this->player1 = new FourRowAI();
        break;
    }
    player1->SetupPlayer(name, CELLTYPE_X);
    player1->SetBoard(board);
}

void SamGame::setPlayer2(QString name, TypePlayer type, SamCellsView* board) {
    switch (type) {
    case TypePlayer::HUMAN:
        this->player2 = new FourRowHumanPlayer();
        break;
    case TypePlayer::WEB_HUMAN:
        this->player2 = new FourRowWebPlayer();
        break;
    case TypePlayer::RANDOM:
        this->player2 = new FourRowRandomPlayer();
        break;
    case TypePlayer::KARL:
        this->player2 = new FourRowKarlPlayer();
        break;
    case TypePlayer::STAIRS:
        this->player2 = new FourRowStairs();
        break;
    case TypePlayer::ALPHABETA:
        this->player2 = new FourRowAI();
        break;
    }
    player2->SetupPlayer(name, CELLTYPE_O);
    player2->SetBoard(board);
}

QString SamGame::getDataPlayer(int index) const {
    if (index == 1) {
        return player1->GetName();
    }
    else if (index == 2) {
        return player2->GetName();
    }
    return "";
}

void SamGame::ShowBoard() const {
    this->board->Show();
}

void SamGame::MakeMove() {
    int variant = currentPlayer->MakeMove();
    if (!variant) {
        stack->error = new SamError("Недопустимый ход, попробуйте ещё раз", stack, this);
        this->grid->addWidget(stack->error, 45, 26, 15, 48);

        this->board->index = -2;
        this->ShowBoard();
        return;
    }
    if (variant == 1) {
        if (gameMode == GameMode::Timer10s) {
            commonTimer = 0;
            this->lblCommonTimer->setStyleSheet("background-color: rgba(81, 200, 251, 180);"
                                                "border: 2px solid rgba(200, 150, 100, 150); border-radius: 15px;");
            lblCommonTimer->setText("Таймер:\n10 секунд");
            stepsToLose = 4;
        }
        else if (gameMode == GameMode::Timer30s) {
            commonTimer = 0;
            this->lblCommonTimer->setStyleSheet("background-color: rgba(81, 200, 251, 180);"
                                                "border: 2px solid rgba(200, 150, 100, 150); border-radius: 15px;");
            lblCommonTimer->setText("Таймер:\n30 секунд");
            stepsToLose = 4;
        }
        else if (gameMode == GameMode::Timer1minAll || gameMode == GameMode::Timer2minAll) {
            if (timerPl1 == -1 && timerPl2 == -1) {
                timerPl1 = timerPl2 = 0;
            }
        }
        else if (gameMode == GameMode::Train) {
            if (!isBluredScore) {
                QPair<int, int> scorePlayers = board->getEstimation();
                this->score->setText("Очки:\n1 игрок: " + QString::number(scorePlayers.first) + "\n2 игрок: " + QString::number(scorePlayers.second));
            }
            if (currClue != -1) {
                this->board->cols[currClue]->setDefault();
                currClue = -1;
            }
        }
        if (this->board->CheckEndCondition()) {
            ShowBoard();
            if (this->board->IsVictory()) {
                currentPlayer == player1 ? wins.push(1) : wins.push(2);

                if (wins.top() == 1)
                    player1Wins++;
                else if (wins.top() == 2)
                    player2Wins++;

                WinsLosses->setText("1 игрок | 2 игрок\n" + QString::number(player1Wins) + " : " + QString::number(player2Wins));
                stack->error = new SamError("Игрок " + currentPlayer->GetName() + " победил!", stack, this);
                this->grid->addWidget(stack->error, 45, 26, 15, 48);
            }
            else {
                wins.push(3);
                player1Wins++;
                player2Wins++;
                WinsLosses->setText("1 игрок | 2 игрок\n" + QString::number(player1Wins) + " : " + QString::number(player2Wins));
                stack->error = new SamError("Объявлена ничья!", stack, this);
                this->grid->addWidget(stack->error, 45, 26, 15, 48);
            }
            this->bGameFinished = true;
            currentPlayer = (currentPlayer == player1) ? player2 : player1;
            if (isWeb && this->board->index >= 0) {
                if (stack->web->HostState) {
                    stack->host->sendStep(this->board->index);
                }
                else {
                    stack->client->sendStep(this->board->index);
                }
            }
            return;
        }
        currentPlayer = (currentPlayer == player1) ? player2 : player1;
        this->lblCurrentStep->setText("Ходит:\n" + currentPlayer->GetName());
        this->ShowBoard();
    }

    if (isWeb && this->board->index >= 0) {
        if (stack->web->HostState) {
            stack->host->sendStep(this->board->index);
        }
        else {
            stack->client->sendStep(this->board->index);
        }
    }
    this->board->index = -2;
    this->board->web_index = -1;
}

bool SamGame::IsGameFinished() {
    return bGameFinished;
}

void SamGame::NextStep() {
    if (!IsGameFinished()) {
        if (gameMode == GameMode::Timer10s && commonTimer != -1) {
            commonTimer++;
            lblCommonTimer->setText("Таймер:\n" + QString::number(10 - commonTimer / 20) + " секунд");
            lblCommonTimer->setStyleSheet("background-color: rgba(" + QString::number(81 + 17 * commonTimer / 20) + ", "
                                          + QString::number(200 - 12 * commonTimer / 20) + ", " + QString::number(251 - 12 * commonTimer / 20)
                                          + ", 180);"
                                            "border: 2px solid rgba(200, 150, 100, 150); border-radius: 15px;");
            if (commonTimer >= 200) {
                currentPlayer = (currentPlayer == player1) ? player2 : player1;
                commonTimer = 0;
                this->lblCurrentStep->setText("Ходит:\n" + currentPlayer->GetName());
                this->lblCommonTimer->setStyleSheet("background-color: rgba(81, 200, 251, 180);"
                                                    "border: 2px solid rgba(200, 150, 100, 150); border-radius: 15px;");
                lblCommonTimer->setText("Таймер:\n10 секунд");
                stepsToLose--;
                this->ShowBoard();
                if (!stepsToLose) {
                    this->bGameFinished = true;
                    stack->error = new SamError("Игрок " + (currentPlayer == player1 ?
                                                                player2->GetName() : player1->GetName()) + " победил!", stack, this);
                    this->grid->addWidget(stack->error, 45, 26, 15, 48);

                    currentPlayer == player1 ? player2Wins++ : player1Wins++;
                    WinsLosses->setText("1 игрок | 2 игрок\n" + QString::number(player1Wins) + " : " + QString::number(player2Wins));
                }
            }
        }
        else if (gameMode == GameMode::Timer30s && commonTimer != -1) {
            commonTimer++;
            lblCommonTimer->setText("Таймер:\n" + QString::number(30 - commonTimer / 20) + " секунд");

            lblCommonTimer->setStyleSheet("background-color: rgba(" + QString::number(81 + std::min(6 * commonTimer / 20, 174)) + ", "
                                          + QString::number(200 - 4 * commonTimer / 20) + ", " + QString::number(251 - 4 * commonTimer / 20)
                                          + ", 180);"
                                          "border: 2px solid rgba(200, 150, 100, 150); border-radius: 15px;");
            if (commonTimer >= 600) {
                currentPlayer = (currentPlayer == player1) ? player2 : player1;
                this->lblCurrentStep->setText("Ходит:\n" + currentPlayer->GetName());
                this->lblCommonTimer->setStyleSheet("background-color: rgba(81, 200, 251, 180);"
                                                    "border: 2px solid rgba(200, 150, 100, 150); border-radius: 15px;");
                lblCommonTimer->setText("Таймер:\n30 секунд");
                stepsToLose--;
                this->ShowBoard();
                if (!stepsToLose) {
                    this->bGameFinished = true;
                    stack->error = new SamError("Игрок " + (currentPlayer == player1 ?
                                                                          player2->GetName() : player1->GetName()) + " победил!", stack, this);
                    this->grid->addWidget(stack->error, 45, 26, 15, 48);

                    currentPlayer == player1 ? player2Wins++ : player1Wins++;
                    WinsLosses->setText("1 игрок | 2 игрок\n" + QString::number(player1Wins) + " : " + QString::number(player2Wins));
                }
            }
        }
        else if (gameMode == GameMode::Timer1minAll && timerPl1 != -1 && timerPl2 != -1) {
            if (currentPlayer == player1) {
                timerPl1++;
            }
            else if (currentPlayer == player2) {
                timerPl2++;
            }

            lblCommonTimer->setText("Таймер:\n1 игрок: " + QString::number((60 - timerPl1 / 20) / 60) + ":" + ((60 - timerPl1 / 20) % 60 < 10 ? "0" : "") + QString::number((60 - timerPl1 / 20) % 60)
                    + "\n2 игрок: " + QString::number((60 - timerPl2 / 20) / 60) + ":" + ((60 - timerPl2 / 20) % 60 < 10 ? "0" : "") + QString::number((60 - timerPl2 / 20) % 60));

            if (!(timerPl1 - 1200) || !(timerPl2 - 1200)) {
                this->bGameFinished = true;
                stack->error = new SamError("Игрок " + (currentPlayer == player1 ? player2->GetName() : player1->GetName())
                                                + " победил!", stack, this);
                this->grid->addWidget(stack->error, 45, 26, 15, 48);

                currentPlayer == player1 ? player2Wins++ : player1Wins++;
                WinsLosses->setText("1 игрок | 2 игрок\n" + QString::number(player1Wins) + " : " + QString::number(player2Wins));
            }
        }
        else if (gameMode == GameMode::Timer2minAll && timerPl1 != -1 && timerPl2 != -1) {
            if (currentPlayer == player1) {
                timerPl1++;
            }
            else if (currentPlayer == player2) {
                timerPl2++;
            }

            lblCommonTimer->setText("Таймер:\n1 игрок: " + QString::number((120 - timerPl1 / 20) / 60) + ":" + ((120 - timerPl1 / 20) % 60 < 10 ? "0" : "") + QString::number((120 - timerPl1 / 20) % 60)
                    + "\n2 игрок: " + QString::number((120 - timerPl2 / 20) / 60) + ":" + ((120 - timerPl2 / 20) % 60 < 10 ? "0" : "") + QString::number((120 - timerPl2 / 20) % 60));

            if (!(timerPl1 - 2400) || !(timerPl2 - 2400)) {
                this->bGameFinished = true;
                stack->error = new SamError("Игрок " + (currentPlayer == player1 ? player2->GetName() : player1->GetName())
                                                + " победил!", stack, this);
                this->grid->addWidget(stack->error, 45, 26, 15, 48);

                currentPlayer == player1 ? player2Wins++ : player1Wins++;
                WinsLosses->setText("1 игрок | 2 игрок\n" + QString::number(player1Wins) + " : " + QString::number(player2Wins));
            }
        }
        MakeMove();
    }
    else timer->stop();
}

void SamGame::stepBack() {
    if (!this->board->stepsBack.isEmpty()) {
        this->board->ClearCell(this->board->stepsBack.top());
        this->board->stepsForward.push(this->board->stepsBack.top());
        this->board->stepsBack.pop();

        currentPlayer = (currentPlayer == player1) ? player2 : player1;
        this->board->index = -1;

        if (bGameFinished) {
            board->bVictory = false;
            bGameFinished = false;

            if (this->board->line != nullptr) {
                this->board->line->DisActivate();
                this->board->fieldLayout->removeWidget(this->board->line);
            }

            switch (wins.top()) {
            case 1:
                player1Wins--;
                break;
            case 2:
                player2Wins--;
                break;
            case 3:
                player1Wins--;
                player2Wins--;
                break;
            }

            WinsLosses->setText("1 игрок | 2 игрок\n" + QString::number(player1Wins) + " : " + QString::number(player2Wins));
        }

        this->board->Show();
    }
}

void SamGame::stepForward() {
    if (!this->board->stepsForward.isEmpty()) {
        this->board->SetCell(this->board->stepsForward.top(), (currentPlayer == player1) ? CellType::CELLTYPE_X : CellType::CELLTYPE_O);
        this->board->stepsBack.push(this->board->stepsForward.top());
        this->board->stepsForward.pop();

        currentPlayer = (currentPlayer == player1) ? player2 : player1;

        this->board->index = -1;

        if (this->board->CheckEndCondition()) {
            ShowBoard();
            if (this->wins.top() == 1) {
                player1Wins++;
                this->board->bVictory = true;
            }
            else if (this->wins.top() == 2) {
                player2Wins++;
                this->board->bVictory = true;
            }
            else {
                player1Wins++;
                player2Wins++;
            }
            WinsLosses->setText("1 игрок | 2 игрок\n" + QString::number(player1Wins) + " : " + QString::number(player2Wins));
            this->bGameFinished = true;
            return;
        }

        this->board->Show();
    }
}

void SamGame::resetGame() {
    bGameFinished = false;
    this->board->index = -2;
    delete player1;
    delete player2;
    player1 = nullptr;
    player2 = nullptr;
    commonTimer = -1;
    timerPl1 = -1;
    timerPl2 = -1;
    if (stack->error != nullptr) {
        this->grid->removeWidget(stack->error);
        delete stack->error;
        stack->error = nullptr;
    }
    if (stepNext != nullptr) {
        grid->removeWidget(stepNext);
        delete stepNext;
        stepNext = nullptr;

        grid->removeWidget(stepPrev);
        delete stepPrev;
        stepPrev = nullptr;

        delete clue;
        currClue = -1;
        clue = nullptr;

        grid->removeWidget(formNextPrevStep);
        delete layoutNextPrevStep;
        delete formNextPrevStep;
        layoutNextPrevStep = nullptr;
        formNextPrevStep = nullptr;

        grid->removeWidget(score);
        grid->removeWidget(blurScore);
        delete blurScore;
        delete score;
        score = nullptr;
        blurScore = nullptr;
    }
    if (lblCommonTimer != nullptr) {
        grid->removeWidget(lblCommonTimer);
        delete lblCommonTimer;
        lblCommonTimer = nullptr;
    }
}

SamGame::~SamGame() {
    if (player1 != nullptr) {
        delete player1;
        delete player2;
    }

    delete board;
    delete lblCurrentStep;

    delete timer;
    delete background;
    delete grid;
    delete startNewGame;
    if (lblCommonTimer != nullptr) delete lblCommonTimer;
    if (stepNext != nullptr) {
        delete stepNext;
        delete stepPrev;
        delete clue;

        delete formNextPrevStep;
        delete layoutNextPrevStep;
        delete blurScore;
        delete score;
    }
}
