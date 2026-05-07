#include "mainwindow.h"

#include <QApplication>
#include "MarkProcess.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MainWindow window;

    window.setTableData();
    window.show();

    return app.exec();
}
