#ifndef SAMHOST_H
#define SAMHOST_H

#include "pch.h"
#include "SamError.h"

class SamStack;

class SamHost : public QTcpServer {
    Q_OBJECT

    friend SamStack;

    QTcpSocket* socket;
    SamStack* stack;
    QByteArray Data;
    bool inited;

    SamWebMessageStart inputMessage;
public:

    SamHost(SamStack* stack);
    ~SamHost();

    void sendStep(int step);

public slots:
    void startServer();
    void incomingConnection(qintptr socketDescriptor);
    void sockReady();
    void sockDisc();
};

#endif // SAMHOST_H
