#include "SamStartGame.h"
#include "SamStack.h"

SamStartGame::SamStartGame(QWidget* parent) : QWidget{parent} {
    int height = 630;
    int width = 1100;
    this->setMinimumSize(width, height);

    SamStack* stack = reinterpret_cast<SamStack*>(this->parentWidget());
    QScreen* screen = QGuiApplication::primaryScreen();
    QRect screenGeometry = screen->geometry();

    this->move(screenGeometry.width() / 2 - width, screenGeometry.height() / 2 - height);

    grid = new QGridLayout();
    grid->setContentsMargins(0, 0, 0, 0);

    background = new QLabel(this);
    QPixmap background_pixmap("./Background.jpg");
    background->setScaledContents(true);
    background->setPixmap(background_pixmap);

    lblNewGame = new QLabel("Новая игра", this);
    lblNewGame->setFont(QFont("Times New Roman", 32));
    lblNewGame->setAlignment(Qt::AlignCenter);

    toStart = new QPushButton("Начать игру", this);
    toStart->setFont(QFont("Times New Roman", 20));
    toStart->setStyleSheet(
        "QPushButton { border: 2px solid #8f8f91; background-color: rgba(81, 200, 251, 180); border-radius: 15px; }"
        "QPushButton:hover { background-color: rgba(150, 200, 251, 180); }"
        "QPushButton:disabled { background-color: rgba(81, 200, 251, 180); }"
        );

    connect(toStart, &QPushButton::clicked, this, [stack]() {
        stack->changeWidget(CurrentWidget::GAME);
    });

    player1 = new QButtonGroup(this);
    humanPlayer1 = new QRadioButton("Человек");
    humanPlayer1->setFont(QFont("Times New Roman", 16));
    karlPlayer1 = new QRadioButton("Монте-Карло");
    karlPlayer1->setFont(QFont("Times New Roman", 16));
    randomPlayer1 = new QRadioButton("Рандом");
    randomPlayer1->setFont(QFont("Times New Roman", 16));
    stairsPlayer1 = new QRadioButton("Лесенка");
    stairsPlayer1->setFont(QFont("Times New Roman", 16));
    alphaBetaPlayer1 = new QRadioButton("Альфа-Бета");
    alphaBetaPlayer1->setFont(QFont("Times New Roman", 16));
    player1->addButton(humanPlayer1, 1);
    player1->addButton(randomPlayer1, 2);
    player1->addButton(karlPlayer1, 3);
    player1->addButton(stairsPlayer1, 4);
    player1->addButton(alphaBetaPlayer1, 5);

    player2 = new QButtonGroup(this);
    humanPlayer2 = new QRadioButton("Человек");
    humanPlayer2->setFont(QFont("Times New Roman", 16));
    karlPlayer2 = new QRadioButton("Монте-Карло");
    karlPlayer2->setFont(QFont("Times New Roman", 16));
    randomPlayer2 = new QRadioButton("Рандом");
    randomPlayer2->setFont(QFont("Times New Roman", 16));
    stairsPlayer2 = new QRadioButton("Лесенка");
    stairsPlayer2->setFont(QFont("Times New Roman", 16));
    alphaBetaPlayer2 = new QRadioButton("Альфа-Бета");
    alphaBetaPlayer2->setFont(QFont("Times New Roman", 16));
    player2->addButton(humanPlayer2, 1);
    player2->addButton(randomPlayer2, 2);
    player2->addButton(karlPlayer2, 3);
    player2->addButton(stairsPlayer2, 4);
    player2->addButton(alphaBetaPlayer2, 5);

    lblPlayer1 = new QLabel("Игрок 1", this);
    lblPlayer1->setFixedHeight(45);
    lblPlayer1->setFont(QFont("Times New Roman", 23));
    lblPlayer1->setAlignment(Qt::AlignCenter);
    playerFirst = new QWidget(this);
    playerFirst->setStyleSheet("background-color: rgba(100, 150, 200, 200); border: 2px solid rgba(200, 150, 100, 200); border-radius: 15px;");
    linePlayer1 = new QLineEdit(this);
    linePlayer1->setAlignment(Qt::AlignCenter);
    linePlayer1->setStyleSheet("border: 2px solid rgba(255, 100, 100, 230)");
    linePlayer1->setPlaceholderText("Введите имя");
    linePlayer1->setFont(QFont("Times New Roman", 20));

    skinIndexes[0] = 1;
    skinIndexes[1] = 2;
    skin1 = new SamSkinButton(&skinIndexes[0], &skinIndexes[1], this);
    skin2 = new SamSkinButton(&skinIndexes[1], &skinIndexes[0], this);

    layoutPlayer1 = new QGridLayout(this);

    layoutPlayer1->addWidget(lblPlayer1, 0, 0, 1, 5);
    layoutPlayer1->addWidget(skin1, 0, 5, 1, 1);
    layoutPlayer1->addWidget(linePlayer1, 1, 0, 1, 6);
    layoutPlayer1->addWidget(randomPlayer1, 2, 0, 1, 6);
    layoutPlayer1->addWidget(karlPlayer1, 3, 0, 1, 6);
    layoutPlayer1->addWidget(stairsPlayer1, 4, 0, 1, 6);
    layoutPlayer1->addWidget(alphaBetaPlayer1, 5, 0, 1, 6);
    layoutPlayer1->addWidget(humanPlayer1, 6, 0, 1, 6);
    playerFirst->setLayout(layoutPlayer1);

    lblPlayer2 = new QLabel("Игрок 2", this);
    lblPlayer2->setFixedHeight(45);
    lblPlayer2->setFont(QFont("Times New Roman", 23));
    lblPlayer2->setAlignment(Qt::AlignCenter);
    playerSecond = new QWidget(this);
    playerSecond->setStyleSheet("background-color: rgba(100, 150, 200, 200); border: 2px solid rgba(200, 150, 100, 200); border-radius: 15px;");
    linePlayer2 = new QLineEdit(this);
    linePlayer2->setAlignment(Qt::AlignCenter);
    linePlayer2->setStyleSheet("border: 2px solid rgba(255, 100, 100, 230)");
    linePlayer2->setPlaceholderText("Введите имя");
    linePlayer2->setFont(QFont("Times New Roman", 20));

    layoutPlayer2 = new QGridLayout(this);

    layoutPlayer2->addWidget(skin2, 0, 0, 1, 1);
    layoutPlayer2->addWidget(lblPlayer2, 0, 1, 1, 5);
    layoutPlayer2->addWidget(linePlayer2, 1, 0, 1, 6);
    layoutPlayer2->addWidget(randomPlayer2, 2, 0, 1, 6);
    layoutPlayer2->addWidget(karlPlayer2, 3, 0, 1, 6);
    layoutPlayer2->addWidget(stairsPlayer2, 4, 0, 1, 6);
    layoutPlayer2->addWidget(alphaBetaPlayer2, 5, 0, 1, 6);
    layoutPlayer2->addWidget(humanPlayer2, 6, 0, 1, 6);
    playerSecond->setLayout(layoutPlayer2);

    options = new QWidget(this);
    options->setStyleSheet("background-color: rgba(100, 150, 200, 200); border: 2px solid rgba(200, 150, 100, 200); border-radius: 15px;");
    lblOptions = new QLabel("Режим", this);
    lblOptions->setStyleSheet("background-color: none; border: none;");
    lblOptions->setFixedHeight(20);
    lblOptions->setFont(QFont("Times New Roman", 18));
    lblOptions->setAlignment(Qt::AlignCenter);
    options_layout = new QVBoxLayout(options);

    gameMode = new GameModeButton(options);
    boardSize = new SamBoardSize(options);

    connect(player1, &QButtonGroup::buttonClicked, this, [this]() {
        if ((player1->checkedId() != 1) && (player1->checkedId() != -1) && (player2->checkedId() != 1) && (player2->checkedId() != -1)) {
            gameMode->setClassic();
            gameMode->setDisabled(true);
            gameMode->setStyleSheet("background-color: rgba(160, 200, 200, 180);");
        }
        else {
            gameMode->setEnabled(true);
            gameMode->setStyleSheet("QPushButton { border: 2px solid #8f8f91; background-color: rgba(81, 200, 251, 180); border-radius: 15px; }"
                                    "QPushButton:hover { background-color: rgba(150, 200, 251, 180); }"
                                    "QPushButton:disabled { background-color: rgba(81, 200, 251, 180); }");
        }
    });
    connect(player2, &QButtonGroup::buttonClicked, this, [this]() {
        if ((player1->checkedId() != 1) && (player1->checkedId() != -1) && (player2->checkedId() != 1) && (player2->checkedId() != -1)) {
            gameMode->setClassic();
            gameMode->setDisabled(true);
            gameMode->setStyleSheet("background-color: rgba(160, 200, 200, 180);");
        }
        else {
            gameMode->setEnabled(true);
            gameMode->setStyleSheet("QPushButton { border: 2px solid #8f8f91; background-color: rgba(81, 200, 251, 180); border-radius: 15px; }"
                                    "QPushButton:hover { background-color: rgba(150, 200, 251, 180); }"
                                    "QPushButton:disabled { background-color: rgba(81, 200, 251, 180); }");
        }
    });

    options_layout->addWidget(lblOptions);
    options_layout->addWidget(gameMode);
    options_layout->addWidget(boardSize);
    options->setLayout(options_layout);

    rules = new SamRules();

    openRules = new QPushButton(this);
    openRules->setIcon(QIcon("./Rules.png"));
    openRules->setFixedSize(65, 65);
    openRules->setIconSize(QSize(55, 55));
    openRules->setStyleSheet(
        "QPushButton { border: 2px solid #8f8f91; border-radius: 22px; }"
        "QPushButton:hover { background-color: rgba(150, 200, 251, 180); }"
        "QPushButton:disabled { background-color: rgba(81, 200, 251, 180); }"
        );
    connect(openRules, &QPushButton::clicked, this, [this]() {
        rules->close();
        rules->show();
    });

    webGame = new QPushButton(this);
    webGame->setIcon(QIcon("./Web.png"));
    webGame->setFixedSize(65, 65);
    webGame->setIconSize(QSize(55, 55));
    webGame->setStyleSheet(
        "QPushButton { border: 2px solid #8f8f91; border-radius: 22px; }"
        "QPushButton:hover { background-color: rgba(150, 200, 251, 180); }"
        "QPushButton:disabled { background-color: rgba(81, 200, 251, 180); }"
        );
    connect(webGame, &QPushButton::clicked, this, [stack]() {
        stack->changeWidget(CurrentWidget::WEB);
    });

    this->grid->addWidget(background, 0, 0, 100, 100);
    this->grid->addWidget(lblNewGame, 10, 30, 10, 40);
    this->grid->addWidget(toStart, 80, 30, 20, 40);

    this->grid->addWidget(openRules, 88, 1, 5, 5);
    this->grid->addWidget(webGame, 88, 8, 5, 5);

    this->grid->addWidget(playerFirst, 28, 0, 50, 40);
    this->grid->addWidget(playerSecond, 28, 60, 50, 40);

    this->grid->addWidget(options, 80, 72, 20, 28);

    this->setLayout(grid);
}

bool SamStartGame::formsFull() {
    if (this->linePlayer1->text() == "" || this->linePlayer2->text() == ""
        || this->player1->checkedId() == -1 || this->player2->checkedId() == -1) {
        return false;
    }
    return true;
}

SamStartGame::~SamStartGame() {
    delete grid;
    delete toStart;
    delete background;

    delete linePlayer1;
    delete linePlayer2;
    delete player1;
    delete player2;

    delete lblNewGame;
    delete humanPlayer1;
    delete humanPlayer2;
    delete karlPlayer1;
    delete karlPlayer2;

    delete randomPlayer1;
    delete randomPlayer2;

    delete alphaBetaPlayer1;
    delete alphaBetaPlayer2;

    delete stairsPlayer1;
    delete stairsPlayer2;

    delete lblPlayer1;
    delete lblPlayer2;

    delete skin1;
    delete skin2;

    delete layoutPlayer1;
    delete layoutPlayer2;
    delete playerFirst;
    delete playerSecond;

    delete rules;

    delete boardSize;
    delete options_layout;
    delete options;
    delete openRules;
}
