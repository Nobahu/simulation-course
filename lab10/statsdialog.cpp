#include "statsdialog.h"
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QValueAxis>
#include <algorithm>
#include <iomanip>
#include <sstream>

StatsDialog::StatsDialog(double lambda, double mu, int n, double modellingTime,
                         size_t served, size_t queueSize,
                         double avgServiceTime, double avgQueueTime,
                         const std::vector<double>& distribution,
                         QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle("Результаты моделирования");
    setMinimumSize(800, 600);
    setModal(true);

    QVBoxLayout* mainLayout = new QVBoxLayout(this);

    // Заголовок
    QLabel* title = new QLabel("РЕЗУЛЬТАТЫ МОДЕЛИРОВАНИЯ");
    title->setAlignment(Qt::AlignCenter);
    QFont titleFont = title->font();
    titleFont.setBold(true);
    titleFont.setPointSize(12);
    title->setFont(titleFont);
    mainLayout->addWidget(title);

    mainLayout->addSpacing(10);

    // Параметры
    mainLayout->addWidget(new QLabel("ПАРАМЕТРЫ:"));
    mainLayout->addWidget(new QLabel("  λ = " + QString::number(lambda, 'f', 4)));
    mainLayout->addWidget(new QLabel("  μ = " + QString::number(mu, 'f', 4)));
    mainLayout->addWidget(new QLabel("  channelAmount = " + QString::number(n)));
    mainLayout->addWidget(new QLabel("  T = " + QString::number(modellingTime, 'f', 0)));

    mainLayout->addSpacing(10);

    // Результаты
    size_t totalArrived = served + queueSize;
    double throughput = modellingTime > 0 ? served / modellingTime : 0;
    double rho = (n * mu) > 0 ? lambda / (n * mu) : 0;

    mainLayout->addWidget(new QLabel("РЕЗУЛЬТАТЫ:"));
    mainLayout->addWidget(new QLabel("  Обслужено заявок: " + QString::number(served)));
    mainLayout->addWidget(new QLabel("  Осталось в очереди: " + QString::number(queueSize)));
    mainLayout->addWidget(new QLabel("  Всего поступило: " + QString::number(totalArrived)));
    mainLayout->addWidget(new QLabel("  Среднее время обслуживания: " + QString::number(avgServiceTime, 'f', 6)));
    mainLayout->addWidget(new QLabel("  Среднее время в очереди: " + QString::number(avgQueueTime, 'f', 6)));
    mainLayout->addWidget(new QLabel("  Пропускная способность: " + QString::number(throughput, 'f', 4) + " заявок/ед.вр."));
    mainLayout->addWidget(new QLabel("  Загрузка (теор.): ρ = " + QString::number(rho, 'f', 4)));

    mainLayout->addSpacing(10);

    // График распределения
    if (!distribution.empty()) {
        mainLayout->addWidget(new QLabel("РАСПРЕДЕЛЕНИЕ ЧИСЛА ЗАЯВОК В СИСТЕМЕ:"));
        QChartView* chartView = createChart(distribution);
        if (chartView) {
            mainLayout->addWidget(chartView);
        }
    }

    mainLayout->addStretch();

    // Кнопка закрытия
    closeButton = new QPushButton("Закрыть");
    connect(closeButton, &QPushButton::clicked, this, &QDialog::accept);

    QHBoxLayout* buttonLayout = new QHBoxLayout();
    buttonLayout->addStretch();
    buttonLayout->addWidget(closeButton);
    buttonLayout->addStretch();
    mainLayout->addLayout(buttonLayout);
}

QChartView* StatsDialog::createChart(const std::vector<double>& distribution)
{
    if (distribution.empty()) return nullptr;

    // Показываем первые 30 состояний
    int maxDisplay = std::min(30, (int)distribution.size());

    // Находим максимальную вероятность
    double maxProb = 0.0;
    for (int i = 0; i < maxDisplay; i++) {
        if (distribution[i] > maxProb) maxProb = distribution[i];
    }

    QBarSeries* series = new QBarSeries();
    QBarSet* barSet = new QBarSet("Вероятность");

    for (int i = 0; i < maxDisplay; i++) {
        *barSet << distribution[i];
    }
    series->append(barSet);

    QChart* chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Распределение числа заявок в системе");
    chart->setAnimationOptions(QChart::SeriesAnimations);

    // Ось X
    QStringList categories;
    for (int i = 0; i < maxDisplay; i++) {
        categories << QString::number(i);
    }
    QBarCategoryAxis* axisX = new QBarCategoryAxis();
    axisX->append(categories);
    axisX->setTitleText("Число заявок в системе");
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    // Ось Y
    QValueAxis* axisY = new QValueAxis();
    axisY->setTitleText("Вероятность");
    axisY->setRange(0.0, maxProb * 1.1);
    if (maxProb >= 0.1)
        axisY->setLabelFormat("%.3f");
    else if (maxProb >= 0.01)
        axisY->setLabelFormat("%.4f");
    else
        axisY->setLabelFormat("%.6f");
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    QChartView* chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setMinimumHeight(350);

    return chartView;
}
