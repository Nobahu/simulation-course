#include "mainsystem.h"
#include <iostream>
#include <iomanip>
#include <algorithm>

MainSystem::MainSystem(double lambda, double mu, double modeling_time)
    : lambda_(lambda), mu_(mu), modeling_time_(modeling_time)
{
    stream_ = std::make_unique<PoissonStream>(lambda);
    device_ = std::make_unique<ProcessingDevice>(mu);
}

void MainSystem::RunImmitation()
{
    double t = 0;
    double ta = stream_->GenerateTau();
    double ts;

    // Сохраняем начальное состояние
    systemStates_.push_back(std::make_pair(t, 0));  // Начинаем с состояния "свободен"

    while (t < modeling_time_)
    {
        ts = device_->GetCurrentServiceTime();

        if (ta <= ts || !device_->IsBusy())
        {
            // СОБЫТИЕ: Приход новой заявки
            t += ta;

            if (!device_->IsBusy())
            {
                // Устройство свободно - принимаем заявку
                device_->AcceptRequirement();
                double serviceTime = device_->GetCurrentServiceTime();
                serviceTimes_.push_back(serviceTime);
                totalServiceTime_ += serviceTime;
                servedRequirements++;

                // Сохраняем состояние после принятия заявки (система стала занята)
                systemStates_.push_back(std::make_pair(t, 1));
            }
            else
            {
                // Устройство занято - заявка теряется
                device_->TimeSubstraction(ta);
                lostRequirements++;

                // Состояние не меняется (остается занятым)
                systemStates_.push_back(std::make_pair(t, 1));
            }

            // Генерируем следующую заявку
            ta = stream_->GenerateTau();
        }
        else
        {
            // СОБЫТИЕ: Завершение обслуживания
            t += ts;
            ta -= ts;

            device_->FinishService();

            // Сохраняем состояние после завершения (система стала свободна)
            systemStates_.push_back(std::make_pair(t, 0));
        }
    }
}

int MainSystem::GetLostRequirements() const
{
    return lostRequirements;
}

int MainSystem::GetServedRequirements() const
{
    return servedRequirements;
}

int MainSystem::GetTotalRequirements() const
{
    return servedRequirements + lostRequirements;
}

double MainSystem::GetLossProbability() const
{
    int total = GetTotalRequirements();
    return total == 0 ? 0.0 : static_cast<double>(lostRequirements) / total;
}

double MainSystem::GetServiceProbability() const
{
    int total = GetTotalRequirements();
    return total == 0 ? 0.0 : static_cast<double>(servedRequirements) / total;
}

double MainSystem::GetAverageServiceTime() const
{
    return servedRequirements == 0 ? 0.0 : totalServiceTime_ / servedRequirements;
}

double MainSystem::GetAverageClients() const
{
    if (systemStates_.empty()) return 0.0;

    double totalTimeWithClients = 0.0;
    double lastTime = systemStates_[0].first;

    for (size_t i = 1; i < systemStates_.size(); i++)
    {
        double currentTime = systemStates_[i].first;
        int state = systemStates_[i-1].second;
        double duration = currentTime - lastTime;

        if (state == 1)  // Система занята
        {
            totalTimeWithClients += duration;
        }

        lastTime = currentTime;
    }

    return totalTimeWithClients / modeling_time_;
}

double MainSystem::CalculateRho() const
{
    return lambda_ / mu_;
}

double MainSystem::CalculateP0Theory() const
{
    double rho = CalculateRho();
    return 1.0 / (1.0 + rho);
}

double MainSystem::CalculatePLossTheory() const
{
    double rho = CalculateRho();
    return rho / (1.0 + rho);
}

double MainSystem::CalculateLAverageTheory() const
{
    return CalculatePLossTheory();
}

void MainSystem::GetStateDistribution(std::vector<int>& states,
                                      std::vector<double>& probabilities) const
{
    if (systemStates_.empty())
    {
        states.clear();
        probabilities.clear();
        return;
    }

    std::vector<double> timeInState(2, 0.0);  // [свободен, занят]
    double lastTime = systemStates_[0].first;

    for (size_t i = 1; i < systemStates_.size(); i++)
    {
        double currentTime = systemStates_[i].first;
        int state = systemStates_[i-1].second;
        double duration = currentTime - lastTime;

        if (duration > 0)  // Добавляем только положительные интервалы
        {
            timeInState[state] += duration;
        }

        lastTime = currentTime;
    }

    states.clear();
    probabilities.clear();

    for (int state = 0; state < 2; state++)
    {
        states.push_back(state);
        probabilities.push_back(timeInState[state] / modeling_time_);
    }
}

double MainSystem::GetStateProbability(int state) const
{
    std::vector<int> states;
    std::vector<double> probs;
    GetStateDistribution(states, probs);

    for (size_t i = 0; i < states.size(); i++)
    {
        if (states[i] == state)
            return probs[i];
    }
    return 0.0;
}

void MainSystem::PrintResults() const
{
    std::cout << "\n" << std::string(70, '=') << std::endl;
    std::cout << "  РЕЗУЛЬТАТЫ МОДЕЛИРОВАНИЯ СИСТЕМЫ M/M/1/0" << std::endl;
    std::cout << std::string(70, '=') << std::endl;

    std::cout << "\n【ПАРАМЕТРЫ СИСТЕМЫ】" << std::endl;
    std::cout << "  λ (интенсивность входа)     = " << std::fixed << std::setprecision(4) << lambda_ << std::endl;
    std::cout << "  μ (интенсивность обслужив.) = " << mu_ << std::endl;
    std::cout << "  ρ = λ/μ                     = " << CalculateRho() << std::endl;
    std::cout << "  T (время моделирования)     = " << modeling_time_ << std::endl;

    std::cout << "\n【СТАТИСТИКА ОБСЛУЖИВАНИЯ】" << std::endl;
    std::cout << "  Всего поступило заявок      = " << GetTotalRequirements() << std::endl;
    std::cout << "  Обслужено заявок            = " << servedRequirements << std::endl;
    std::cout << "  Потеряно заявок             = " << lostRequirements << std::endl;
    std::cout << "  Вероятность отказа          = " << std::fixed << std::setprecision(6)
              << GetLossProbability() << " (" << GetLossProbability() * 100 << "%)" << std::endl;
    std::cout << "  Вероятность обслуживания    = " << GetServiceProbability()
              << " (" << GetServiceProbability() * 100 << "%)" << std::endl;

    std::cout << "\n【СРЕДНИЕ ХАРАКТЕРИСТИКИ】" << std::endl;
    std::cout << "  Среднее время обслуживания  = " << std::fixed << std::setprecision(6)
              << GetAverageServiceTime() << " ед.времени" << std::endl;
    std::cout << "  Среднее число клиентов в СМО= " << GetAverageClients() << std::endl;

    std::cout << "\n【РАСПРЕДЕЛЕНИЕ СОСТОЯНИЙ】" << std::endl;
    std::vector<int> states;
    std::vector<double> probs;
    GetStateDistribution(states, probs);

    for (size_t i = 0; i < states.size(); i++)
    {
        std::string stateName = (states[i] == 0) ? "Свободен" : "Занят";
        std::cout << "  " << stateName << " (состояние " << states[i] << "): "
                  << std::fixed << std::setprecision(6) << probs[i]
                  << " (" << probs[i] * 100 << "% времени)" << std::endl;
    }
}

void MainSystem::PrintComparisonWithTheory() const
{
    std::cout << "\n" << std::string(70, '=') << std::endl;
    std::cout << "  СРАВНЕНИЕ ТЕОРИИ И ПРАКТИКИ (Формулы Эрланга)" << std::endl;
    std::cout << std::string(70, '=') << std::endl;

    // Заголовок с правильными ширинами колонок
    std::cout << std::left << std::setw(35) << "  Параметр"
              << std::right << std::setw(15) << "Теория"
              << std::setw(15) << "Практика"
              << std::setw(15) << "Погрешность" << std::endl;
    std::cout << std::string(70, '-') << std::endl;

    double rho = CalculateRho();
    double p0_theory = CalculateP0Theory();
    double p0_prac = GetStateProbability(0);
    double p0_error = std::abs(p0_prac - p0_theory) / p0_theory * 100;

    std::cout << std::left << std::setw(35) << "  Интенсивность нагрузки (ρ)"
              << std::right << std::setw(15) << std::fixed << std::setprecision(6) << rho
              << std::setw(15) << "---"
              << std::setw(15) << "---" << std::endl;

    std::cout << std::left << std::setw(35) << "  Вероятность простоя (P0)"
              << std::right << std::setw(15) << p0_theory
              << std::setw(15) << p0_prac
              << std::setw(14) << std::setprecision(6) << p0_error << "%" << std::endl;

    double p_loss_theory = CalculatePLossTheory();
    double p_loss_prac = GetLossProbability();
    double p_loss_error = std::abs(p_loss_prac - p_loss_theory) / p_loss_theory * 100;

    std::cout << std::left << std::setw(35) << "  Вероятность отказа (P_loss)"
              << std::right << std::setw(15) << p_loss_theory
              << std::setw(15) << p_loss_prac
              << std::setw(14) << p_loss_error << "%" << std::endl;

    double L_theory = CalculateLAverageTheory();
    double L_prac = GetAverageClients();
    double L_error = std::abs(L_prac - L_theory) / L_theory * 100;

    std::cout << std::left << std::setw(35) << "  Среднее число клиентов (L)"
              << std::right << std::setw(15) << L_theory
              << std::setw(15) << L_prac
              << std::setw(14) << L_error << "%" << std::endl;

    std::cout << std::string(70, '-') << std::endl;

    // Анализ погрешности
    std::cout << "\n【АНАЛИЗ ТОЧНОСТИ】" << std::endl;
    std::cout << "  Максимальная погрешность: " << std::max({p0_error, p_loss_error, L_error}) << "%" << std::endl;
    std::cout << "  Средняя погрешность: " << (p0_error + p_loss_error + L_error) / 3.0 << "%" << std::endl;

    std::cout << "\n" << std::string(70, '=') << std::endl;
}
