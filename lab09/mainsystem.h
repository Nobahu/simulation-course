#ifndef MAINSYSTEM_H
#define MAINSYSTEM_H

#include <memory>
#include "processing_device.h"
#include "stream.h"

class MainSystem
{
public:

    MainSystem( double lambda, double mu, double modeling_time );

    void RunImmitation();

    int GetLostRequirements() const;
    int GetServedRequirements() const;
    int GetTotalRequirements() const;

    double GetLossProbability() const;
    double GetServiceProbability() const;

    double GetAverageServiceTime() const;
    double GetAverageClients() const;

    double CalculateRho() const;                        // ρ = λ/μ
    double CalculateP0Theory() const;                   // Вероятность простоя
    double CalculatePLossTheory() const;                // Вероятность отказа
    double CalculateLAverageTheory() const;             // Среднее число клиентов

    void GetStateDistribution(std::vector<int>& states, std::vector<double>& probabilities) const;
    double GetStateProbability(int state) const;

    void PrintResults() const;
    void PrintComparisonWithTheory() const;             // Сравнение с теорией


private:

    double lambda_;
    double mu_;
    double modeling_time_;
    std::unique_ptr< ProcessingDevice > device_;
    std::unique_ptr< PoissonStream > stream_;

    int servedRequirements = 0;
    int lostRequirements = 0;

    std::vector<double> serviceTimes_; // Времена обслуживания обслуженных заявок
    std::vector<std::pair<double, int>> systemStates_; // (время, состояние: 0-свободен, 1-занят)
    double totalServiceTime_ = 0; // Суммарное время обслуживания
};

#endif // MAINSYSTEM_H
