#include <QApplication>
#include "../include/GameWidget.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    GameWidget window;
    window.setWindowTitle("Hamster Game");
    window.resize(1024, 768);
    window.show();
    return app.exec();
}
