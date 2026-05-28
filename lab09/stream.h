#ifndef STREAM_H
#define STREAM_H

#include "RandomGenerator.h"

class PoissonStream
{
public:

    explicit PoissonStream( double lambda ) : lambda_( lambda ), distr_( lambda ) {}

    double GenerateTau()
    {
        return distr_( RandomGenerator::get() );
    }

private:

    double lambda_;
    std::exponential_distribution< double > distr_;

};

#endif // STREAM_H
