// C++ code to demonstrate the working of
// make_heap() using syntax 2

#include<iostream>
#include<algorithm> // for heap
#include<vector>
#include "chromosome.hh"
#include "deme.hh"
using namespace std;

// comparator function to make min heap
bool test(std::vector<int> order_, std::vector<int> cities)
{
	for (auto i : order_)
  	{
    if (std::count(order_.cbegin(), order_.cend(), i) != 1 || i > order_.size() - 1 || order_.size() != cities.size()) //not chaning ordering
      {
          return false;
      }
  } // Add your implementation here
  return true;
}


// int main()
// {
// 	// initializing vector;
// 	vector<int> vi = { 3,2,1,0,4 };
// 	vector<int> cities = {1,2,3,4,7};
// 	cout << test(vi, cities) << endl;
// 	// using make_heap() to transform vector into
// 	// a min heap

// 	Chromosome c1();
	
	
// 	// checking if heap using
// 	// front() function
// 	return 0;
// }
#include "cities.hh"
#include <fstream>

int main(int argc, char **argv)
{
	auto fin = std::ifstream(argv[1]);
    Cities* cities_ptr = new Cities;    
	fin >> *(cities_ptr);      

	fin = std::ifstream(argv[2]);
    Cities* cities_ptr1 = new Cities;    
	fin >> *(cities_ptr1);     
    cout << "First one: " << endl;

    Chromosome* c1 = new Chromosome(cities_ptr);
    Chromosome* c2 = new Chromosome(cities_ptr1);

    cout << "Before: " << endl;
    cout << "c1: " << c1 << endl;
    for (auto i : c1->get_ordering())
    {
        cout << i;
    } 
    cout << endl;

    cout << "c2: " << c2 << endl;

    for (auto i : (*c2).get_ordering())
    {
        cout << i;
    } 
    cout << endl;

    c1->mutate();
    c2->mutate();
    
    cout << "after" << endl;
    cout << "c1: " << c1 << endl;
    for (auto i : c1->get_ordering())
    {
        cout << i;
    } 
    cout << endl;

    cout << "c2: " << c2 << endl;

    for (auto i : (*c2).get_ordering())
    {
        cout << i;
    } 
    cout << endl;

    for (int i = 0; i < 5; i++)
    {
        cout << "trail" << i << endl;
            cout << "Before: " << endl;
    cout << "c1" << endl;
    for (auto i : c1->get_ordering())
    {
        cout << i;
    } 
    cout << endl;

    cout << "c2" << endl;

    for (auto i : (*c2).get_ordering())
    {
        cout << i;
    } 
    cout << endl; 
        std::pair<Chromosome*,Chromosome*> test;
        test = c1->recombine(c2);

        cout << "After: " << endl;
        cout << "c1" << endl;
        for (auto i : (*(test.first)).get_ordering())
        {
            cout << i;
        } 
        cout << endl;

        cout << "c2" << endl;
    
        for (auto i :  (*(test.second)).get_ordering())
        {
            cout << i;
        } 
        cout << endl;


    }
    // Deme d(cities_ptr, 50, 0.2);

    // cout << (d.get_best())->get_fitness() << endl;
    // d.compute_next_generation();

    return 0;
}
