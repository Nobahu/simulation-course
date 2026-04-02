#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCharts>
#include <QLineEdit>

#include <math.h>
#include <vector>

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

    QChart* createBarChart(const std::vector<double>& probs);

    // Функции для генерации ДСВ на основе заданных вероятностей
    std::vector<int> generateCustomSample(const unsigned int& n, const std::vector<double>& probs);
    int generateCustomDiscrete(const std::vector<double>& probs);

    // Функции для генерации РДР
    int generateUniformDiscrete();
    std::vector<int> generateUniformSample(const unsigned int& n);

    void calculateStats(const std::vector<double>& probs);
    void calculateEmpStats(const std::vector<int>& sample);
    std::pair<double, int> calculateChiSquared(const std::vector<int>& sample,
                                               const std::vector<double>& probs);

private slots:
    void on_startPushButton_2_clicked();

    void on_autoPushButton_clicked();

private:
    Ui::MainWindow *ui;

    double mean;
    double variance;
    double chiSquared;

    double freqs;
    double empMean;
    double empVariance;

    double absMeanErr;
    double absVarianceErr;
};
#endif // MAINWINDOW_H
