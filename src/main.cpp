#include <iostream>
#include <iomanip>
#include "Timer.h"
#include "PercolationStats.h"

// Note: large-scale experiments show that the
// percolation threshold for large systems is 0.592746

int main(int argc, char* argv)
{
	unsigned int n{ 1000 }, trials{ 50 };

	if (argc == 3) {
		n = argv[1];
		trials = argv[2];
	}

	{
        // Only needed to output the total time to
        // run the current scope, can be removed
		Timer timer;

		PercolationStats percStats(n, trials);

		std::cout << std::setw(30) << "Mean:" << '\t' << std::setprecision(10) << percStats.getMean() << '\n';
		std::cout << std::setw(30) << "Standard Deviation:" << '\t' << percStats.getStdDev() << '\n';
		std::cout << std::setw(30) << "95% Confidence Interval:" << '\t' <<
			'[' << percStats.getConfidenceLow() << ", " << percStats.getConfidenceHigh() << ']' << std::endl;
	}
}