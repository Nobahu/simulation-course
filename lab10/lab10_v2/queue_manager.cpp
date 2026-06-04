#include "queue_manager.h"
#include "event_manager.h"

double QueueManager::getCurrentTime() const {
    return EventManager::get().getCurrentTime();
}
