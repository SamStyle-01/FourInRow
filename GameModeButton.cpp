#include "GameModeButton.h"

GameModeButton::GameModeButton(QWidget* parent) : QPushButton { parent }  {
    this->setStyleSheet("QPushButton { border: 2px solid #8f8f91; background-color: rgba(81, 200, 251, 180); border-radius: 15px; }"
                        "QPushButton:hover { background-color: rgba(150, 200, 251, 180); }"
                        "QPushButton:disabled { background-color: rgba(81, 200, 251, 180); }");
    this->setText("Классический");
    this->setFont(QFont("Times New Roman", 18));
    state = GameMode::CLASSIC;
}

void GameModeButton::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        if (state == GameMode::CLASSIC) {
            state = GameMode::Timer10s;
        }
        else if (state == GameMode::Timer10s) {
            state = GameMode::Timer30s;
        }
        else if (state == GameMode::Timer30s) {
            state = GameMode::Timer1minAll;
        }
        else if (state == GameMode::Timer1minAll) {
            state = GameMode::Timer2minAll;
        }
        else if (state == GameMode::Timer2minAll) {
            state = GameMode::Train;
        }
        else if (state == GameMode::Train) {
            state = GameMode::CLASSIC;
        }
    } else if (event->button() == Qt::RightButton) {
        if (state == GameMode::Timer10s) {
            state = GameMode::CLASSIC;
        }
        else if (state == GameMode::Timer30s) {
            state = GameMode::Timer10s;
        }
        else if (state == GameMode::Timer1minAll) {
            state = GameMode::Timer30s;
        }
        else if (state == GameMode::Timer2minAll) {
            state = GameMode::Timer1minAll;
        }
        else if (state == GameMode::Train) {
            state = GameMode::Timer2minAll;
        }
        else if (state == GameMode::CLASSIC) {
            state = GameMode::Train;
        }
    }

    if (state == GameMode::CLASSIC)
        this->setText("Классический");
    else if (state == GameMode::Timer10s)
        this->setText("Ход 10 сек");
    else if (state == GameMode::Timer30s)
        this->setText("Ход 30 сек");
    else if (state == GameMode::Timer1minAll)
        this->setText("Таймер 1:00");
    else if (state == GameMode::Timer2minAll)
        this->setText("Таймер 2:00");
    else if (state == GameMode::Train)
        this->setText("Тренировка");

    QWidget::mousePressEvent(event);
}

GameMode GameModeButton::getState() const {
    return state;
}

void GameModeButton::setClassic() {
    this->state = GameMode::CLASSIC;
    this->setText("Классический");
}
