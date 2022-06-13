#include "cities.hh"

using namespace std;

// generate random number
default_random_engine generator((unsigned int)time(0));

// if given a permutation to the Cities object, then initialize the random_p to be the permutation given
Cities::Cities(Cities::permutation_t p)
    :random_p(p)
{
}


double Cities::total_path_distance(const permutation_t &ordering) const
{
    // initialize and declare variables for future usages
    double distance = 0.0; // total distance travelled
    Cities::coord_t beginning; // record the coordinates of the first city we started
    Cities::coord_t temp;      // a temp variable to store the city we visited last time
    int index = 0;             // just a simple index


    for (const auto &i : ordering)
    {
        // if it's not the first coordiniates, then calculate the total distance
        if (index != 0)
        {
            // calculate the distance between the city we are at right now and the city from last time
            distance += sqrt(pow(cities[i].first - temp.first, 2) + pow(cities[i].second - temp.second, 2));
            // update the temp variable when we leave the city
            temp.first = cities[i].first;
            temp.second = cities[i].second;
        }

        // if it's the first element in teh ordering, recode the coordinates and start the travel
        else
        {
            temp.first = cities[i].first;
            temp.second = cities[i].second;
            beginning.first = cities[i].first;
            beginning.second = cities[i].second;
            // index + 1 to never use it again
            index++;
        }
    }
    // need to calculate the distance from the last city to the first city
    distance += sqrt(pow(beginning.first - temp.first, 2) + pow(beginning.second - temp.second, 2));

    // return the distance 
    return distance;
}

std::istream &operator>>(std::istream &is, Cities &C)
{
    int number; // number we got from the file
    int temp_num; // a temp container for number
    int index = 0; // a simple index

    // we will always have even number in is (as we are getting coordinates of cities, so it must come with even number of integers)
    while (is >> number)
    {
        //add the number we got to the first place of the temp (defined in header file - a coord_t type variable)
        C.temp.first = number;

        // get another number from the file
        is >> temp_num;

        // make the second coordinate of temp to be temp_num
        C.temp.second = temp_num;

        // add the coordinate of this city into cities (defined in header file - a vector<coord_t> type variable to store cities from the file)
        C.cities.push_back(C.temp);
    }

    // initialize the random_p (permutation of the cities) to {0,1,2, ... ,len}
    for (auto i = C.cities.begin(); i != C.cities.end(); ++i)
    {
        // index = 0 from last while loop at last, so we push back index for every element in the cities
        // assuming cities = {{0,0}, {0,1}, {0,2}}, then random_p = {0,1,2}
        C.random_p.push_back(index);
        // increase the index every time
        index++;
    }

    // return is
    return is;
}

std::ostream &operator<<(std::ostream &os, Cities &C)
{    
    // for every number in the random_p (a permutation)
    for (auto i = C.random_p.begin(); i != C.random_p.end(); ++i)
    {
        // print the coordinates of the i-th cities into os
        os << C.cities[*i].first << "\t" << C.cities[*i].second << "\n";
    }

    // return os
    return os;
}

Cities::permutation_t Cities::random_permutation(unsigned len)
{
    // make a temp to store the permutation
    permutation_t temp;

    // use uniform_int_distribution to generate a number between 0 to len - 1
    uniform_int_distribution<int> distribution(0, len - 1);
 
    // while the size of temp is not equal to len (still have room for numbers)
    while (temp.size() != len)
    {
        // generate a random number between 0 to len - 1
        int i = distribution(generator);

        // check whether i is in the temp or not
        // if in the temp, continue to the next round
        if (std::count(temp.begin(), temp.end(), i))
        {
            continue;
        }
        // if not, then push back i into temp
        else
        {
            temp.push_back(i);
        }
    }

    // return the random permutation 
    return temp;
}


Cities Cities::reorder(const Cities::permutation_t &ordering) const
{
    // create a new object with a specific permutation given
    Cities c(ordering);

    // return the object
    return c;
}
