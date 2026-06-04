#pragma once

#include "random_generator.h"
#include <memory>
#include <functional>

class PoissonStream : public std::enable_shared_from_this<PoissonStream>
{
public:
    explicit PoissonStream(double lambda);

    void start();
    void generateRequest();

private:
    void scheduleNext(); // запланировать следующее событие

    double lambda_;
};
