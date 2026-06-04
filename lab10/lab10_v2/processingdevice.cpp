#include "processingdevice.h"
#include "event_manager.h"
#include "queue_manager.h"

ProcessingDevice::ProcessingDevice(double mu)
    : mu_(mu) {}

void ProcessingDevice::start() {}

void ProcessingDevice::accept(std::shared_ptr<Requirement> req) {
    if (isBusy_) return;

    isBusy_ = true;
    currentReq_ = req;

    // Генерируем время обслуживания
    double serviceTime = LCG::get().generate( mu_ );
    currentServiceTime_ = serviceTime;

    // Запоминаем время обслуживания в заявке
    currentReq_->setServiceTime(serviceTime);

    // Планируем завершение
    scheduleCompletion(serviceTime);
}

void ProcessingDevice::scheduleCompletion(double serviceTime) {
    double completeTime = EventManager::get().getCurrentTime() + serviceTime;

    EventManager::get().scheduleEvent(
        completeTime,
        [self = shared_from_this()]() {
            self->completeService();
        }
        );
}

void ProcessingDevice::completeService() {
    // Сохраняем статистику
    double serviceEnd = EventManager::get().getCurrentTime();
    totalBusyTime_ += currentServiceTime_;

    if (currentReq_) {
        StatisticsCollector::get().addCompletedRequirement(currentReq_);
    }

    // Освобождаем прибор
    isBusy_ = false;
    currentReq_.reset();
    currentServiceTime_ = 0;

    // Ище следующую заявку в очереди
    auto nextReq = QueueManager::get().pop();
    if (nextReq) {
        // Есть заявка в очереди — начинаем обслуживать
        accept(nextReq);
    }
}
