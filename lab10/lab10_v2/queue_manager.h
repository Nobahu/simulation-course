#pragma once

#include "requirement.h"
#include <queue>
#include <memory>
#include <vector>

class EventManager;

struct QueueEntry {
    std::shared_ptr<Requirement> req;
    double enqueueTime;
};

class QueueManager {
public:
    static QueueManager& get() {
        static QueueManager instance;
        return instance;
    }

    void push(std::shared_ptr<Requirement> req, double enqueueTime) {
        queue_.push({req, enqueueTime});
    }

    std::shared_ptr<Requirement> pop() {
        if (queue_.empty()) return nullptr;

        QueueEntry entry = queue_.front();
        queue_.pop();

        // Сохраняем время ожидания
        double now = getCurrentTime();  // выносим в отдельный метод
        entry.req->setQueueTime(now - entry.enqueueTime);

        return entry.req;
    }

    size_t size() const {
        return queue_.size();
    }

    bool empty() const {
        return queue_.empty();
    }

    void reset() {
        while (!queue_.empty()) queue_.pop();
    }

private:
    double getCurrentTime() const;

    QueueManager() = default;
    std::queue<QueueEntry> queue_;
};
