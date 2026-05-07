#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setStyleSheet("QMainWindow { background-color: rgba(71,74,81, 240); }");

    drawTimer = new QTimer(this);
    connect(drawTimer, &QTimer::timeout, this, &MainWindow::onDrawNextPoint);
}

void MainWindow::setTableData()
{
    const auto& matrix = mapp.getMatrix();

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            QTableWidgetItem* item = ui->tableWidget->item(i, j);
            if (!item) {
                item = new QTableWidgetItem();
                ui->tableWidget->setItem(i, j, item);
            }
            item->setText(QString::number(matrix[i][j], 'f', 3));
            item->setTextAlignment(Qt::AlignCenter);
        }
    }
}
std::vector<std::vector<double>> MainWindow::readTableData()
{
    std::vector<std::vector<double>> matrix(3, std::vector<double>(3));
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            QTableWidgetItem* item = ui->tableWidget->item(i,j);
            if(item) {
                matrix[i][j] = item->text().toDouble();
            }
        }
    }
    return matrix;
}

QChart* MainWindow::createBarChart(const std::vector<double>& theorDistr, const std::vector<double>& empDistr)
{
    QStringList states;
    states << "Ясно" << "Облачно" << "Пасмурно";

    QBarSet *setEmperical = new QBarSet("Эмпирическое");
    QBarSet *setTheoretical = new QBarSet("Теоретическое");
    for(size_t i = 0;i < theorDistr.size();i++) {
        *setTheoretical << theorDistr[i];
        *setEmperical << empDistr[i];
    }

    QBarSeries* series = new QBarSeries();
    series->append(setEmperical);
    series->append(setTheoretical);

    QChart* barChart = new QChart();
    barChart->addSeries(series);
    barChart->setAnimationOptions(QChart::SeriesAnimations);
    barChart->setTitleBrush(QBrush(Qt::white));
    barChart->setBackgroundBrush(QColor(71, 74, 81));
    barChart->legend()->setLabelColor(Qt::white);

    // Настройка оси X
    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    axisX->append({"Ясно", "Облачно", "Пасмурно"});
    axisX->setTitleBrush(QBrush(Qt::white));
    axisX->setLabelsColor(Qt::white);
    barChart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    // Настройка оси Y
    QValueAxis *axisY = new QValueAxis();
    axisY->setTitleText("Вероятность");
    axisY->setTitleBrush(QBrush(Qt::white));
    axisY->setLabelsColor(Qt::white);
    axisY->setRange(0, 1);
    barChart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    return barChart;
}

void MainWindow::setupDynamicChart()
{
    // Очистка старого содержимого GraphicWidget
    QLayout *oldLayout = ui->GraphicWidget->layout();
    if (oldLayout) {
        QLayoutItem *child;
        while ((child = oldLayout->takeAt(0)) != nullptr) {
            if (child->widget()) delete child->widget();
            delete child;
        }
        delete oldLayout;
    }

    // Создаем пустую серию
    dynamicSeries = new QLineSeries();
    dynamicSeries->setColor(QColor(71,74,81));
    dynamicSeries->setPen(QPen(QBrush(QColor(0, 255, 204)), 2));

    // Создаем диаграмму
    dynamicChart = new QChart();
    dynamicChart->addSeries(dynamicSeries);
    dynamicChart->setTitle("Динамика изменения погоды");
    dynamicChart->setTitleBrush(QBrush(Qt::white));
    dynamicChart->setAnimationOptions(QChart::SeriesAnimations);
    dynamicChart->setTheme(QChart::ChartThemeDark);
    dynamicChart->setBackgroundBrush(QColor(71,74,81));

    // Ось X (дни)
    QValueAxis *axisX = new QValueAxis();
    axisX->setTitleText("Часы");
    axisX->setTitleBrush(QBrush(Qt::white));
    axisX->setLabelsColor(Qt::white);
    axisX->setLabelFormat("%d");
    axisX->setRange(1, cachedHistory.size());
    axisX->setTickCount(qMin(10, (int)cachedHistory.size()));
    dynamicChart->addAxis(axisX, Qt::AlignBottom);
    dynamicSeries->attachAxis(axisX);

    // Ось Y (состояния)
    QCategoryAxis *axisY = new QCategoryAxis();
    axisY->setTitleText("Состояние погоды");
    axisY->setTitleBrush(QBrush(Qt::white));
    axisY->setLabelsColor(Qt::white);
    axisY->append("Ясно", 1);
    axisY->append("Облачно", 2);
    axisY->append("Пасмурно", 3);
    axisY->setRange(0.5, 3.5);
    axisY->setLabelsPosition(QCategoryAxis::AxisLabelsPositionOnValue);
    dynamicChart->addAxis(axisY, Qt::AlignLeft);
    dynamicSeries->attachAxis(axisY);

    // Отображение
    dynamicChartView = new QChartView(dynamicChart);
    dynamicChartView->setRenderHint(QPainter::Antialiasing);

    QVBoxLayout *layout = new QVBoxLayout(ui->GraphicWidget);
    layout->addWidget(dynamicChartView);
    layout->setContentsMargins(0, 0, 0, 0);
    ui->GraphicWidget->setLayout(layout);
}

void MainWindow::onDrawNextPoint()
{
    if (currentDrawIndex >= cachedHistory.size()) {
        // Отрисовка завершена
        drawTimer->stop();
        isDrawing = false;
        ui->pushButton->setText("Start");

        return;
    }

    // Добавляем следующую точку
    int day = currentDrawIndex + 1;
    int state = cachedHistory[currentDrawIndex];
    dynamicSeries->append(day, state);

    int windowSize = 30;  // показываем последние 30 дней
    QValueAxis *axisX = qobject_cast<QValueAxis*>(dynamicChart->axes(Qt::Horizontal).first());
    if (axisX) {
        if (day <= windowSize) {
            // Начальный этап - от 1 до windowSize
            axisX->setRange(1, windowSize);
        } else {
            // Прокрутка - показываем последние windowSize дней
            axisX->setRange(day - windowSize + 1, day);
        }
        axisX->setTickCount(6);
    }

    currentDrawIndex++;
}

void MainWindow::startAnimatedDrawing()
{
    setupDynamicChart();
    currentDrawIndex = 0;
    isDrawing = true;

    // Задержка между добавлением точек (в миллисекундах)
    int delay = ui->delay_lineEdit->text().toInt();
    drawTimer->start(delay);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    //Чтение данных с таблицы и заполнение матрицы MarkovApp
    std::vector<std::vector<double>> currentMatrix = readTableData();
    mapp.setMatrix(currentMatrix);


    //Симуляция
    int days = ui->daynum_lineEdit->text().toInt();
    if (days <= 0) days = 30;

    //Динамический график измненеия погоды
    mapp.process(days);

    //Создание гистограммы
    QChart* chart = createBarChart(mapp.getTheoreticalDistr(),mapp.getEmpDistr());
    if (chart) {
        QLayout *oldLayout = ui->StatsWidget->layout();
        if (oldLayout) {
            QLayoutItem *child;
            while ((child = oldLayout->takeAt(0)) != nullptr) {
                if (child->widget()) {
                    child->widget()->deleteLater();
                }
                delete child;
            }
            delete oldLayout;
        }

        QChartView *chartView = new QChartView(chart);
        chartView->setRenderHint(QPainter::Antialiasing);
        chartView->setFixedSize(391, 651);

        QVBoxLayout *layout = new QVBoxLayout(ui->StatsWidget);
        layout->addWidget(chartView);
        layout->setContentsMargins(0, 0, 0, 0);
        ui->StatsWidget->setLayout(layout);
    }

    cachedHistory = mapp.getHistory();
    startAnimatedDrawing();

}

