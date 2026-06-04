#ifndef REQUIREMENT_H
#define REQUIREMENT_H

#include <memory>
#include <functional>

class ProcessingDevice;
class QueueManager;

class Requirement : public std::enable_shared_from_this<Requirement>
{
public:
    explicit Requirement(double arrivalTime);

    /// Действия
    void tryEnterSystem();                    // попытаться войти в систему
    void startService(std::shared_ptr<ProcessingDevice> device);  // начать обслуживание

    void setServiceTime(double time) { serviceTime_ = time; }
    void setQueueTime(double t) { queueTime_ = t; }

    double getArrivalTime() const { return arrivalTime_; }
    double getQueueTime() const { return queueTime_; }
    double getServiceTime() const { return serviceTime_; }

private:
    double arrivalTime_;      // время прихода в систему
    double queueTime_;        // время в очереди
    double serviceTime_;      // время обслуживания
};

#endif // REQUIREMENT_H
