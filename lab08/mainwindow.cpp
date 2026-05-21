#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include "simulationmodel.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

bool MainWindow::RRValidation( const double& modelling_time, const double& lambda, const int& seed, const int& nRuns )
{

    QMessageBox msgBox;
    msgBox.setIcon( QMessageBox::Critical );
    msgBox.setWindowTitle( "Для RR" );
    msgBox.setMinimumSize(1000, 500);

    if ( modelling_time <= 0 || lambda <= 0 || seed < 0 || nRuns <= 0 )
    {
        msgBox.setText("Радмир Ренатович, не надо баловаться!\n" "Поправьте данные ;) " );
        msgBox.exec();
        return false;
    }

    else if ( nRuns > 10000 || modelling_time >= 1000 )
    {
        msgBox.setText("Радмир Ренатович, не надо баловаться!\n" "Ну куда вам столько?! " );
        msgBox.exec();
        return false;
    }
    return true;
}

QChart* MainWindow::CreateChart(const std::vector<int>& data, double lambda, double time)
{
    if (data.empty())
    {
        return nullptr;
    }

    double lambdaT = lambda * time;

    // 1. Подсчёт частот
    std::map<int, int> frequency;
    for (int value : data)
    {
        frequency[value]++;
    }

    // 2. Готовим данные для гистограммы
    QBarSeries* series = new QBarSeries();
    QBarSet* barSet = new QBarSet("Эмпирическое распределение");
    QStringList categories;

    int total = data.size();

    for (const auto& [value, freq] : frequency)
    {
        barSet->append(static_cast<double>(freq) / total);
        categories << QString::number(value);
    }

    series->append(barSet);

    // 4. График
    QChart* chart = new QChart();
    chart->addSeries(series);

    // Ось X
    QBarCategoryAxis* axisX = new QBarCategoryAxis();
    axisX->append(categories);
    axisX->setTitleText("Число запросов");
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    // Ось Y
    QValueAxis* axisY = new QValueAxis();
    axisY->setTitleText("Вероятность");

    double maxProb = 0;
    for (int i = 0; i < barSet->count(); i++) {
        maxProb = std::max(maxProb, barSet->at(i));
    }
    axisY->setRange(0, maxProb * 1.2);
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    // Настройка цвета
    barSet->setColor(QColor("#3498db"));
    return chart;
}

void MainWindow::on_Start_pushButton_clicked()
{
    double modelling_time = ui->lineEdit_2->text().toDouble();
    double lambda = ui->lineEdit_3->text().toDouble();
    int seed = ui->lineEdit_5->text().toInt();
    int nRuns = ui->lineEdit_6->text().toInt();

    if ( !RRValidation( modelling_time, lambda, seed, nRuns ) )
    {
        return;
    }

    SimulationModel model( lambda );
    RandomGenerator::seed( seed );

    std::vector< int > modellingResults = model.SimulateManyRuns( modelling_time, nRuns );
    double resultMean = model.CalculateMean( modellingResults );
    double resultVariance = model.CalculateVariance( modellingResults, resultMean );

    qDebug() << "Mean: " << resultMean << "\n";
    qDebug() << "Variance: " << resultVariance << "\n";

    QLayout* oldLayout = ui->widget->layout();
    if (oldLayout) {
        // Удаляем все виджеты из layout
        while (QLayoutItem* item = oldLayout->takeAt(0)) {
            if (QWidget* widget = item->widget()) {
                delete widget;
            }
            delete item;
        }
        delete oldLayout;
    }

    // Создаём новый график
    QChart* chart = CreateChart( modellingResults, lambda, modelling_time );
    QChartView* view = new QChartView(chart);
    view->setRenderHint(QPainter::Antialiasing);

    // Новый layout
    QVBoxLayout* layout = new QVBoxLayout(ui->widget);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->addWidget(view);
}

