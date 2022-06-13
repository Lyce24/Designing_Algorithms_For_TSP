/*
 * Implementation for Chromosome class
 */

#include <algorithm>
#include <cassert>
#include <random>
#include "chromosome.hh"

using namespace std;

//////////////////////////////////////////////////////////////////////////////
// Generate a completely random permutation from a list of cities
Chromosome::Chromosome(const Cities *cities_ptr)
    : cities_ptr_(cities_ptr),
      order_(random_permutation(cities_ptr->size())),
      generator_(rand())
{
  assert(is_valid());
}

//////////////////////////////////////////////////////////////////////////////
// Clean up as necessary
Chromosome::~Chromosome()
{
  assert(is_valid());
}

//////////////////////////////////////////////////////////////////////////////
// Perform a single mutation on this chromosome
void Chromosome::mutate()
{
  // use uniform_int_distribution to generate two numbers between 0 to len - 1
  std::uniform_int_distribution<int> distribution(0, order_.size() - 1);
  int first = distribution(generator_);
  int second = distribution(generator_);

  // swap the element in order_ with the index of the smaller number between first and second and the element with the index of the larger number.
  std::iter_swap(order_.begin() + min(first,second), order_.begin() + max(first,second));
  assert(is_valid());

  return;
}

//////////////////////////////////////////////////////////////////////////////
// Return a pair of offsprings by recombining with another chromosome
// Note: this method allocates memory for the new offsprings
std::pair<Chromosome *, Chromosome *>
Chromosome::recombine(const Chromosome *other)
{
  assert(is_valid());
  assert(other->is_valid());

  // generate numbers between 0 - order_.size()
  std::uniform_int_distribution<int> distribution(0, order_.size());
  int first = distribution(generator_);
  int second = distribution(generator_);
  auto range = std::minmax(first, second);

  // create_crossover_child with the numbers generated before
  auto c1 = create_crossover_child(this, other, range.first ,range.second);
  auto c2 = create_crossover_child(other, this, range.first, range.second);

  // return a std::pair containing two children
  return std::make_pair(c1,c2);
}

//////////////////////////////////////////////////////////////////////////////
// For an ordered set of parents, return a child using the ordered crossover.
// The child will have the same values as p1 in the range [b,e),
// and all the other values in the same order as in p2.
Chromosome *
Chromosome::create_crossover_child(const Chromosome *p1, const Chromosome *p2,
                                   unsigned b, unsigned e) const
{
  Chromosome *child = p1->clone();

  unsigned i = 0, j = 0;

  for (; i < p1->order_.size() && j < p2->order_.size(); ++i)
  {
    if (i >= b and i < e)
    {

      child->order_[i] = p1->order_[i];
    }

    else
    { // Increment j as long as its value is in the [b,e) range of p1
      while (p1->is_in_range(p2->order_[j], b, e))
      {
        ++j;
        assert(j < p2->order_.size());
      }        
      child->order_[i] = p2->order_[j];
      j++;
    }
  }
  assert(child->is_valid());
  return child;
}

// Return a positive fitness value, with higher numbers representing
// fitter solutions (shorter total-city traversal path).
double
Chromosome::get_fitness() const
{
  double result = calculate_total_distance();
  // make sure than 0 is not a divisor here
  double fitness = 1 / (result + 1);
  return fitness;
}

// A chromosome is valid if it has no repeated values in its permutation,
// as well as no indices above the range (length) of the chromosome.
bool Chromosome::is_valid() const
{
  for (auto i : order_)
  {
    // checking: 1. the occurrence of every element in the order_ is exactly one; 2. the order_ size is equal to the cities passed; 3. make sure all elements in order_ is smaller or equal to the order_.size()
    if (std::count(order_.cbegin(), order_.cend(), i) != 1 || order_.size() != cities_ptr_->size() || i > (order_.size() - 1))
    {
      // if anything above is not satisfied, return false as invalid 
      return false;
    }
  }
  // otherwise, return true
  return true;
}

// Find whether a certain value appears in a given range of the chromosome.
// Returns true if value is within the specified the range specified
// [begin, end) and false otherwise.
bool Chromosome::is_in_range(unsigned value, unsigned begin, unsigned end) const
{
  // iterate the elements with indexes between begin and end-1
  for (int i = begin; i < end; i++)
  {
    // if there is some elements equals to the value
    if (order_[i] == value)
    {
      // return true
      return true;
    }
  }
  // otherwise, return false
  return false;
}
