#ifndef SIMULATIONMODEL_H
#define SIMULATIONMODEL_H

#include "Generator.h"

#include <vector>

class SimulationModel
{
public:
    SimulationModel( double lambda ): lambda_( lambda ), exp_dist( lambda ) {};

    int SimulateSingleRun( double time );
    std::vector< int > SimulateManyRuns( double time, int n_runs );

    double CalculateMean( const std::vector< int >& data );
    double CalculateVariance( const std::vector< int >& data, double mean );

private:

    double lambda_;
    std::exponential_distribution< double > exp_dist;
};

#endif // SIMULATIONMODEL_H
