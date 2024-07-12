#ifndef SAMRULES_H
#define SAMRULES_H

#include "pch.h"

class SamRules : public QWidget {
    QScrollArea* area;
    QGridLayout* layout;
    QTextEdit* rules;
    QLabel* background;
public:
    SamRules(QWidget* parent = nullptr);
    ~SamRules();
};

#endif // SAMRULES_H
