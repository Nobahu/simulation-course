#ifndef PROCESSING_DEVICE_H
#define PROCESSING_DEVICE_H

#include "RandomGenerator.h"

class ProcessingDevice
{
public:

    explicit ProcessingDevice( double mu ): mu_( mu ), distr_( mu ) {}

    bool AcceptRequirement()
    {
        if ( isBusy )
        {
            return false;
        }
        isBusy = true;
        currentServiceTime_ = distr_( RandomGenerator::get() );

        return true;
    }

    void FinishService()
    {
        isBusy = false;
        currentServiceTime_ = 0;
    }

    void TimeSubstraction( double time )
    {
        if ( currentServiceTime_ <= time )
        {
            currentServiceTime_ = 0;
        }
        else
        {
            currentServiceTime_ -= time;
        }
    }

    double GetCurrentServiceTime() const
    {
        return currentServiceTime_;
    }

    bool IsBusy() const
    {
        return isBusy;
    }

private:

    bool isBusy = false;
    double mu_;
    double currentServiceTime_ = 0;
    std::exponential_distribution< double > distr_;
};

#endif // PROCESSING_DEVICE_H
