<h2>
<p align="center"> 
TSP project - Part 2 (Genetic Algorithm search)
</p> 
</h2>


<p align="center">
    Eriksen Liu, Ryan Tang, Ella Ngo 
</p>



### chromosome.cc
To construct a class that contains a random order of cities. In this class, the ordering can "mutate", i.e swap two cities randomly. And like chromosomes do, they can recombine to produce two different orderings of the cities. We use these methods to create and re-produce mutated chromosomes.  
For each chromosome, we can get its fitness in order to find out the best ordering of the cities.  
All the codes are explained in <code>chromosome.cc</code> file.

### deme.cc
This file constructs a class containing a certain size of chromosomes to allow them to mutate and recombine. It will produce randomized chromosomes in a certain way based on their fitnesses.  
All codes are explained in <code>deme.cc</code> file.


### How to implement
In the console, we can type the following command as,

    g++ -std=c++2a -O3 cities.cc chromosome.cct deme.cc sp.cc -o tsp
    ./tsp filename.tsv popsize mutrate

And then a file named <code>shortest.tsv</code> will appear in your directory which contains ordered coordinates with shortest total distance.  
For example, 

    g++ -std=c++2a -O3 cities.cc chromosome.cc deme.cc tsp.cc -o tsp
    ./tsp five.tsv 50 0.5
    50       43.1834

### Result
We can compare the efficiency of using GA with randomized search. With the steps in the slide, we are able to get the graph below showing a major improvement in efficiency while using GA.

![five_speed!](/tsp_part2/comparison.gif)

