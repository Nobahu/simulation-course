#include "requirement.h"
#include "processingdevice.h"
#include "device_manager.h"
#include "queue_manager.h"
#include "event_manager.h"

Requirement::Requirement(double arrivalTime)
    : arrivalTime_(arrivalTime), queueTime_(0), serviceTime_(0) {}

void Requirement::tryEnterSystem() {

    auto freeDevice = DeviceManager::get().findFreeDevice();

    if (freeDevice) {
        // Есть свободный канал, то начинаем обслуживание
        startService(freeDevice);
    } else {
        // Если нет свободного, то встаём в очередь и сохраняем время начала ожидания
        double now = EventManager::get().getCurrentTime();
        QueueManager::get().push(shared_from_this(), now);
    }
}

void Requirement::startService(std::shared_ptr<ProcessingDevice> device) {
    // Заявка сама передаёт себя каналу
    device->accept(shared_from_this());
}
