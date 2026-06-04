#pragma once

#include "processingdevice.h"

#include <vector>
#include <memory>
#include <algorithm>

class ProcessingDevice;

class DeviceManager {
public:
    static DeviceManager& get() {
        static DeviceManager instance;
        return instance;
    }

    void addDevice(std::shared_ptr<ProcessingDevice> device) {
        devices_.emplace_back(device);
    }

    std::shared_ptr<ProcessingDevice> findFreeDevice() {
        for (auto& device : devices_) {
            if (device->isFree()) {
                return device;
            }
        }
        return nullptr;
    }

    std::vector<std::shared_ptr<ProcessingDevice>>& getAllDevices() {
        return devices_;
    }

    void reset() {
        devices_.clear();
    }

private:
    DeviceManager() = default;
    std::vector<std::shared_ptr<ProcessingDevice>> devices_;
};
