#include "SamWeb.h"
#include "SamStack.h"
#include "SamStack.h"

SamWeb::SamWeb(SamStack *parent) : QWidget{parent} {
    this->stack = parent;
    int height = 630;
    int width = 1100;
    this->setMinimumSize(width, height);

    playerNum = 1;

    SamStack* stack = reinterpret_cast<SamStack*>(this->parentWidget());
    background = new QLabel(this);
    QPixmap background_pixmap("./WebBackground.png");
    background->setScaledContents(true);
    background->setPixmap(background_pixmap);

    webGameLbl = new QLabel("Сетевая игра", this);
    webGameLbl->setFont(QFont("Times New Roman", 28));
    webGameLbl->setAlignment(Qt::AlignCenter);
    webGameLbl->setStyleSheet("background-color: rgba(255, 175, 175, 180); border: 2px solid rgba(220, 220, 220, 200); border-radius: 15px;");

    back = new QPushButton("Назад", this);
    back->setStyleSheet(
        "QPushButton { background-color: rgba(255, 175, 175, 180); border: 2px solid rgba(220, 220, 220, 200); border-radius: 10px; }"
        "QPushButton:hover { background-color: rgba(255, 135, 135, 180); }"
        "QPushButton:disabled { background-color: rgba(255, 175, 175, 180); }"
        );
    back->setFont(QFont("Times New Roman", 20));
    connect(back, &QPushButton::clicked, this, [stack]() {
        stack->changeWidget(CurrentWidget::MENU);
    });

    start = nullptr;

    grid = new QGridLayout(this);
    grid->setContentsMargins(0, 0, 0, 0);

    space = new QLabel();
    space->setAttribute(Qt::WA_TransparentForMouseEvents);
    space->setStyleSheet("background-color: none; border: none;");

    frame = new QWidget(this);
    frame->setStyleSheet("background-color: rgba(255, 175, 175, 180); border: 2px solid rgba(220, 220, 220, 200); border-radius: 15px;");

    gridInFrame = new QGridLayout(frame);
    isHost = new QPushButton("Хостить", frame);
    connect(isHost, &QPushButton::clicked, this, [this]() {
        this->HostOrConnect();
    });
    HostState = true;
    isHost->setStyleSheet(
        "QPushButton { background-color: rgba(255, 175, 175, 180); border: 2px solid rgba(220, 220, 220, 200); border-radius: 10px; }"
        "QPushButton:hover { background-color: rgba(255, 135, 135, 180); }"
        "QPushButton:disabled { background-color: rgba(255, 175, 175, 180); }"
        );
    isHost->setFont(QFont("Times New Roman", 25));

    playerFrame = new QWidget(this);
    playerGrid = new QGridLayout(playerFrame);

    playerLbl = new QLabel("Игрок", playerFrame);
    playerLbl->setMaximumHeight(60);
    playerLbl->setAlignment(Qt::AlignCenter);
    playerLbl->setFont(QFont("Times New Roman", 20));

    playerName = new QLineEdit(playerFrame);
    playerName->setAlignment(Qt::AlignCenter);
    playerName->setPlaceholderText("Введите имя");
    playerName->setFont(QFont("Times New Roman", 20));

    skin_index = 1;
    skin = new SamSkinButton(&skin_index, playerFrame);

    playerNumBtn = new QPushButton("1", this);
    playerNumBtn->setFont(QFont("Times New Roman", 20));
    playerNumBtn->setMinimumHeight(60);
    playerNumBtn->setStyleSheet(
        "QPushButton { background-color: rgba(255, 175, 175, 180); border: 2px solid rgba(220, 220, 220, 200); border-radius: 10px; }"
        "QPushButton:hover { background-color: rgba(255, 135, 135, 180); }"
        "QPushButton:disabled { background-color: rgba(255, 175, 175, 180); }"
        );
    connect(playerNumBtn, &QPushButton::clicked, this, [this]() {
        playerNum = (playerNum == 1 ? 2 : 1);
        playerNumBtn->setText(QString::number(playerNum));
    });

    stack->host = nullptr;
    stack->client = nullptr;

    onConnection = new QPushButton("Ожидать игрока", this);
    onConnection->setFont(QFont("Times New Roman", 20));
    onConnection->setMinimumHeight(50);
    onConnection->setStyleSheet(
        "QPushButton { background-color: rgba(255, 175, 175, 180); border: 2px solid rgba(220, 220, 220, 200); border-radius: 10px; }"
        "QPushButton:hover { background-color: rgba(255, 135, 135, 180); }"
        "QPushButton:disabled { background-color: rgba(255, 175, 175, 180); }"
        );
    connect(onConnection, &QPushButton::clicked, this, [this, stack]() {
        if (ipShowLbl == nullptr) {
            if (playerName->text() == "") {
                this->stack->error = new SamError("Заполните все поля", this->stack, this);
                this->grid->addWidget(this->stack->error, 45, 26, 15, 48);
            }
            else {
                stack->host = new SamHost(stack);
                onConnection->setText("Закончить ожидание");

                stack->host->startServer();

                ipShowLbl = new QLabel("IP:", this);
                ipShowLbl->setMaximumHeight(50);
                ipShowLbl->setAlignment(Qt::AlignCenter);
                ipShowLbl->setFont(QFont("Times New Roman", 20));

                ipShow = new QLineEdit(stack->host->serverAddress().toString() == "127.0.0.1" ?
                                           "Нет соединения с интернетом" : stack->host->serverAddress().toString(), this);
                ipShow->setMaximumHeight(50);
                ipShow->setAlignment(Qt::AlignCenter);
                ipShow->setFont(QFont("Times New Roman", 20));
                ipShow->setReadOnly(true);

                gridInFrame->addWidget(ipShowLbl, 65, 0, 30, 20);
                gridInFrame->addWidget(ipShow, 65, 20, 30, 80);
            }
        }
        else {
            stack->host->sockDisc();
            delete stack->host;
            stack->host = nullptr;

            onConnection->setText("Ожидать игрока");
            if (ipShowLbl != nullptr) {
                gridInFrame->removeWidget(ipShow);
                gridInFrame->removeWidget(ipShowLbl);

                delete ipShow;
                delete ipShowLbl;

                ipShow = nullptr;
                ipShowLbl = nullptr;
            }
        }
    });

    boardSize = new SamBoardSize(this);
    boardSize->setStyleSheet(
        "QPushButton { background-color: rgba(255, 175, 175, 180); border: 2px solid rgba(220, 220, 220, 200); border-radius: 10px; }"
        "QPushButton:hover { background-color: rgba(255, 135, 135, 180); }"
        "QPushButton:disabled { background-color: rgba(255, 175, 175, 180); }"
        );

    playerGrid->addWidget(playerLbl, 0, 0, 11, 83);
    playerGrid->addWidget(playerNumBtn, 0, 83, 11, 10);
    playerGrid->addWidget(skin, 0, 93, 11, 7);
    playerGrid->addWidget(playerName, 13, 0, 10, 100);
    playerGrid->addWidget(boardSize, 25, 0, 10, 100);

    playerFrame->setLayout(playerGrid);

    gridInFrame->addWidget(space, 0, 0, 100, 100);
    gridInFrame->addWidget(isHost, 0, 0, 10, 100);
    gridInFrame->addWidget(playerFrame, 15, 0, 30, 100);
    gridInFrame->addWidget(onConnection, 50, 0, 13, 100);

    frame->setLayout(gridInFrame);

    ipAddress = nullptr;
    clientLabel = nullptr;
    connectFrame = nullptr;
    connectLayout = nullptr;
    ipShow = nullptr;
    ipShowLbl = nullptr;

    this->grid->addWidget(background, 0, 0, 100, 100);
    this->grid->addWidget(webGameLbl, 7, 37, 8, 26);
    this->grid->addWidget(frame, 17, 15, 70, 70);
    this->grid->addWidget(back, 89, 2, 10, 20);

    this->setLayout(grid);
}

void SamWeb::HostOrConnect() {
    if (HostState) {
        HostState = false;
        isHost->setText("Подключиться");
        isHost->setStyleSheet(
            "QPushButton { background-color: rgba(175, 175, 255, 180); border: 2px solid rgba(220, 220, 220, 200); border-radius: 10px; }"
            "QPushButton:hover { background-color: rgba(135, 135, 255, 180); }"
            "QPushButton:disabled { background-color: rgba(175, 175, 255, 180); }"
            );

        frame->setStyleSheet("background-color: rgba(175, 175, 255, 180); border: 2px solid rgba(220, 220, 220, 200); border-radius: 15px;");

        webGameLbl->setStyleSheet("background-color: rgba(175, 175, 255, 180); border: 2px solid rgba(220, 220, 220, 200); border-radius: 15px;");

        back->setStyleSheet(
            "QPushButton { background-color: rgba(175, 175, 255, 180); border: 2px solid rgba(220, 220, 220, 200); border-radius: 10px; }"
            "QPushButton:hover { background-color: rgba(135, 135, 255, 180); }"
            "QPushButton:disabled { background-color: rgba(175, 175, 255, 180); }"
            );

        start = new QPushButton("Начать игру", this);
        start->setStyleSheet(
            "QPushButton { background-color: rgba(175, 175, 255, 180); border: 2px solid rgba(220, 220, 220, 200); border-radius: 10px; }"
            "QPushButton:hover { background-color: rgba(135, 135, 255, 180); }"
            "QPushButton:disabled { background-color: rgba(175, 175, 255, 180); }"
            );
        start->setFont(QFont("Times New Roman", 20));
        connect(start, &QPushButton::clicked, this, [this]() {
            stack->client->startConnection(ipAddress->text());
        });
        this->grid->addWidget(start, 89, 78, 10, 20);

        connectFrame = new QWidget();
        connectLayout = new QVBoxLayout(connectFrame);

        clientLabel = new QLabel("Введите IP-адрес хоста", connectFrame);
        clientLabel->setStyleSheet("background-color: none; border: none;");
        clientLabel->setAlignment(Qt::AlignCenter);
        clientLabel->setFont(QFont("Times New Roman", 20));
        clientLabel->setMaximumHeight(60);
        ipAddress = new QLineEdit(connectFrame);
        ipAddress->setAlignment(Qt::AlignCenter);
        ipAddress->setFont(QFont("Times New Roman", 20));
        ipAddress->setPlaceholderText("IP");

        stack->client = new SamClient(stack);
        delete stack->host;
        stack->host = nullptr;

        playerGrid->removeWidget(boardSize);
        delete boardSize;
        stack->startGameResetState();

        playerGrid->removeWidget(playerNumBtn);
        delete playerNumBtn;
        playerNumBtn = nullptr;

        playerGrid->removeWidget(onConnection);
        delete onConnection;
        onConnection = nullptr;

        if (ipShowLbl != nullptr) {
            gridInFrame->removeWidget(ipShow);
            gridInFrame->removeWidget(ipShowLbl);

            delete ipShow;
            delete ipShowLbl;

            ipShow = nullptr;
            ipShowLbl = nullptr;
        }

        playerGrid->addWidget(playerLbl, 0, 0, 11, 93);

        connectLayout->addWidget(clientLabel);
        connectLayout->addWidget(ipAddress);
        connectFrame->setLayout(connectLayout);

        gridInFrame->addWidget(connectFrame, 50, 0, 28, 100);
    }
    else {
        HostState = true;
        isHost->setText("Хостить");
        isHost->setStyleSheet(
            "QPushButton { background-color: rgba(255, 175, 175, 180); border: 2px solid rgba(220, 220, 220, 200); border-radius: 10px; }"
            "QPushButton:hover { background-color: rgba(255, 135, 135, 180); }"
            "QPushButton:disabled { background-color: rgba(255, 175, 175, 180); }"
            );

        frame->setStyleSheet("background-color: rgba(255, 175, 175, 180); border: 2px solid rgba(220, 220, 220, 200); border-radius: 15px;");

        back->setStyleSheet(
            "QPushButton { background-color: rgba(255, 175, 175, 180); border: 2px solid rgba(220, 220, 220, 200); border-radius: 10px; }"
            "QPushButton:hover { background-color: rgba(255, 135, 135, 180); }"
            "QPushButton:disabled { background-color: rgba(255, 175, 175, 180); }"
            );

        grid->removeWidget(start);
        delete start;
        start = nullptr;

        webGameLbl->setStyleSheet("background-color: rgba(255, 175, 175, 180); border: 2px solid rgba(220, 220, 220, 200); border-radius: 15px;");

        gridInFrame->removeWidget(connectFrame);

        playerNumBtn = new QPushButton("1", this);
        playerNumBtn->setFont(QFont("Times New Roman", 20));
        playerNumBtn->setFixedHeight(50);
        playerNumBtn->setStyleSheet(
            "QPushButton { background-color: rgba(255, 175, 175, 180); border: 2px solid rgba(220, 220, 220, 200); border-radius: 10px; }"
            "QPushButton:hover { background-color: rgba(255, 135, 135, 180); }"
            "QPushButton:disabled { background-color: rgba(255, 175, 175, 180); }"
            );
        connect(playerNumBtn, &QPushButton::clicked, this, [this]() {
            playerNum = (playerNum == 1 ? 2 : 1);
            playerNumBtn->setText(QString::number(playerNum));
        });

        boardSize = new SamBoardSize(this);
        boardSize->setStyleSheet(
            "QPushButton { background-color: rgba(255, 175, 175, 180); border: 2px solid rgba(220, 220, 220, 200); border-radius: 10px; }"
            "QPushButton:hover { background-color: rgba(255, 135, 135, 180); }"
            "QPushButton:disabled { background-color: rgba(255, 175, 175, 180); }"
            );
        boardSize->resetState();

        playerGrid->addWidget(playerLbl, 0, 0, 11, 83);
        playerGrid->addWidget(playerNumBtn, 0, 83, 11, 10);
        playerGrid->addWidget(skin, 0, 93, 11, 7);
        playerGrid->addWidget(boardSize, 25, 0, 10, 100);

        onConnection = new QPushButton("Ожидать игрока", this);
        onConnection->setFont(QFont("Times New Roman", 20));
        onConnection->setMinimumHeight(50);
        onConnection->setStyleSheet(
            "QPushButton { background-color: rgba(255, 175, 175, 180); border: 2px solid rgba(220, 220, 220, 200); border-radius: 10px; }"
            "QPushButton:hover { background-color: rgba(255, 135, 135, 180); }"
            "QPushButton:disabled { background-color: rgba(255, 175, 175, 180); }"
            );
        connect(onConnection, &QPushButton::clicked, this, [this]() {
            if (ipShowLbl == nullptr) {
                if (playerName->text() == "") {
                    this->stack->error = new SamError("Заполните все поля", this->stack, this);
                    this->grid->addWidget(this->stack->error, 45, 26, 15, 48);
                }
                else {
                    stack->host = new SamHost(stack);
                    onConnection->setText("Закончить ожидание");

                    stack->host->startServer();

                    ipShowLbl = new QLabel("IP:", this);
                    ipShowLbl->setMaximumHeight(50);
                    ipShowLbl->setAlignment(Qt::AlignCenter);
                    ipShowLbl->setFont(QFont("Times New Roman", 20));

                    ipShow = new QLineEdit(stack->host->serverAddress().toString() == "127.0.0.1" ?
                                               "Нет соединения с интернетом" : stack->host->serverAddress().toString(), this);
                    ipShow->setMaximumHeight(50);
                    ipShow->setAlignment(Qt::AlignCenter);
                    ipShow->setFont(QFont("Times New Roman", 20));
                    ipShow->setReadOnly(true);

                    gridInFrame->addWidget(ipShowLbl, 65, 0, 30, 20);
                    gridInFrame->addWidget(ipShow, 65, 20, 30, 80);
                }
            }
            else {
                stack->host->sockDisc();
                delete stack->host;
                stack->host = nullptr;

                onConnection->setText("Ожидать игрока");
                if (ipShowLbl != nullptr) {
                    gridInFrame->removeWidget(ipShow);
                    gridInFrame->removeWidget(ipShowLbl);

                    delete ipShow;
                    delete ipShowLbl;

                    ipShow = nullptr;
                    ipShowLbl = nullptr;
                }
            }
        });
        gridInFrame->addWidget(onConnection, 50, 0, 13, 100);

        delete clientLabel;
        delete ipAddress;
        delete connectLayout;
        delete connectFrame;

        delete stack->client;
        stack->client = nullptr;
        stack->host = new SamHost(stack);

        clientLabel = nullptr;
        ipAddress = nullptr;
        connectFrame = nullptr;
        connectLayout = nullptr;
    }
}

SamWeb::~SamWeb() {
    delete grid;
    delete background;
    delete webGameLbl;
    delete back;
    delete isHost;
    delete gridInFrame;
    delete space;
    if (clientLabel != nullptr) {
        delete clientLabel;
        delete ipAddress;
        delete connectLayout;
        delete connectFrame;
        delete start;
    }
    else {
        delete playerNumBtn;
        delete onConnection;
    }
    if (stack->host != nullptr) {
        delete stack->host;
    }
    else if (stack->client != nullptr) {
        delete stack->client;
    }
}
