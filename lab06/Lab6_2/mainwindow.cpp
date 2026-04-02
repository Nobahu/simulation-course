#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QDebug>

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

QChart* MainWindow::createBarChart(const std::vector<double>& sample)
{
    double minVal = sample[0];
    double maxVal = sample.back();

    // Правило Скотта
    h = 3.5 * sigma / std::pow(sample.size(), 1.0/3.0);
    if (h <= 0) h = 1.0;

    int numIntervals = static_cast<int>(std::ceil((maxVal - minVal) / h));
    if (numIntervals < 1) numIntervals = 1;

    QStringList otrezki;
    for (int i = 0; i < numIntervals; ++i) {
        double left = minVal + i * h;
        double right = minVal + (i + 1) * h;

        QString interval;
        if (i == numIntervals - 1) {
            interval = "[" + QString::number(left, 'f', 1) + "; " +
                       QString::number(right, 'f', 1) + "]";
        } else {
            interval = "[" + QString::number(left, 'f', 1) + "; " +
                       QString::number(right, 'f', 1) + ")";
        }
        otrezki << interval;
    }

    // 5. Подсчёт частот
    std::vector<int> counts(numIntervals, 0);
    for (double value : sample) {
        int index = static_cast<int>((value - minVal) / h);
        if (index >= numIntervals) index = numIntervals - 1;
        if (index < 0) index = 0;
        counts[index]++;
    }

    // 6. Вероятности (относительные частоты)
    std::vector<double> probability(numIntervals, 0);
    for (int i = 0; i < numIntervals; ++i) {
        probability[i] = static_cast<double>(counts[i]) / sample.size();
    }

    double maxProbability = *std::max_element(probability.begin(), probability.end());

    // Создаем график
    QBarSet *set = new QBarSet("Вероятность");
    for (double prob : probability) {
        *set << prob;
    }

    QBarSeries *series = new QBarSeries();
    series->append(set);

    QChart* barChart = new QChart();
    barChart->addSeries(series);
    barChart->setTitle("Нормальное распределение (n=" + QString::number(sample.size()) + ")");
    barChart->setAnimationOptions(QChart::SeriesAnimations);

    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    axisX->append(otrezki);
    axisX->setTitleText("Интервалы");
    barChart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    QValueAxis *axisY = new QValueAxis();
    axisY->setTitleText("Вероятность");
    // Динамический диапазон от 0 до максимальной вероятности + 10% запаса
    axisY->setRange(0, maxProbability * 1.1);
    axisY->setLabelFormat("%.2f");  // Два знака после запятой
    barChart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    return barChart;
}

std::vector<double> MainWindow::NormalDistributionGenerator(const double& mean, const double& variance, const unsigned int& sample_size)
{
    std::vector<double> result;
    result.reserve(sample_size);

    std::random_device rd;
    std::mt19937_64 mtgen(rd());
    std::uniform_real_distribution<double> uniform(0.0, 1.0);

    double sigma = std::sqrt(variance);

    // Генерируем пары чисел (можно генерировать по одному, но Бокс-Мюллер даёт пару)
    for (unsigned int i = 0; i < sample_size; i += 2) {
        double r = uniform(mtgen);
        double phi = uniform(mtgen);

        // Формула Бокса-Мюллера для двух независимых стандартных нормальных
        double z1 = std::sqrt(-2.0 * std::log(r)) * std::cos(2.0 * M_PI * phi);
        double z2 = std::sqrt(-2.0 * std::log(r)) * std::sin(2.0 * M_PI * phi);

        // Преобразуем к заданному среднему и дисперсии
        double x1 = mean + z1 * sigma;
        double x2 = mean + z2 * sigma;

        result.push_back(x1);
        if (i + 1 < sample_size) {
            result.push_back(x2);
        }
    }

    std::sort(result.begin(), result.end());
    return result;
}

double MainWindow::calculateAvg(const std::vector<double>& sample)
{
    double sum = 0;
    for(auto& el: sample) {
        sum += el;
    }
    return sum / sample.size();
}
double MainWindow::calculateVariance(const std::vector<double>& sample,const double& avg)
{
    double sumSquaredDiff = 0;
    for(auto& el: sample) {
        sumSquaredDiff += std::pow(el - avg, 2);
    }
    return sumSquaredDiff / (sample.size() - 1);
}
std::pair<double, int> MainWindow::calculateCS(const std::vector<double>& sample, const double& mean, const double& variance)
{
    double minVal = sample[0];
    double maxVal = sample.back();

    int numIntervals = static_cast<int>(std::ceil((maxVal - minVal) / h));
    if (numIntervals < 1) numIntervals = 1;

    // Наблюдаемые частоты
    std::vector<int> observed(numIntervals, 0);
    for (double value : sample) {
        int index = static_cast<int>((value - minVal) / h);
        if (index >= numIntervals) index = numIntervals - 1;
        if (index < 0) index = 0;
        observed[index]++;
    }

    // Теоретические вероятности
    auto phi = [](double z) { return 0.5 * (1.0 + std::erf(z / std::sqrt(2.0))); };
    double sigma0 = std::sqrt(variance);

    std::vector<double> prob(numIntervals);
    for (int i = 0; i < numIntervals; ++i) {
        double left = minVal + i * h;
        double right = minVal + (i + 1) * h;
        double z_left = (left - mean) / sigma0;
        double z_right = (right - mean) / sigma0;
        prob[i] = phi(z_right) - phi(z_left);
    }

    // Ожидаемые частоты
    std::vector<double> expected(numIntervals);
    for (int i = 0; i < numIntervals; ++i) {
        expected[i] = sample.size() * prob[i];
    }

    // Объединение интервалов
    std::vector<int> obs_merged;
    std::vector<double> exp_merged;
    int cur_obs = 0;
    double cur_exp = 0.0;

    for (int i = 0; i < numIntervals; ++i) {
        cur_obs += observed[i];
        cur_exp += expected[i];
        if (cur_exp >= 5.0 || i == numIntervals - 1) {
            obs_merged.push_back(cur_obs);
            exp_merged.push_back(cur_exp);
            cur_obs = 0;
            cur_exp = 0.0;
        }
    }

    // Расчёт хи-квадрат по формуле:
    // X² = Σ(n_i² / (N*p_i)) - N
    double chi2 = 0.0;
    for (size_t i = 0; i < obs_merged.size(); ++i) {
        if (exp_merged[i] > 0) {
            chi2 += (obs_merged[i] * obs_merged[i]) / exp_merged[i];
        }
    }
    chi2 -= sample.size(); // Вычитаем N

    int df = static_cast<int>(obs_merged.size()) - 1;
    if (df < 1) df = 1;

    qDebug() << "Интервалов:" << numIntervals;
    qDebug() << "После объединения:" << obs_merged.size();
    qDebug() << "χ² =" << chi2 << "df =" << df;

    return {chi2, df};
}

void MainWindow::on_startPushButton_clicked()
{
    double currentMean = ui->meanLineEdit->text().toDouble();
    double currentVariance = ui->varianceLineEdit->text().toDouble();
    unsigned int sampleSize = ui->sampleLineEdit->text().toInt();

    // Проверка ввода
    if (sampleSize == 0) {
        qDebug() << "Размер выборки должен быть больше 0";
        return;
    }

    std::vector<double> sample = NormalDistributionGenerator(currentMean, currentVariance, sampleSize);
    calculatedAvg = calculateAvg(sample);
    calculatedVariance = calculateVariance(sample,calculatedAvg);
    sigma = std::sqrt(calculatedVariance);

    QChart* chart = createBarChart(sample);
    if (chart) {
        // Очищаем старый layout, если он существует
        QLayout *oldLayout = ui->graphWidget->layout();
        if (oldLayout) {
            // Удаляем все виджеты из layout
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
        chartView->setMinimumSize(400, 300);

        // Создаем новый layout и добавляем виджет
        QVBoxLayout *layout = new QVBoxLayout(ui->graphWidget);
        layout->addWidget(chartView);
        layout->setContentsMargins(0, 0, 0, 0);
        ui->graphWidget->setLayout(layout);
    }

    auto [chi2, df] = calculateCS(sample, currentMean, currentVariance);
    calculatedChisquared = chi2;
    double criticalValue = getCriticalValue(df);

    double meanError = 0;
    if (currentMean != 0) {
        meanError = std::abs(currentMean - calculatedAvg) / std::abs(currentMean) * 100;
    } else {
        meanError = std::abs(currentMean - calculatedAvg) * 100; // если теоретическое среднее = 0
    }

    double varianceError = 0;
    if (currentVariance != 0) {
        varianceError = std::abs(currentVariance - calculatedVariance) / std::abs(currentVariance) * 100;
    } else {
        varianceError = std::abs(currentVariance - calculatedVariance) * 100;
    }


    ui->Avglabel->setText("Average: " + QString::number(calculatedAvg, 'f', 4) +
                          " (error = " + QString::number(meanError, 'f', 2) + "%)");
    ui->VarianceLabel->setText("Variance: " + QString::number(calculatedVariance, 'f', 4) +
                               " (error = " + QString::number(varianceError, 'f', 2) + "%)");
    ui->CSlabel->setText("Chi-Squared: " + QString::number(calculatedChisquared, 'f', 2) +
                         "/ CriticalValue: " + QString::number(criticalValue, 'f', 2));
}

