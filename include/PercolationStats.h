#pragma once

#include <vector>
#include <utility>
#include "Percolation.h"

class PercolationStats
{
	typedef unsigned int uint;
    typedef std::pair<double, double> pair;

public:
    // Perform independent trials on an n-by-n grid
    PercolationStats(uint n, uint trials);

    // Sample mean of percolation threshold
    double getMean();

    // Sample standard deviation of percolation threshold
    double getStdDev();

    // Low and high endpoints of 95% confidence interval
    double getConfidenceLow();
    double getConfidenceHigh();

private:
    // Number of elements per side
    uint n;

    // Number of experiments to be carried out
    uint trials;

    // Statistics
    double mean, std_dev;
    pair conf_interval;

    // Collect the percolation threshold for each trial
    std::vector<double> thresholds;

    // Performs 'trials' experiments and computes the statistics
    void computeStatistics();

    // Randomly opens a Percolation object's sites until it percolates
    double computeThreshold(Percolation& percolation);

    // Statistics utilities
    double computeMean();
    double computeStdDeviation(double ref_mean);
    pair computeConfidenceInterval(double ref_mean, double stddev);
};

