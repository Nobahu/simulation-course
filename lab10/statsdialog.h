#ifndef STATSDIALOG_H
#define STATSDIALOG_H

#include <QDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <vector>
#include <QtCharts/QChartView>

    class StatsDialog : public QDialog
{
    Q_OBJECT

public:
    StatsDialog(double lambda, double mu, int n, double modellingTime,
                size_t served, size_t queueSize,
                double avgServiceTime, double avgQueueTime,
                const std::vector<double>& distribution,
                QWidget *parent = nullptr);

private:
    QChartView* createChart(const std::vector<double>& distribution);
    QPushButton* closeButton;
};

#endif
