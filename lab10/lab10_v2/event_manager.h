#pragma once

#include <queue>
#include <functional>
#include <vector>
#include <algorithm>
#include "statistic_collector.h"
#include "device_manager.h"
#include "queue_manager.h"

struct Event {
    double time;
    std::function<void()> callback;

    bool operator<(const Event& other) const {
        return time > other.time;  // min-heap
    }
};

class EventManager {
public:
    static EventManager& get() {
        static EventManager instance;
        return instance;
    }

    void scheduleEvent(double time, std::function<void()> callback) {
        events_.push({time, callback});
    }

    void run(double modellingTime) {
        double lastTime = 0;
        int lastState = 0;
        bool first = true;

        while (!events_.empty() && currentTime_ < modellingTime) {
            Event nextEvent = events_.top();
            events_.pop();

            if (nextEvent.time > modellingTime) break;

            // Записываем состояние до перехода
            if (!first) {
                double duration = nextEvent.time - lastTime;
                StatisticsCollector::get().recordState(lastState, duration);
            }

            currentTime_ = nextEvent.time;
            nextEvent.callback();

            // Сохраняем новое состояние
            lastTime = currentTime_;
            lastState = getCurrentState();
            first = false;
        }
    }

    double getCurrentTime() const { return currentTime_; }
    void reset() {
        while (!events_.empty()) events_.pop();
        currentTime_ = 0;
    }

private:

    int getCurrentState() const {
        int busyChannels = 0;
        for (auto& device : DeviceManager::get().getAllDevices()) {
            if (!device->isFree()) busyChannels++;
        }
        return busyChannels + QueueManager::get().size();
    }

    EventManager() = default;
    std::priority_queue<Event> events_;
    double currentTime_ = 0;
};
