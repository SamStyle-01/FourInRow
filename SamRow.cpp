#include "SamRow.h"
#include "SamGame.h"

SamRow::SamRow(QWidget* parent, int index, SamGame* game) : QWidget { parent }, game(game), index(index), color(ColorRow::TRANSPARENT) {}

void SamRow::enterEvent(QEnterEvent *event) {
    QWidget::enterEvent(event);

    this->setStyleSheet("background-color: #AA8888; border: none; border-radius: 15px;");
}

void SamRow::leaveEvent(QEvent* event) {
    QWidget::leaveEvent(event);
    if (color == ColorRow::TRANSPARENT)
        this->setStyleSheet("background-color: none; border: none; border-radius: 15px;");
    else {
        this->setStyleSheet("background-color: rgba(255, 190, 0, 120); border: none; border-radius: 15px;");
    }
}

void SamRow::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        if (this->game->getBoardIndex() == -2) {
            this->game->setBoardIndex(this->index);
        }
    }
    QWidget::mousePressEvent(event);
}

void SamRow::setOrange() {
    this->color = ColorRow::ORANGE;
    this->setStyleSheet("background-color: rgba(255, 190, 0, 120); border: none; border-radius: 15px;");
}

void SamRow::setDefault() {
    this->color = ColorRow::TRANSPARENT;
    this->setStyleSheet("background-color: none; border: none; border-radius: 15px;");
}
