#include "SamError.h"
#include "SamStack.h"

SamError::SamError(QString textError, SamStack* stack, QWidget *parent) : QWidget{parent} {
    this->setStyleSheet("background-color: #CD9999; border: 3px solid #DCDCDC; border-radius: 15px;");

    layout = new QVBoxLayout(this);
    this->parent = stack;

    error = new QTextEdit(this);
    error->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    error->setReadOnly(true);
    error->setPlainText(textError);
    error->setFont(QFont("Times New Roman", 16));
    error->setAlignment(Qt::AlignCenter);

    Ok = new QPushButton("Ок", this);
    Ok->setFont(QFont("Times New Roman", 20));
    connect(Ok, &QPushButton::clicked, this, [this]() {
        this->close();
        this->~SamError();
    });

    layout->addWidget(error);
    layout->addWidget(Ok);
    this->setLayout(layout);
}

SamError::~SamError() {
    delete layout;
    delete Ok;
    delete error;
    parent->error = nullptr;
}
