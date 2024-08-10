#ifndef SAMCLIENT_H
#define SAMCLIENT_H

#include "pch.h"
#include "SamError.h"

class SamStack;

class SamClient : QObject {
    friend SamStack;

    Q_OBJECT
    int numCalls;
    QTcpSocket* socket;
    QByteArray Data;

    SamWebMessageStart inputMessage;
    SamStack* stack;
public:

    SamClient(SamStack* stack);

    ~SamClient();

    void sendStep(int step);

public slots:
    void startConnection(QString address);
    void sockReady();
    void sockDisc();
};

#endif // SAMCLIENT_H
