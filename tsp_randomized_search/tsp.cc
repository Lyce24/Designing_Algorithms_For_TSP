#include "cities.hh"
#include <fstream>

int main(int argc, char **argv)
{
    // create a cities object and pass a file into the object to let it read numbers from it
    auto fin = std::ifstream(argv[1]);
    Cities cities;
    fin >> cities;

    // create an output file called shortest.tsv to record the ordered cities
    const char *fos = "shortest.tsv";
    std::ofstream outfile(fos);

    double shortest;
    // first case where random_p = {0,1,2, ... , len} - regular permutation
    shortest = cities.total_path_distance(cities.random_p);
    // print out the first case in the console
    cout << 1 << "\t";
    cout << shortest << endl;

    // iterate 1000000 times to find the shortest path
    for (int i = 0; i < 1000000; i++)
    {
        // getting a random permutation from the random_permutation methods on the number of cities in the file
        std::vector<unsigned> random_per = cities.random_permutation(cities.random_p.size());

        // make a temp variable to store the distance traveled based on the permutation above
        double temp = cities.total_path_distance(random_per);

        // if the temp variable is shorter than the distance before, change the shortest variable to temp
        if (temp < shortest)
        {
            // create a new cities object with the permutation generated above
            cities = cities.reorder(random_per);

            // make temp to be the shortest path for now
            shortest = temp;

            // print out the information in the console
            cout << i + 2 << "\t";
            cout << shortest << endl;
        }
        // if bigger than shortest, then move on to the next iteration
        else
        {
            continue;
        }
    }

    // output the cities based on the permutation to a new file
    outfile << cities;

    // close both files
    fin.close();
    outfile.close();

    return 0;
}
