#ifndef SAMCLIENT_H
#define SAMCLIENT_H

#include "pch.h"
#include "SamError.h"

class SamStack;

class SamClient : QObject {
    Q_OBJECT

public:
    SamClient(SamStack* stack);
    SamStack* stack;

    ~SamClient();

    QTcpSocket* socket;
    QByteArray Data;

    SamWebMessageStart inputMessage;

    void sendStep(int step);

    int numCalls;

public slots:
    void startConnection(QString address);
    void sockReady();
    void sockDisc();
};

#endif // SAMCLIENT_H
