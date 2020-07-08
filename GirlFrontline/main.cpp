#include "gamestart.h"
#include "gameconsole.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    gameConsole gC;
    gC.show();

    return a.exec();
}
