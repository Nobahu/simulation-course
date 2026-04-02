#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCharts>

#include <random>
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

    QChart* createBarChart(const std::vector<double>& sample);

    std::vector<double> NormalDistributionGenerator(const double& mean,const double& variance,const unsigned int& sample_size);

    double calculateAvg(const std::vector<double>& sample);
    double calculateVariance(const std::vector<double>& sample,const double& avg);
    std::pair<double, int> calculateCS(const std::vector<double>& sample, const double& mean, const double& variance);

private slots:
    void on_startPushButton_clicked();

private:

    double getCriticalValue(int df)
    {
        if (df < 1) return 0;

        // Аппроксимация для α = 0.05
        double z = 1.6449;  // квантиль стандартного нормального распределения для 0.05
        return df + std::sqrt(2.0 * df) * z;
    }

    Ui::MainWindow *ui;

    double calculatedAvg;
    double calculatedVariance;
    double sigma;
    double h;
    double calculatedChisquared;

};
#endif // MAINWINDOW_H
