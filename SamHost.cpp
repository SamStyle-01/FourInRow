#include "SamHost.h"
#include "SamStack.h"

SamHost::SamHost(SamStack* stack) : QTcpServer() {
    socket = nullptr;
    this->stack = stack;
    inited = false;
}

SamHost::~SamHost() {
    if (socket != nullptr) {
        socket->deleteLater();
    }
}

void SamHost::startServer() {
    QList<QHostAddress> list = QNetworkInterface::allAddresses();

    if (this->listen(list[1], 666)) {

    }
    else {

    }
}

void SamHost::sendStep(int step) {
    Data.clear();
    QDataStream out(&Data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_5);
    out << step;

    socket->write(Data);
    socket->flush();
    socket->waitForBytesWritten();
}

void SamHost::incomingConnection(qintptr socketDescriptor) {
    socket = new QTcpSocket(this);
    socket->setSocketDescriptor(socketDescriptor);

    connect(socket, SIGNAL(readyRead()), this, SLOT(sockReady()));
    connect(socket, SIGNAL(disconnected()), this, SLOT(sockDisc()));

    SamWebMessageStart start(stack->web->playerName->text(), stack->web->skin_index, stack->web->playerNum, stack->web->boardSize->getState());
    QDataStream out(&Data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_5);
    out << start;
    socket->write(Data);
    socket->flush();
    socket->waitForBytesWritten();
}

void SamHost::sockReady() {
    if (!inited) {
        inited = true;
        if (socket->waitForConnected(500)) {
            socket->waitForReadyRead(500);

            Data = socket->readAll();
            QDataStream in(&Data, QIODevice::ReadOnly);
            in.setVersion(QDataStream::Qt_6_5);

            in >> inputMessage;

            if ((inputMessage.name != stack->web->playerName->text()) && (inputMessage.numSkin != stack->web->skin_index))
                stack->changeWidget(CurrentWidget::GAME);
            else {
                this->stack->error = new SamError("Имя и скин не должны совпадать", this->stack, stack->web);
                this->stack->web->grid->addWidget(this->stack->error, 45, 26, 15, 48);
                inited = false;
            }
        }
    }
    else {
        Data.clear();
        Data = socket->readAll();
        QDataStream in(&Data, QIODevice::ReadOnly);
        in.setVersion(QDataStream::Qt_6_5);
        int buf;
        in >> buf;
        if (buf == 42)
            stack->game->startGameAgain();
        else if (buf == 40) {
            stack->wasStoppedWeb = true;
            stack->changeWidget(CurrentWidget::MENU);
        }
        else
            stack->game->setBoardWebIndex(buf);
    }
}

void SamHost::sockDisc() {

}
