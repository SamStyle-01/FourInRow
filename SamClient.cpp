#include "SamClient.h"
#include "SamStack.h"

SamClient::SamClient(SamStack* stack) {
    socket = nullptr;
    this->stack = stack;
    numCalls = 0;
}

SamClient::~SamClient() {
    if (socket != nullptr) {
        socket->deleteLater();
    }
}

void SamClient::startConnection(QString address) {
    socket = new QTcpSocket();
    connect(socket, SIGNAL(readyRead()), this, SLOT(sockReady()));
    connect(socket, SIGNAL(disconnected()), this, SLOT(sockDisc()));
    socket->connectToHost(address, 666);
}

void SamClient::sockDisc() {

}

void SamClient::sockReady() {
    Data.clear();
    if (!numCalls) {
        numCalls++;

        if (socket->waitForConnected(500)) {
            socket->waitForReadyRead(500);

            Data = socket->readAll();
            QDataStream in(&Data, QIODevice::ReadOnly);
            in.setVersion(QDataStream::Qt_6_5);

            in >> inputMessage;
        }

        SamWebMessageStart start(stack->web->playerName->text(), stack->web->skin_index);
        QDataStream out(&Data, QIODevice::WriteOnly);
        out.setVersion(QDataStream::Qt_6_5);
        out << start;
        socket->write(Data);
        socket->flush();
        socket->waitForBytesWritten();

        if ((inputMessage.name != stack->web->playerName->text()) && (inputMessage.numSkin != stack->web->skin_index))
            stack->changeWidget(CurrentWidget::GAME);
        else {
            this->stack->error = new SamError("Имя и скин не должны совпадать", this->stack, stack->web);
            this->stack->web->grid->addWidget(this->stack->error, 45, 26, 15, 48);
            numCalls--;
        }
    }
    else {
        Data = socket->readAll();
        QDataStream in(&Data, QIODevice::ReadOnly);
        in.setVersion(QDataStream::Qt_6_5);
        int buf;
        in >> buf;
        if (buf == 42)
            stack->game->startGameAgain();
        else if (buf == 40) {
            stack->changeWidget(CurrentWidget::MENU);
            stack->game->board->web_index = -1;
            stack->error = new SamError("Связь со вторым игроком пропала", stack, this->stack->startGame);
            stack->startGame->grid->addWidget(stack->error, 45, 26, 18, 48);
        }
        else {
            stack->game->board->web_index = buf;
        }
    }
}

void SamClient::sendStep(int step) {
    Data.clear();
    QDataStream out(&Data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_5);
    out << step;

    socket->write(Data);
    socket->flush();
    socket->waitForBytesWritten();
}
