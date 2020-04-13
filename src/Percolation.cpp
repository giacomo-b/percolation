#include "Percolation.h"

#include <iostream>
#include "WeightedQuickUnion.h"

typedef unsigned int uint;

Percolation::Percolation(uint n)
	: n(n), n_sites(n * n), wqu(n_sites + 2)
{	
	open_sites.assign(n_sites + 2, false);
	open_sites[0] = true;
	open_sites[n_sites + 1] = true;
}

void Percolation::open(uint row, uint col)
{
	validate(row, col);

	if (!isOpen(row, col)) {
		connectToAdjacentCells(row, col);
		open_sites[rowColToSite(row, col)] = true;
		n_open++;
	}
}

bool Percolation::isOpen(int row, int col) const
{
	validate(row, col);

	return open_sites[rowColToSite(row, col)];
}

bool Percolation::isFull(int row, int col) const
{
	return wqu.connected(0, rowColToSite(row, col));
}

uint Percolation::numberOfOpenSites()
{
	return n_open;
}

bool Percolation::percolates()
{
	return wqu.connected(0, n_sites + 1);
}

void Percolation::validate(uint row, uint col) const
{
	if (row < 1 || row > n || col < 1 || col > n) {
		std::cerr << "\nInvalid element index. Values for rows and cols must be between " <<
			"1 and " << n << '\n' << std::endl;
		exit(EXIT_FAILURE);
	}
}

uint Percolation::rowColToSite(uint row, uint col) const
{
	return 1 + (row - 1) * n + (col - 1);
}

void Percolation::connectToAdjacentCells(uint row, uint col)
{
	uint site = rowColToSite(row, col);

	// Most likely case for big matrices, element in the middle
	if (row != 1 && row != n && col != 1 && col != n) {
		// Top
		if (isOpen(row - 1, col))
			wqu.join(site, rowColToSite(row - 1, col));

		// Bottom
		if (isOpen(row + 1, col))
			wqu.join(site, rowColToSite(row + 1, col));

		// Left
		if (isOpen(row, col - 1))
			wqu.join(site, rowColToSite(row, col - 1));

		// Right
		if (isOpen(row, col + 1))
			wqu.join(site, rowColToSite(row, col + 1));
	}
	// Element in the top row
	else if (row == 1) {
		// Top
		wqu.join(site, 0);

		// Bottom
		if (isOpen((uint)2, col))
			wqu.join(site, rowColToSite((uint)2, col));

		if (col != 1) {
			// Left
			if (isOpen(row, col - 1))
				wqu.join(site, rowColToSite(row, col - 1));
		}

		if (col != n) {
			// Right
			if (isOpen(row, col + 1))
				wqu.join(site, rowColToSite(row, col + 1));
		}
	}
	// Element in the bottom row
	else if (row == n) {
		// Top
		if (isOpen(row - 1, col))
			wqu.join(site, rowColToSite(row - 1, col));

		// Bottom
		wqu.join(site, n_sites + 1);

		if (col != 1) {
			// Left
			if (isOpen(row, col - 1))
				wqu.join(site, rowColToSite(row, col - 1));
		}

		if (col != n) {
			// Right
			if (isOpen(row, col + 1))
				wqu.join(site, rowColToSite(row, col + 1));
		}
	}
	// Either in first or last column
	else {
		// Top
		if (isOpen(row - 1, col))
			wqu.join(site, rowColToSite(row - 1, col));

		// Bottom
		if (isOpen(row + 1, col))
			wqu.join(site, rowColToSite(row + 1, col));

		if (col == n) {
			// Left
			if (isOpen(row, col - 1))
				wqu.join(site, rowColToSite(row, col - 1));
		}

		if (col == 1) {
			// Right
			if (isOpen(row, col + 1))
				wqu.join(site, rowColToSite(row, col + 1));
		}
	}
}