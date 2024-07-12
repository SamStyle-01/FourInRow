#ifndef SAMHOST_H
#define SAMHOST_H

#include "pch.h"
#include "SamError.h"

class SamStack;

class SamHost : public QTcpServer {
    Q_OBJECT
public:
    SamHost(SamStack* stack);
    ~SamHost();

    QTcpSocket* socket;
    SamStack* stack;
    QByteArray Data;
    bool inited;

    void sendStep(int step);

    SamWebMessageStart inputMessage;

public slots:
    void startServer();
    void incomingConnection(qintptr socketDescriptor);
    void sockReady();
    void sockDisc();
};

#endif // SAMHOST_H
