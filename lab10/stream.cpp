#include "stream.h"
#include "event_manager.h"
#include "requirement.h"

PoissonStream::PoissonStream(double lambda)
    : lambda_(lambda) {}

void PoissonStream::start() {
    // Планируем первое событие
    scheduleNext();
}

void PoissonStream::scheduleNext() {
    double delta = LCG::get().generate( lambda_ );
    double nextTime = EventManager::get().getCurrentTime() + delta;

    EventManager::get().scheduleEvent(
        nextTime,
        [self = shared_from_this()]() {
            self->generateRequest();
            self->scheduleNext();  // планируем следующее событие
        }
        );
}

void PoissonStream::generateRequest() {
    double arrivalTime = EventManager::get().getCurrentTime();

    // Создаём новую заявку
    auto req = std::make_shared<Requirement>(arrivalTime);

    // Заявка сама пытается войти в систему
    req->tryEnterSystem();
}
