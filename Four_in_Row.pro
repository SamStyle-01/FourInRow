QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets network

CONFIG += c++17 precompile_header

PRECOMPILED_HEADER = \
    pch.h

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    AlphaBetaTree.cpp \
    FourRowAI.cpp \
    FourRowBoardMonteCarloEvaluator.cpp \
    FourRowComputerPlayer.cpp \
    FourRowHumanPlayer.cpp \
    FourRowPlayer.cpp \
    FourRowRandomIterPlayer.cpp \
    FourRowRandomPlayer.cpp \
    FourRowStairs.cpp \
    FourRowWebPlayer.cpp \
    GameModeButton.cpp \
    SamBoardSize.cpp \
    SamCellsView.cpp \
    SamClient.cpp \
    SamError.cpp \
    SamGame.cpp \
    SamHost.cpp \
    SamLogic.cpp \
    SamRow.cpp \
    SamRules.cpp \
    SamSkinButton.cpp \
    SamStack.cpp \
    SamStartGame.cpp \
    SamWeb.cpp \
    SamWinLine.cpp \
    main.cpp

HEADERS += \
    AlphaBetaTree.h \
    CellType.h \
    FourRowAI.h \
    FourRowBoardMonteCarloEvaluator.h \
    FourRowComputerPlayer.h \
    FourRowHumanPlayer.h \
    FourRowPlayer.h \
    FourRowRandomIterPlayer.h \
    FourRowRandomPlayer.h \
    FourRowStairs.h \
    FourRowWebPlayer.h \
    GameModeButton.h \
    SamBoardSize.h \
    SamCellsView.h \
    SamClient.h \
    SamError.h \
    SamGame.h \
    SamHost.h \
    SamLogic.h \
    SamRow.h \
    SamRules.h \
    SamSkinButton.h \
    SamStack.h \
    SamStartGame.h \
    SamWeb.h \
    SamWebMessage.hpp \
    SamWinLine.h \
    pch.h

win32:RC_FILE = icon.rc

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES +=

FORMS +=
