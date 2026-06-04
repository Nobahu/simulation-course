#pragma once

#include "random_generator.h"
#include "statistic_collector.h"
#include "requirement.h"
#include <memory>
#include <functional>

class ProcessingDevice : public std::enable_shared_from_this<ProcessingDevice>
{
public:
    explicit ProcessingDevice(double mu);

    // === ДЕЙСТВИЯ АГЕНТА ===
    void start();                              // запустить прибор (после создания)
    void accept(std::shared_ptr<Requirement> req);  // принять заявку
    void completeService();                    // завершить обслуживание (сам)

    // === ДЛЯ ПОИСКА СВОБОДНЫХ ===
    bool isFree() const { return !isBusy_; }

    // === ДЛЯ СТАТИСТИКИ ===
    double getTotalBusyTime() const { return totalBusyTime_; }

private:
    void scheduleCompletion(double serviceTime);  // запланировать завершение

    bool isBusy_ = false;
    double mu_;
    double currentServiceTime_ = 0;
    double totalBusyTime_ = 0;
    std::shared_ptr<Requirement> currentReq_;
};
