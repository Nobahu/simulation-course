#ifndef MARKPROCESS_H
#define MARKPROCESS_H

#include <iostream>
#include <vector>
#include <random>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <chrono>

class MarkovApp
{
public:
    MarkovApp() : currentState(1), totalTime(0.0) {
        matrix = {
            {0.0, 0.2, 0.05},
            {0.15, 0.0, 0.2},
            {0.05, 0.3, 0.0}
        };
        updateDiagonals();

        // Инициализация статистики
        stateVisitCount = {0, 0, 0};
        stateDurationsSum = {0.0, 0.0, 0.0};
        stateDurationsSumSq = {0.0, 0.0, 0.0};
    }

    void process(double hours = 720)
    {
        history.clear();
        historyTime.clear();
        std::fill(timeInState.begin(), timeInState.end(), 0.0);

        // Сброс статистики
        std::fill(stateVisitCount.begin(), stateVisitCount.end(), 0);
        std::fill(stateDurationsSum.begin(), stateDurationsSum.end(), 0.0);
        std::fill(stateDurationsSumSq.begin(), stateDurationsSumSq.end(), 0.0);

        totalTime = 0.0;

        std::vector<double> initialProbs = {0.4, 0.4, 0.2};
        currentState = getDiscreteState(rng.nextDouble(), initialProbs) + 1;

        logEvents.clear();
        logEvents.push_back("СТАРТ. Начало: " + stateNames[currentState - 1]);

        history.push_back(currentState);

        while (totalTime < hours) {
            double q_ii = Q[currentState - 1][currentState - 1];
            if (q_ii >= 0) break;

            double lambda = -q_ii;
            double u = rng.nextDouble();
            double tau = -std::log(1.0 - u) / lambda;

            if (totalTime + tau > hours) {
                tau = hours - totalTime;
            }

            // Накопление статистики для ТЕКУЩЕГО состояния (выход из него)
            stateVisitCount[currentState - 1]++;
            stateDurationsSum[currentState - 1] += tau;
            stateDurationsSumSq[currentState - 1] += tau * tau;

            timeInState[currentState - 1] += tau;
            totalTime += tau;

            logEvents.push_back("[" + formatTime(totalTime - tau) + " - " + formatTime(totalTime) +
                                "] " + stateNames[currentState - 1] + " | Дл: " + formatDuration(tau));

            if (totalTime >= hours - 1e-9) break;

            // Выбор следующего состояния
            double r = rng.nextDouble();
            double cum = 0.0;

            for (int j = 0; j < 3; ++j) {
                if (j == currentState - 1) continue;
                cum += Q[currentState - 1][j] / lambda;
                if (r <= cum) {
                    currentState = j + 1;
                    break;
                }
            }

            // Заполнение истории для графика
            int currentHour = (int)totalTime;
            while ((int)history.size() <= currentHour) {
                history.push_back(currentState);
            }
        }

        while ((int)history.size() <= (int)hours) {
            history.push_back(currentState);
        }

        calculateEmpDistr(hours);
        calculateTheoreticalDistr();

        saveToCSV(hours);
    }

    std::vector<int> getHistory() const { return history; }
    std::vector<double> getTheoreticalDistr() const { return theoreticalDistr; }
    std::vector<double> getEmpDistr() const { return empDistr; }
    std::vector<std::vector<double>> getMatrix() const { return matrix; }
    std::vector<std::string> getLogEvents() const { return logEvents; }

    void setMatrix(std::vector<std::vector<double>> newMatrix) {
        matrix = newMatrix;
        updateDiagonals();
    }

private:
    void updateDiagonals() {
        Q = matrix;
        for (int i = 0; i < 3; ++i) {
            double sum = 0.0;
            for (int j = 0; j < 3; ++j) {
                if (i != j) sum += matrix[i][j];
            }
            Q[i][i] = -sum;
        }
    }

    void saveToCSV(double totalHours) {
        std::ofstream file("weather_stats.csv");
        if (!file.is_open()) return;

        // ===== 1. Распределение вероятностей =====
        file << "=== РАСПРЕДЕЛЕНИЕ ВЕРОЯТНОСТЕЙ ===\n";
        file << "State;Empirical;Theoretical;Error\n";
        for (int i = 0; i < 3; ++i) {
            double error = std::abs(empDistr[i] - theoreticalDistr[i]);
            file << stateNames[i] << ";"
                 << std::fixed << std::setprecision(4) << empDistr[i] << ";"
                 << theoreticalDistr[i] << ";"
                 << error << "\n";
        }

        // ===== 2. Статистика посещений =====
        file << "\n=== СТАТИСТИКА ПОСЕЩЕНИЙ ===\n";
        file << "State;VisitCount;TotalTime(hours)\n";
        for (int i = 0; i < 3; ++i) {
            file << stateNames[i] << ";"
                 << stateVisitCount[i] << ";"
                 << std::fixed << std::setprecision(2) << timeInState[i] << "\n";
        }

        // ===== 3. Мат.ожидание и дисперсия (эмпирические vs теоретические) =====
        file << "\n=== МАТ.ОЖИДАНИЕ И ДИСПЕРСИЯ ВРЕМЕНИ ПРЕБЫВАНИЯ ===\n";
        file << "State;Mean_empirical(hours);Variance_empirical(hours^2);Mean_theoretical(hours);Variance_theoretical(hours^2)\n";

        for (int i = 0; i < 3; ++i) {
            // Эмпирические значения
            double meanEmp = 0.0;
            double varEmp = 0.0;
            if (stateVisitCount[i] > 0) {
                meanEmp = stateDurationsSum[i] / stateVisitCount[i];
                if (stateVisitCount[i] > 1) {
                    varEmp = (stateDurationsSumSq[i] - stateDurationsSum[i] * stateDurationsSum[i] / stateVisitCount[i])
                             / (stateVisitCount[i] - 1);
                }
            }

            // Теоретические значения (для экспоненциального распределения)
            double lambda = -Q[i][i];
            double meanTheo = 1.0 / lambda;
            double varTheo = 1.0 / (lambda * lambda);

            file << stateNames[i] << ";"
                 << std::fixed << std::setprecision(4) << meanEmp << ";"
                 << varEmp << ";"
                 << meanTheo << ";"
                 << varTheo << "\n";
        }

        file.close();
    }

    std::string formatTime(double hours) {
        int h = (int)hours;
        int m = (int)((hours - h) * 60);
        char buf[16];
        snprintf(buf, sizeof(buf), "%02d:%02d", h, m);
        return std::string(buf);
    }

    std::string formatDuration(double hours) {
        int h = (int)hours;
        int m = (int)((hours - h) * 60);
        char buf[32];
        snprintf(buf, sizeof(buf), "%dч %02dм", h, m);
        return std::string(buf);
    }

    int getDiscreteState(double r, const std::vector<double>& probs) {
        double cum = 0.0;
        for (size_t i = 0; i < probs.size(); ++i) {
            cum += probs[i];
            if (r <= cum) return i;
        }
        return probs.size() - 1;
    }

    void calculateTheoreticalDistr() {
        double A[3][3] = {
            {Q[0][0], Q[1][0], Q[2][0]},
            {Q[0][1], Q[1][1], Q[2][1]},
            {1.0, 1.0, 1.0}
        };
        double B[3] = {0.0, 0.0, 1.0};

        auto det3 = [](double m[3][3]) -> double {
            return m[0][0] * (m[1][1] * m[2][2] - m[1][2] * m[2][1])
                   - m[0][1] * (m[1][0] * m[2][2] - m[1][2] * m[2][0])
                   + m[0][2] * (m[1][0] * m[2][1] - m[1][1] * m[2][0]);
        };

        double det = det3(A);
        if (std::abs(det) < 1e-9) {
            theoreticalDistr = {1.0/3.0, 1.0/3.0, 1.0/3.0};
            return;
        }

        theoreticalDistr.resize(3);
        for (int i = 0; i < 3; ++i) {
            double Ai[3][3];
            std::copy(&A[0][0], &A[0][0] + 9, &Ai[0][0]);
            Ai[0][i] = B[0];
            Ai[1][i] = B[1];
            Ai[2][i] = B[2];
            theoreticalDistr[i] = det3(Ai) / det;
        }
    }

    void calculateEmpDistr(double totalHours) {
        empDistr.clear();
        for (int i = 0; i < 3; ++i) {
            empDistr.push_back(timeInState[i] / totalHours);
        }
    }

    class RNG {
        std::mt19937_64 rng;
        std::uniform_real_distribution<double> dist;
    public:
        RNG() : rng(std::chrono::steady_clock::now().time_since_epoch().count()), dist(0.0, 1.0) {}
        double nextDouble() { return dist(rng); }
    } rng;

    const std::vector<std::string> stateNames = {"Ясно", "Облачно", "Пасмурно"};

    std::vector<std::vector<double>> matrix;
    std::vector<std::vector<double>> Q;

    std::vector<double> theoreticalDistr;
    std::vector<double> empDistr;
    std::vector<double> timeInState = {0.0, 0.0, 0.0};

    // Статистика для мат.ожидания и дисперсии
    std::vector<int> stateVisitCount;
    std::vector<double> stateDurationsSum;
    std::vector<double> stateDurationsSumSq;

    std::vector<int> history;
    std::vector<double> historyTime;
    std::vector<std::string> logEvents;

    int currentState;
    double totalTime;
};

#endif // MARKPROCESS_H
