#pragma once

#include <vector>
#include "WeightedQuickUnion.h"

class Percolation
{
	typedef unsigned int uint;

public:

	// Creates n-by-n grid, with all sites initially blocked
	Percolation(uint n);

    // Opens the site (row, col) if it is not open already
    void open(uint row, uint col);

    // Is the site (row, col) open?
    bool isOpen(int row, int col) const;

    // Is the site (row, col) full?
    bool isFull(int row, int col) const;

    // Returns the number of open sites
    uint numberOfOpenSites();

    // Does the system percolate?
    bool percolates();

private:
    // Number of element per side
    uint n;

    // Total number of sites
    uint n_sites;

    // How many sites are currently open
    uint n_open{ 0 };

    // Core algorithm
    WeightedQuickUnion wqu;

    // Keeps track of which sites are open
    std::vector<bool> open_sites;

    // Is (row, col) a valid input?
    void validate(uint row, uint col) const;

    // Go from (row, col) to 1D index for WQU and open_sites
    uint rowColToSite(uint row, uint col) const;

    // Check all the surrounding cells. If they are open, connect
    void connectToAdjacentCells(uint row, uint col);
};