#ifndef SAMERROR_H
#define SAMERROR_H

#include "pch.h"

class SamStack;

class SamError : public QWidget {
public:
    SamError(QString textError, SamStack* stack, QWidget *parent = nullptr);
    ~SamError();
    SamStack* parent;
    QVBoxLayout* layout;
    QPushButton* Ok;
    QTextEdit* error;
};

#endif // SAMERROR_H
