#include "SamWinLine.h"
#include <QLabel>

SamWinLine::SamWinLine(QWidget *parent) : QLabel {parent} {
    state = LineState::NONE;
    this->setAttribute(Qt::WA_TransparentForMouseEvents);
}

void SamWinLine::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);

    if (state == LineState::ROW) {
        QPainter painter(this);

        QColor color(Qt::darkMagenta);
        color.setAlpha(150);
        painter.setPen(QPen(color, 10));

        painter.drawLine(0, this->height() / 2, this->width(), this->height() / 2);
    }
    else if (state == LineState::COL) {
        QPainter painter(this);

        QColor color(Qt::darkMagenta);
        color.setAlpha(150);
        painter.setPen(QPen(color, 10));

        painter.drawLine(this->width() / 2, 0, this->width() / 2, this->height());
    }
    else if (state == LineState::DIAG_RIGHT) {
        QPainter painter(this);

        QColor color(Qt::darkMagenta);
        color.setAlpha(150);
        painter.setPen(QPen(color, 10));

        painter.drawLine(0, 0, this->width(), this->height());
    }
    else if (state == LineState::DIAG_LEFT) {
        QPainter painter(this);

        QColor color(Qt::darkMagenta);
        color.setAlpha(150);
        painter.setPen(QPen(color, 10));

        painter.drawLine(0, this->height(), this->width(), 0);
    }
}

void SamWinLine::Activate(LineState state) {
    this->state = state;
}

void SamWinLine::DisActivate() {
    state = LineState::NONE;
}
