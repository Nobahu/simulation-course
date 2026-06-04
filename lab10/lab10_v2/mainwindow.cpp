#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include "event_manager.h"
#include "device_manager.h"
#include "queue_manager.h"
#include "stream.h"

#include "statsdialog.h"

#include <iostream>
#include <QMessageBox>

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

void MainWindow::on_pushButton_clicked() try
{
    double modelling_time = ui->lineEdit->text().toDouble();
    double lambda = ui->lineEdit_2->text().toDouble();
    double mu = ui->lineEdit_3->text().toDouble();
    unsigned int channelAmount = ui->lineEdit_4->text().toInt();
    unsigned int seed = ui->lineEdit_5->text().toInt();

    if( modelling_time < 0 || lambda < 0 || mu < 0 || channelAmount < 0 )
    {
        throw std::invalid_argument("Введены не корректные данные!");
    }

    // Сброс состояний
    EventManager::get().reset();
    DeviceManager::get().reset();
    QueueManager::get().reset();
    StatisticsCollector::get().reset();

    // Установка seed для генератора
    LCG::get().setSeed(seed);

    // Создаём каналы
    for (int i = 0; i < channelAmount; i++) {
        auto device = std::make_shared< ProcessingDevice >( mu );
        DeviceManager::get().addDevice( device );
    }

    // Создаём и запускаем поток заявок
    auto stream = std::make_shared< PoissonStream >( lambda );
    stream->start();

    // Запускаем моделирование
    EventManager::get().run( modelling_time );

    size_t served = StatisticsCollector::get().getTotalServed();
    size_t queueSize = QueueManager::get().size();
    double avgServiceTime = StatisticsCollector::get().getAverageServiceTime();
    double avgQueueTime = StatisticsCollector::get().getAverageQueueTime();
    std::vector<double> distribution = StatisticsCollector::get().getStateProbabilities(modelling_time);

    // Показываем диалог
    StatsDialog dialog(lambda, mu, channelAmount, modelling_time,
                       served, queueSize,
                       avgServiceTime, avgQueueTime,
                       distribution, nullptr);
    dialog.exec();
}
catch ( const std::exception& e )
{
    QMessageBox::critical(this, "Ошибка", e.what());
}

