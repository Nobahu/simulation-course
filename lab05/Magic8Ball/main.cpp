#include <QApplication>
#include "magic8ball.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    Magic8Ball window;
    window.show();

    return app.exec();
}
