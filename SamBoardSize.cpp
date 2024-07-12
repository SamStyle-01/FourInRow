#include "SamBoardSize.h"

SamBoardSize::SamBoardSize(QWidget* parent) : QPushButton {parent} {
    this->setStyleSheet("QPushButton { border: 2px solid #8f8f91; background-color: rgba(81, 200, 251, 180); border-radius: 15px; }"
                        "QPushButton:hover { background-color: rgba(150, 200, 251, 180); }"
                        "QPushButton:disabled { background-color: rgba(81, 200, 251, 180); }");
    this->setText("8 X 7");
    this->setFont(QFont("Times New Roman", 18));
    state = BoardSizeState::s8x7;
}

void SamBoardSize::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        if (state == BoardSizeState::s7x6) {
            state = BoardSizeState::s8x7;
            ROWS = 8;
            COLS = 7;
        }
        else if (state == BoardSizeState::s8x7) {
            state = BoardSizeState::s8x8;
            ROWS = 8;
            COLS = 8;
        }
        else if (state == BoardSizeState::s8x8) {
            state = BoardSizeState::s9x7;
            ROWS = 9;
            COLS = 7;
        }
        else if (state == BoardSizeState::s9x7) {
            state = BoardSizeState::s9x9;
            ROWS = 9;
            COLS = 9;
        }
        else if (state == BoardSizeState::s9x9) {
            state = BoardSizeState::s7x6;
            ROWS = 7;
            COLS = 6;
        }
    } else if (event->button() == Qt::RightButton) {
        if (state == BoardSizeState::s8x7) {
            state = BoardSizeState::s7x6;
            ROWS = 7;
            COLS = 6;
        }
        else if (state == BoardSizeState::s8x8) {
            state = BoardSizeState::s8x7;
            ROWS = 8;
            COLS = 7;
        }
        else if (state == BoardSizeState::s9x7) {
            state = BoardSizeState::s8x8;
            ROWS = 8;
            COLS = 8;
        }
        else if (state == BoardSizeState::s9x9) {
            state = BoardSizeState::s9x7;
            ROWS = 9;
            COLS = 7;
        }
        else if (state == BoardSizeState::s7x6) {
            state = BoardSizeState::s9x9;
            ROWS = 9;
            COLS = 9;
        }
    }

    if (state == BoardSizeState::s7x6)
        this->setText("7 X 6");
    else if (state == BoardSizeState::s8x7)
        this->setText("8 X 7");
    else if (state == BoardSizeState::s8x8)
        this->setText("8 X 8");
    else if (state == BoardSizeState::s9x7)
        this->setText("9 X 7");
    else if (state == BoardSizeState::s9x9)
        this->setText("9 X 9");

    QWidget::mousePressEvent(event);
}

BoardSizeState SamBoardSize::getState() const {
    return state;
}

void SamBoardSize::resetState() {
    if (state == BoardSizeState::s7x6) {
        ROWS = 7;
        COLS = 6;
    }
    else if (state == BoardSizeState::s8x7) {
        ROWS = 8;
        COLS = 7;
    }
    else if (state == BoardSizeState::s8x8) {
        ROWS = 8;
        COLS = 8;
    }
    else if (state == BoardSizeState::s9x7) {
        ROWS = 9;
        COLS = 7;
    }
    else if (state == BoardSizeState::s9x9) {
        ROWS = 9;
        COLS = 9;
    }
}
