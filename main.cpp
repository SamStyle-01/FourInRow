#include "SamStartGame.h"
#include "SamGame.h"
#include "SamStack.h"
#include "SamWeb.h"

#include "pch.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    srand(static_cast<unsigned>(time(0)));
    SamStack* stack = new SamStack(&app);
    SamStartGame* startGame = new SamStartGame(stack);
    SamGame* game = new SamGame(stack);
    SamWeb* web = new SamWeb(stack);

    stack->init(startGame, game, web);

    stack->show();

    app.setApplicationVersion("2.1");
    app.setOrganizationName("SamStyle-01");

    QPixmap pixmap("./Cursor.png");
    QCursor customCursor = QCursor(pixmap);
    app.setOverrideCursor(customCursor);
    app.setApplicationName("Четыре в ряд");

    return app.exec();
}
