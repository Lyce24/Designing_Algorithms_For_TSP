/*
 * Declarations for Deme class to evolve a genetic algorithm for the
 * travelling-salesperson problem.  A deme is a population of individuals.
 */

#include "chromosome.hh"
#include "deme.hh"
#include <cassert>

using namespace std;

// Generate a Deme of the specified size with all-random chromosomes.
// Also receives a mutation rate in the range [0-1].
Deme::Deme(const Cities* cities_ptr, unsigned pop_size, double mut_rate)
 : generator_(rand()), mut_rate_(mut_rate)
{
  // append pop_size Chromosome into pop_
   for (int i = 0; i < int(pop_size); i++)
   {
     Chromosome* c = new Chromosome(cities_ptr);
     pop_.push_back(c);
   }
   return;
}

// Clean up as necessary
Deme::~Deme()
{
  // release memory (Delete all Chromosome)
  for (auto &i : pop_)
  {
    delete i;
  }
}

// Evolve a single generation of new chromosomes, as follows:
// We select pop_size/2 pairs of chromosomes (using the select() method below).
// Each chromosome in the pair can be randomly selected for mutation, with
// probability mut_rate, in which case it calls the chromosome mutate() method.
// Then, the pair is recombined once (using the recombine() method) to generate
// a new pair of chromosomes, which are stored in the Deme.
// After we've generated pop_size new chromosomes, we delete all the old ones.
void Deme::compute_next_generation()
{
  // container to store the Chromosome generated
  std::vector<Chromosome*> temp;
  // generate a random number between 0-1 (For mutation)
  std::uniform_real_distribution<double> distribution(0.0, 1.0);
  // iterate pop_size()/2 times (generate 2 Chromosome each time -> total number of pop_ doesn't change)
  for (int i = 0; i < pop_.size()/2; i++)
  {
    // generate random number
    double mutate_rate = distribution(generator_);

    // select 2 parents by select_parent()
    Chromosome* parent1 = select_parent();
    Chromosome* parent2 = select_parent();

    // if mut_rate_ of deme is greater than mutate rate -> Both of the Chromosomes mutate
    if (mutate_rate < mut_rate_)
    {
      parent1->mutate();
      parent2->mutate();
    }

    assert(!(parent1 == nullptr));
    assert(!(parent2 == nullptr));

    // recombine the parents to produce 2 children
    auto c1 = parent1->recombine(parent2);

    // push back the children into the temp
    temp.push_back(c1.first);
    temp.push_back(c1.second);
  }
  // update the pop_ with temp
  pop_ = temp;
}

// Return a copy of the chromosome with the highest fitness.
const Chromosome* Deme::get_best() const
{
  // set the variables to compare
  Chromosome* result = pop_.front();
  // make best_fitness to initialize at the fitness of the first chromosome in pop_
  double best_fitness = (pop_.front())->get_fitness();
  // iterate the pop_ to see if there's chromosome has higher fitness than the one we have now
  for (auto i : pop_)
  {
    // if greater -> update the best_fitness and the chromosome as well
    if (i->get_fitness() > best_fitness)
    {
      best_fitness = i->get_fitness();
      result = i;
    }
  }

  // return the chromosome with highest fitness
  return result;
}

// Randomly select a chromosome in the population based on fitness and
// return a pointer to that chromosome.
Chromosome* Deme::select_parent()
{
  // setting the parameter
  double total_fitness = 0.0;
  double sum = 0.0;

  // iterate the pop_ to sum up all the fitness to set the upper boundary for uniform_real_distribution below
  for (auto &i : pop_)
  {
    total_fitness += i->get_fitness();
  }
  
  // generate a random number between 0 - total_fitness
  std::uniform_real_distribution<double> distribution(0.0, total_fitness);
  double random = distribution(generator_);

  // summing up the fitnesses of the chromosome, return the one which make the sum be greater than the random number we generated
  for (auto &i : pop_)
  {
    sum += i->get_fitness();

    // the chromosome with higher fitness will have higher possibility to be return 
    if (sum >= random)
    {
      assert(!(i == nullptr));
      return i;
    }
  }

  // if something goes wrong, return nullptr
  return nullptr;
}
