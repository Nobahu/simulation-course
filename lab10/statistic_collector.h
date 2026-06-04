#pragma once

#include <vector>
#include <memory>
#include "requirement.h"

class StatisticsCollector {
public:
    static StatisticsCollector& get() {
        static StatisticsCollector instance;
        return instance;
    }

    void addCompletedRequirement(std::shared_ptr<Requirement> req) {
        completedRequirements_.push_back(req);
    }

    double getAverageServiceTime() const {
        if (completedRequirements_.empty()) return 0;
        double total = 0;
        for (const auto& req : completedRequirements_) {
            total += req->getServiceTime();
        }
        return total / completedRequirements_.size();
    }

    double getAverageQueueTime() const {
        if (completedRequirements_.empty()) return 0;
        double total = 0;
        for (const auto& req : completedRequirements_) {
            total += req->getQueueTime();
        }
        return total / completedRequirements_.size();
    }

    void recordState(int state, double duration) {
        if (state >= stateTimes_.size()) {
            stateTimes_.resize(state + 1, 0.0);
        }
        stateTimes_[state] += duration;
    }

    std::vector<double> getStateProbabilities(double totalTime) const {
        std::vector<double> probs;
        for (double t : stateTimes_) {
            probs.push_back(t / totalTime);
        }
        return probs;
    }

    void reset() {
        completedRequirements_.clear();
        stateTimes_.clear();
    }

    size_t getTotalServed() const { return completedRequirements_.size(); }

private:
    std::vector<std::shared_ptr<Requirement>> completedRequirements_;
    std::vector<double> stateTimes_;
};
