#include "cities.hh"
#include "chromosome.hh"
#include <iostream>
#include <fstream>


using namespace std;

int main(int argc, char **argv)
{
    auto fin = std::ifstream(argv[1]);
    Cities* cities_ptr = new Cities;    
	fin >> *(cities_ptr);      

    Chromosome c(cities_ptr);

    cout << c.calculate_total_distance()<< endl;

    return 0;
}