#include "mainwindow.h"
#include "mainsystem.h"
#include "RandomGenerator.h"

#include <iostream>

#include <QApplication>

int main(int argc, char *argv[])
{
    // QApplication a(argc, argv);
    // MainWindow w;
    // w.show();
    // return a.exec();
    // Параметры моделирования
    double lambda = 2.0;      // интенсивность входного потока
    double mu = 2.5;          // интенсивность обслуживания
    double modeling_time = 100000.0;  // время моделирования

    // Создаем и запускаем модель
    MainSystem system(lambda, mu, modeling_time);
    system.RunImmitation();

    // Выводим результаты
    system.PrintResults();
    system.PrintComparisonWithTheory();
}
