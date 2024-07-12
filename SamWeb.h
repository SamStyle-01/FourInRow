#ifndef SAMWEB_H
#define SAMWEB_H

#include "pch.h"
#include "SamSkinButton.h"
#include "SamBoardSize.h"
#include "SamGame.h"
#include "SamHost.h"
#include "SamClient.h"

class SamStack;

class SamWeb : public QWidget {
public:
    QGridLayout* grid;
    QLabel* background;
    SamStack* stack;

    QLabel* webGameLbl;

    QPushButton* back;
    QPushButton* start;

    SamBoardSize* boardSize;

    QPushButton* isHost;
    bool HostState;
    QGridLayout* gridInFrame;

    QWidget* frame;

    QLabel* space;

    void HostOrConnect();

    QWidget* playerFrame;
    QGridLayout* playerGrid;
    QLabel* playerLbl;
    QLineEdit* playerName;
    int skin_index;
    SamSkinButton* skin;

    // If Host
    int playerNum;
    QPushButton* playerNumBtn;
    QPushButton* onConnection;
    QLineEdit* ipShow;
    QLabel* ipShowLbl;

    // If Client
    QLabel* clientLabel;
    QLineEdit* ipAddress;
    QWidget* connectFrame;
    QVBoxLayout* connectLayout;

    explicit SamWeb(SamStack *parent = nullptr);
    ~SamWeb();
};

#endif // SAMWEB_H
