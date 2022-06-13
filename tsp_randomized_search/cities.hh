/*
 * API file for Travelling-Salesperson Cities class and utilities
 */

#pragma once
#include <iostream>

// container
#include <vector>

// need to generate random date
#include <random>

// need to use sqrt and pow method
#include <math.h>

// need to use algorithm in random_permutation (.count())
#include <algorithm>

using namespace std;

// Representation of an ordering of cities
class Cities
{
public:
	// A pair of integral coordinates for each city
	using coord_t = std::pair<int, int>;

	// An ordering of cities. Each value represents a unique index
	// into the current city ordering in some container.
	using permutation_t = std::vector<unsigned int>;
	// permutation of cities
	permutation_t random_p;

	// default constructor
	Cities() = default;

	// The constructor with a given ordering
	Cities(permutation_t p);

	~Cities() = default;

	// Given a permutation, return a new Cities object where the order of the
	// cities reflects the original order of this class after reordering with
	// the given ordering. So for example, the ordering { 1, 0 } simply swaps
	// the first two elements (coordinates) in the new Cities object.
	Cities reorder(const permutation_t &ordering) const;

	// For a given permutation of the cities in this object,
	// compute how long (distance) it would take to traverse all the cities in the
	// order of the permutation, and then returning to the first city.
	// The distance between any two cities is computed as the Euclidean
	// distance on a plane between their coordinates.
	double total_path_distance(const permutation_t &ordering) const;

	// generate a random permutation from 0 to len, with no missing value from 0 to len.
	permutation_t random_permutation(unsigned len);

	// get the numbers in a file to form a vector of cities
	friend std::istream &operator>>(std::istream &is, Cities &C);

	// output the coordinates of cities based on the ordering to a new file
	friend std::ostream &operator<<(std::ostream &os, Cities &C);

private:
	// container to store coordinates of the cities
	std::vector<coord_t> cities;

	// coordinates of each city
	std::pair<int, int> temp;
};
