#include "SamRules.h"

SamRules::SamRules(QWidget* parent) : QWidget { parent } {
    this->setMinimumSize(525, 650);
    this->setWindowTitle("Правила игры");
    this->setWindowIcon(QIcon("./Rules.png"));

    rules = new QTextEdit(this);
    QString rulesWords = "Правила игры \"Четыре в ряд\"\n\n"
        "Цель игры: Собрать четыре своих фишки в ряд по горизонтали, вертикали или диагонали.\n\n"
        "Как играть:\n\n"
        "1. Игровое поле: Игровое поле представляет собой вертикальную доску, состоящую из столбцов и строк. В каждом столбце можно разместить фишку.\n\n"
        "2. Фишки игроков: Играют два игрока, каждый из которых имеет свои фишки. Один игрок играет фишками одного цвета (например, красными), "
        "а другой игрок - фишками другого цвета (например, желтыми).\n\n"
        "3. Ходы: Игроки по очереди ставят свои фишки в любой свободный столбец на игровом поле. "
        "Фишка всегда падает вниз до первого свободного места в столбце.\n\n"
        "4. Победа: Целью каждого игрока является собрать четыре свои фишки в ряд горизонтально, вертикально или диагонально. "
        "Если игроку удается выполнить это условие первым, он побеждает.\n\n"
        "5. Ничья: Если все клетки на игровом поле заполнены, а ни один игрок не собрал четыре фишки в ряд, игра заканчивается вничью.\n\n"
        "Подсказка: Попробуйте блокировать ходы противника, чтобы предотвратить его победу, и стройте свои комбинации для достижения победы!";
    rules->setText(rulesWords);
    rules->setFont(QFont("Times New Roman", 18));

    background = new QLabel(this);
    QPixmap background_pixmap("./RulesBackground.jpg");
    background->setPixmap(background_pixmap);
    background->setScaledContents(true);

    layout = new QGridLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    area = new QScrollArea(this);
    area->setStyleSheet("background-color: rgba(255, 255, 255, 0);");
    area->setWidget(rules);
    area->setWidgetResizable(true);
    layout->addWidget(background, 0, 0, 1, 1);
    layout->addWidget(area, 0, 0, 1, 1);
    this->setLayout(layout);
    this->resize(525, 650);
}

SamRules::~SamRules() {
    delete rules;
    delete area;
    delete layout;
    delete background;
}
