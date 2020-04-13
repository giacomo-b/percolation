#include "PercolationStats.h"

#include <random>
#include <math.h>

typedef unsigned int uint;
typedef std::pair<double, double> pair;

PercolationStats::PercolationStats(uint n, uint trials)
	: n(n), trials(trials)
{	
	thresholds.reserve(trials);
	computeStatistics();
}

double PercolationStats::getMean()
{
	return mean;
}

double PercolationStats::getStdDev()
{
	return std_dev;
}

double PercolationStats::getConfidenceLow()
{
	return conf_interval.first;
}

double PercolationStats::getConfidenceHigh()
{
	return conf_interval.second;
}

void PercolationStats::computeStatistics()
{
	double threshold;
	for (auto i = 0; i < trials; ++i) {
		Percolation percolation(n);
		threshold = computeThreshold(percolation);
		thresholds.push_back(threshold);
	}

	mean = computeMean();
	std_dev = computeStdDeviation(mean);
	conf_interval = computeConfidenceInterval(mean, std_dev);
}

double PercolationStats::computeThreshold(Percolation& percolation)
{
    // Get a random number from hardware, seed random generator
    // and initialize distribution
	std::random_device rd;
	std::mt19937 eng(rd());
	std::uniform_int_distribution<> distr(1, n);
	
	uint open_sites;
	uint p, q;

	while (!percolation.percolates()) {
		p = distr(eng);
		q = distr(eng);
		percolation.open(p, q);
		open_sites = percolation.numberOfOpenSites();
	}

	return (double)open_sites / (n * n);
}

double PercolationStats::computeMean()
{
	double sum = 0;
	for (auto& t : thresholds)
		sum += t;
	
	return sum / trials;
}

double PercolationStats::computeStdDeviation(double ref_mean)
{
	double sum_of_squares = 0;
	for (auto& t : thresholds)
		sum_of_squares += pow((t - ref_mean), 2);

	double variance = sum_of_squares / (trials - 1);

	return sqrt(variance);
}

pair PercolationStats::computeConfidenceInterval(double ref_mean, double stddev)
{
	double low = ref_mean - 1.96 * stddev / sqrt(trials);
	double high = ref_mean + 1.96 * stddev / sqrt(trials);

	return pair(low, high);
}