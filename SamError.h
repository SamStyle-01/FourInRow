#ifndef SAMERROR_H
#define SAMERROR_H

#include "pch.h"

class SamStack;

class SamError : public QWidget {
    SamStack* parent;
    QVBoxLayout* layout;
    QPushButton* Ok;
    QTextEdit* error;
public:
    SamError(QString textError, SamStack* stack, QWidget *parent = nullptr);
    ~SamError();
};

#endif // SAMERROR_H
