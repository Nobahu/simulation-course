#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCharts>
#include "MarkProcess.h"


QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void setTableData();
    std::vector<std::vector<double>> readTableData();

    QChart* createBarChart(const std::vector<double>& theorDistr, const std::vector<double>& empDistr);

private slots:
    void on_pushButton_clicked();
    void onDrawNextPoint();

private:

    void setupDynamicChart(); // создание пустого графика
    void startAnimatedDrawing(); // запуск анимации

    MarkovApp mapp;
    Ui::MainWindow *ui;

    QTimer *drawTimer = nullptr;
    QLineSeries *dynamicSeries = nullptr;
    QChart *dynamicChart = nullptr;
    QChartView *dynamicChartView = nullptr;

    size_t currentDrawIndex = 0;
    bool isDrawing = false;
    std::vector<int> cachedHistory; // копия истории для отрисовки
};
#endif // MAINWINDOW_H
