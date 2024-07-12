#ifndef SAMWEBMESSAGE_H
#define SAMWEBMESSAGE_H

#include "SamBoardSize.h"

struct SamWebMessageStart {
    QString name;
    int numSkin;
    int numStep;
    BoardSizeState sizeBoard;

    SamWebMessageStart(QString name, int numSkin, int numStep = 0, BoardSizeState sizeBoard = BoardSizeState::none) {
        this->name = name;
        this->numSkin = numSkin;
        this->numStep = numStep;
        this->sizeBoard = sizeBoard;
    }

    SamWebMessageStart() {
        this->name = "NoName";
        this->numSkin = -1;
        this->numStep = -1;
        this->sizeBoard = BoardSizeState::none;
    }

    // Метод для сериализации
    friend QDataStream &operator<<(QDataStream &out, const SamWebMessageStart& that) {
        out << that.name << that.numSkin << that.numStep << that.sizeBoard;
        return out;
    }

    // Метод для десериализации
    friend QDataStream &operator>>(QDataStream &in, SamWebMessageStart& that) {
        in >> that.name >> that.numSkin >> that.numStep >> that.sizeBoard;
        return in;
    }
};

#endif // SAMWEBMESSAGE_H
