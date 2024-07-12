#include "SamSkinButton.h"

SamSkinButton::SamSkinButton(int* index, int* index_2, QWidget* parent) : QPushButton {parent} {
    this->setFixedHeight(45);
    this->index = index;
    this->index_2 = index_2;
    this->setIcon(QIcon("./skins/player" + QString::number(*index) + ".png"));
    this->setIconSize(QSize(45, 45));
    this->setStyleSheet("border: none; background-color: none;");
}

SamSkinButton::SamSkinButton(int* index, QWidget* parent) : QPushButton {parent} {
    this->setFixedHeight(45);
    this->setIcon(QIcon("./skins/player" + QString::number(*index) + ".png"));
    this->setIconSize(QSize(45, 45));
    this->setStyleSheet("border: none; background-color: none;");
    this->index = index;
    this->index_2 = nullptr;
}

void SamSkinButton::mousePressEvent(QMouseEvent *event) {
    if (index_2 != nullptr) {
        if (event->button() == Qt::LeftButton) {
            if (*index < NUM_PICTURES)
                (*index)++;
            else *index = 1;

            if (*index == *index_2) {
                if (*index < NUM_PICTURES)
                    (*index)++;
                else *index = 1;
            }
        } else if (event->button() == Qt::RightButton) {
            if (*index > 1)
                (*index)--;
            else *index = NUM_PICTURES;

            if (*index == *index_2) {
                if (*index > 1)
                    (*index)--;
                else *index = NUM_PICTURES;
            }
        }
    }
    else {
        if (event->button() == Qt::LeftButton) {
            if (*index < NUM_PICTURES)
                (*index)++;
            else *index = 1;
        } else if (event->button() == Qt::RightButton) {
            if (*index > 1)
                (*index)--;
            else *index = NUM_PICTURES;
        }
    }
    this->setIcon(QIcon("./skins/player" + QString::number(*index) + ".png"));
    QWidget::mousePressEvent(event);
}
