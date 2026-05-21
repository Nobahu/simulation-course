#include "simulationmodel.h"

int SimulationModel::SimulateSingleRun( double time )
{
    double t = 0.0;
    int count = 0;


    while ( true )
    {

        double tau = exp_dist( RandomGenerator::get() );
        t += tau;

        if ( t > time ) {
            break;
        }

        count++;
    }

    return count;
}

std::vector< int > SimulationModel::SimulateManyRuns( double time, int n_runs )
{

    std::vector< int > results;
    results.reserve( n_runs );

    for ( int i = 0; i < n_runs; i++ ) {
        results.push_back( SimulateSingleRun( time ) );
    }

    return results;
}

double SimulationModel::CalculateMean( const std::vector<int>& data )
{

    if ( data.empty() )
    {
        return 0.0;
    }

    double sum = 0.0;

    for ( int val : data )
    {
        sum += val;
    }

    return sum / data.size();
}

double SimulationModel::CalculateVariance( const std::vector<int>& data, double mean ) {

    if ( data.empty() )
    {
        return 0.0;
    }

    double sum_squared_diff = 0.0;

    for ( int val : data )
    {
        double diff = val - mean;
        sum_squared_diff += diff * diff;
    }

    return sum_squared_diff / (data.size() - 1);
}
