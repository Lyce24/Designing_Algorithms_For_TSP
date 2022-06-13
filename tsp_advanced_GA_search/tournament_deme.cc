#include "tournament_deme.hh"

using namespace std;

// selecting chromosome based on the result of the tournament
Chromosome *TournamentDeme::select_parent()
{
    // setting the parameter
    std::vector<Chromosome *> temp;
    std::vector<Chromosome *> result;

    // selecting a number of power of 2
    std::uniform_int_distribution<int> distribution(0, pop_.size());
    int p = distribution(generator_);

    // checking if p is a power of 2
    while (!(ceil(log2(p)) == floor(log2(p))) || p == 0 || p == 1)
    {
        p = distribution(generator_);
    }

    // making a distribution_1 to select a number between 0 and pop_.size() - 1 to select random chromosomes into the container as temp
    std::uniform_int_distribution<int> distribution_1(0, pop_.size() - 1);
    for (int i = 0; i < p; i++)
    {
        int index = distribution_1(generator_);
        temp.push_back(pop_[index]);
    }

    // while there are more than 2 chromosomes -> not into final battle
    while (temp.size() != 2)
    {
        int size = temp.size();

        // make them compete (size/2) times
        for (int i = 0; i < (size / 2); i++)
        {
            // compare the first and the second elements in temp, push back the one with higher fitness into result vector
            if (temp[0]->get_fitness() > temp[1]->get_fitness())
            {
                result.push_back(temp[0]);
            }
            else
            {
                result.push_back(temp[1]);
            }

            // pop out the first and the second elements in temp since we have already compared them
            temp.erase(temp.begin());
            temp.erase(temp.begin());
        }
        // In result, we have the winners from the competitions before with size of (size/2), make temp = result for the next round 
        temp = result;
        // clear the result
        result.clear();
    }

    // two chromosomes who survived from the tournaments before meet here to battle, return the one with higher fitness
    if (temp[0]->get_fitness() > temp[1]->get_fitness())
    {
        return temp[0];
    }
    return temp[1];
}

