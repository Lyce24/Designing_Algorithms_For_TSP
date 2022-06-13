#include "climb_chromosome.hh"

// mutate() - local hill climbing: searches for the best solution in a small local “neighborhood” of the current chromosome
void ClimbChromosome::mutate()
{
    // get fitness now to set a highest_fitness
    double highest_fitness = get_fitness();
    Cities::permutation_t temp = order_; //setting variable to store original ordering
    // generate a random number between 0 and order_.size() - 1 to set neighborhood
    std::uniform_int_distribution<int> distribution(0, order_.size() - 1);
    int p = distribution(generator_);

    // firstly checking (p-1) cases
    // if p == 0
    if (p == 0)
    {
        // swap the beginning and the end in the vector
        std::iter_swap(order_.begin(), order_.begin() + (order_.size() - 1));
        // compare the fitness after swapping and the highest fitness before (original ordering)
        if (get_fitness() > highest_fitness)
        {
            // if bigger, setting highest fitness to equal to the fitness rn
            highest_fitness = get_fitness();
        }
        // if not...
        else
        {
            // swap the element back
            std::iter_swap(order_.begin(), order_.begin() + (order_.size() - 1));
        }
    }
    // simliar process for p!= 0
    else
    {
        // swap element in p slot and (p-1) slot
        std::iter_swap(order_.begin() + p, order_.begin() + (p-1));
        if (get_fitness() > highest_fitness)
        {
            highest_fitness = get_fitness();
        }
        else
        {
            std::iter_swap(order_.begin() + p, order_.begin() + (p-1));
        }
    }

    // Secondly checking (p+1) cases
    // if we are choosing the last element in the ordering
    if (p == int(order_.size() - 1))
    {
        // swap the first and the last elements in the temp (original ordering)
        std::iter_swap(temp.begin(), temp.begin() + p);
        // compare the fitness for the temp and the current highest fitness
        if ((1/ (1 + (cities_ptr_->total_path_distance(temp)))) > highest_fitness )
        {
            // setting order as temp (highest fitness - (p+1) case)
            order_ = temp;
        }
    }
    // simliar case for p != order_.size() - 1
    else
    {
        std::iter_swap(temp.begin() + p, temp.begin() + (p+1));
        if ((1/ (1 + (cities_ptr_->total_path_distance(temp)))) > highest_fitness )
        {
            order_ = temp;
        }
    }

    // Remark:
    // if original order has the highest fitness, in (p-1) case, the order will swap back to original order and (p+1) case won't change it
    // if (p-1) case has the highest fitness, then (p+1) case won't change it since (p+1) case alter the temp vector. not order_
    // if (p+1) case has the highest fitness, then at the final stage order_ will changed to the altered ordering of temp
    return;
}


Chromosome* ClimbChromosome::clone() const
{
    // create a new ClimbChromosome with the same order
    return new ClimbChromosome(*this);
}