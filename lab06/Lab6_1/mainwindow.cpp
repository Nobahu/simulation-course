#include "mainwindow.h"
#include "./ui_mainwindow.h"

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

// Равномерное распределение
int MainWindow::generateUniformDiscrete()
{
    static const unsigned short a = 1;
    static const unsigned short b = 5;

    static unsigned short n = b - a;

    static std::random_device rd;
    static std::mt19937_64 mtgen(rd());
    static std::uniform_real_distribution<double> distr(0.0, 1.0);

    double alpha = distr(mtgen);
    int x = static_cast<int>(alpha * (n + 1));
    x += a;

    return x;
}
std::vector<int> MainWindow::generateUniformSample(const unsigned int& n)
{
    std::vector<int> results;
    results.reserve(n);

    for(size_t i = 0; i < n; i++) {
        results.push_back(generateUniformDiscrete());
    }

    return results;
}

// Генерация методом обратной функции
int MainWindow::generateCustomDiscrete(const std::vector<double>& probs)
{
    static std::random_device rd;
    static std::mt19937_64 mtgen(rd());
    static std::uniform_real_distribution<double> distr(0.0, 1.0);

    double alpha = distr(mtgen);
    double sum = 0;

    for (size_t i = 0; i < probs.size(); i++) {
        sum += probs[i];
        if (alpha < sum) {
            return i + 1;  // возвращаем номер интервала (1-5)
        }
    }
    return probs.size();  // на всякий случай
}
std::vector<int> MainWindow::generateCustomSample(const unsigned int& n, const std::vector<double>& probs)
{
    std::vector<int> results;
    results.reserve(n);

    for (size_t i = 0; i < n; i++) {
        results.push_back(generateCustomDiscrete(probs));
    }

    return results;
}

void MainWindow::calculateStats(const std::vector<double>& probs)
{
    mean = 0;
    variance = 0;

    for(size_t i = 0;i < probs.size();i++) {
        mean += probs[i] * (i + 1);
    }
    for(size_t i = 0;i < probs.size();i++) {
        variance += probs[i] * std::pow((i + 1) - mean,2);
    }
}

void MainWindow::calculateEmpStats(const std::vector<int>& sample)
{
    empMean = 0;
    empVariance = 0;

    //Частоты
    std::vector<int> frequencies(5, 0);
    for (int el : sample) {
        frequencies[el - 1]++;
    }

    std::vector<double> empiricalfreq(5);
    for(int i = 0;i < 5;i++) {
        empiricalfreq[i] = static_cast<double>(frequencies[i]) / sample.size();
    }

    for(int i = 0;i < 5;i++) {
        empMean += empiricalfreq[i] * (i + 1);
    }

    for(int i = 0;i < 5;i++) {
        empVariance += empiricalfreq[i] * (std::pow((i+1) - empMean,2));
    }

}

std::pair<double, int> MainWindow::calculateChiSquared(const std::vector<int>& sample,
                                                       const std::vector<double>& probs)
{
    int N = sample.size();
    int m = probs.size();  // количество значений (5)

    // Подсчет наблюдаемых частот
    std::vector<int> observed(m, 0);
    for (int val : sample) {
        observed[val - 1]++;
    }

    // Расчет хи-квадрат по формуле: χ² = Σ (n_i² / (N * p_i)) - N
    double chi2 = 0.0;
    for (int i = 0; i < m; ++i) {
        double expected = N * probs[i];
        if (expected > 0) {
            chi2 += (observed[i] * observed[i]) / expected;
        }
    }
    chi2 -= N;

    int df = m - 1;  // степени свободы

    return {chi2, df};
}

QChart* MainWindow::createBarChart(const std::vector<double>& sample)
{
    QStringList probNums;
    probNums << "1" << "2" << "3" << "4" << "5";

    QBarSet *set = new QBarSet("Вероятность");
    for (double el : sample) {
        *set << el;
    }

    QBarSeries *series = new QBarSeries();
    series->append(set);

    QChart* barChart = new QChart();
    barChart->addSeries(series);
    barChart->setAnimationOptions(QChart::SeriesAnimations);
    barChart->setTitle("Гистограмма вероятностей"); // Добавлен заголовок

    // Настройка оси X
    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    axisX->append(probNums);
    axisX->setTitleText("Интервалы");
    barChart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    // Настройка оси Y
    QValueAxis *axisY = new QValueAxis();
    axisY->setTitleText("Вероятность");

    // Находим максимальное значение (исправлено)
    double maxProb = sample.empty() ? 1.0 : *std::max_element(sample.begin(), sample.end());
    axisY->setRange(0, maxProb * 1.1);
    axisY->setLabelFormat("%.2f");
    barChart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    return barChart;
}

void MainWindow::on_startPushButton_2_clicked()
{
    if(ui->comboBox->currentText() == "Uniform_distr")
    {
        ui->probLineEdit_1->setText("0.2");
        ui->probLineEdit_2->setText("0.2");
        ui->probLineEdit_3->setText("0.2");
        ui->probLineEdit_4->setText("0.2");
        ui->probLineEdit_5->setText("0.2");
    }

    std::vector<double> probs;
    probs.push_back(ui->probLineEdit_1->text().toDouble());
    probs.push_back(ui->probLineEdit_2->text().toDouble());
    probs.push_back(ui->probLineEdit_3->text().toDouble());
    probs.push_back(ui->probLineEdit_4->text().toDouble());
    probs.push_back(ui->probLineEdit_5->text().toDouble());

    double sum = 0;
    for (double p : probs) {
        sum += p;
    }

    if(std::abs(sum - 1.0) > 1e-6) {
        QMessageBox::warning(this, "Ошибка ввода",
                             QString("Сумма вероятностей = %1\nДолжна быть равна 1").arg(sum, 0, 'f', 4));
        return;
    }

    for (double p : probs) {
        if (p < 0) {
            QMessageBox::warning(this, "Ошибка", "Вероятности не могут быть отрицательными");
            return;
        }
    }

    calculateStats(probs);

    int n = ui->numexprLineEdit->text().toInt();
    std::vector<int> expr_sample;

    if (ui->comboBox->currentText() == "Uniform_distr")
    {
        expr_sample = generateUniformSample(n);
    }
    else if (ui->comboBox->currentText() == "Custom")
    {
        expr_sample = generateCustomSample(n, probs);
    }

    calculateEmpStats(expr_sample);
    auto [chi2, df] = calculateChiSquared(expr_sample, probs);

    std::vector<int> frequencies(5, 0);
    for (int el : expr_sample) {
        frequencies[el - 1]++;
    }

    std::vector<double> empiricalProbs(5);
    for(int i = 0; i < 5; i++) {
        empiricalProbs[i] = static_cast<double>(frequencies[i]) / expr_sample.size();
    }

    // Обновление текста
    ui->Avglabel->setText(QString("Average: %1 (theor: %2)")
                              .arg(empMean, 0, 'f', 4)
                              .arg(mean, 0, 'f', 4));

    ui->VarianceLabel->setText(QString("Variance: %1 (theor: %2)")
                                   .arg(empVariance, 0, 'f', 4)
                                   .arg(variance, 0, 'f', 4));

    double criticalValue = 9.488;
    ui->CSlabel->setText(QString("Chi-Squared: %1 (crit: %2) %3")
                             .arg(chi2, 0, 'f', 4)
                             .arg(criticalValue)
                             .arg(chi2 < criticalValue ? "PASSED" : "FAILED"));

    QChart* chart = createBarChart(empiricalProbs);
    if (chart) {
        QLayout *oldLayout = ui->graphWidget->layout();
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
        chartView->setMinimumSize(400, 300);

        QVBoxLayout *layout = new QVBoxLayout(ui->graphWidget);
        layout->addWidget(chartView);
        layout->setContentsMargins(0, 0, 0, 0);
        ui->graphWidget->setLayout(layout);
    }
}


void MainWindow::on_autoPushButton_clicked()
{
    double sum = 0;
    sum += ui->probLineEdit_1->text().toDouble();
    sum += ui->probLineEdit_2->text().toDouble();
    sum += ui->probLineEdit_3->text().toDouble();
    sum += ui->probLineEdit_4->text().toDouble();

    if (1 - sum < 0) {
        QMessageBox::warning(this, "Ошибка", "Сумма первых четырех вероятностей > 1");
        return;
    }

    ui->probLineEdit_5->setText(QString::number(1 - sum));
}

