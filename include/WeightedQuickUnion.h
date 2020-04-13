#pragma once

#include <vector>

class WeightedQuickUnion
{
	typedef unsigned int uint;

public:

	WeightedQuickUnion(uint n)
	{
		parent.reserve(n);

		for (auto i = 0; i < n; ++i)
			parent.push_back(i);

		size.assign(n, 1);
	}

	bool connected(uint p, uint q) const
	{
		return root(p) == root(q);
	}

	void join(uint p, uint q)
	{
		uint i = root(p);
		uint j = root(q);

		if (i == j) return;

		if (size[i] < size[j]) {
			parent[i] = j;
			size[j] += size[i];
		}
		else {
			parent[j] = i;
			size[i] += size[j];
		}
	}

private:
	std::vector<uint> parent, size;

	uint root(uint i) const
	{
		while (i != parent[i])
			i = parent[i];

		return i;
	}
};