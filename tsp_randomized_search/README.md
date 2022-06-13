<h2>
<p align="center"> 
TSP project - Part 1 (random search)
</p> 
</h2>


<p align="center">
    Eriksen Liu
</p>

### cities.hh
A class object which allows user to pass the coordinates of cities and arrange them into a vector in order to do future manipulations. In the class, we define methods to calculate the total distance traveled based on the permutation, to generate a random permutation of all the numbers from 0 to len-1 (with no skipped or repeated indices), and to produce a new cities with a given permutation.  
All the codes are explained in <code>cities.hh</code> file.

### cities.cc
The implementation of the cities class. By reading the coordinates of the cities into a vector, we can easily get the total distance based on the permutation as explained in the <code>.cc</code> file. And since we are doing the random search for the shortest path, we used <code>uniform_int_distribution</code> and <code>default_random_engine generator((unsigned int)time(0))</code> to generate a completely random permutation of the length given.  
And in order to read and write from and to a file, we overload the operators >> and << to make sure we can get numbers from a file and write the re-ordered cities into a new file.  
All the codes are explained in <code>cities.cc</code> file.

### tsp.cc
Our goal is to find the shortest path by random searching. We iterated 100,000 times to try different permutations of the cities to check if the path is shorter. In order to do that, we have a double variable called <code>shortest</code> that keeps track of the shortest distance that we've gotten so far. We then compare the record holder to the new iteration's total distance. If the new iteration yields a shorter total distance, we update <code>shortest</code> with the new distance. After all the iterations, we should get a decently optimized path if not the best one.  
When we get the optimized ordering of cities, we put the cities with the optmized permutation into a new file called <code>shortest.tsv</code>. And the process of finding the shortest path will appear in the console.

### How to implement
In the console, we can type the following command as,

    g++ -std=c++2a -O3 cities.cc tsp.cc -o tsp
    ./tsp filename.tsv

And then a file named <code>shortest.tsv</code> will appear in your directory which contains ordered coordinates with shortest total distance.  
For example, 

    g++ -std=c++2a -O3 cities.cc tsp.cc -o tsp
    ./tsp five.tsv
    1       48.8699
    8       43.1834

### Result
With plotting tools like <code>gnuplot</code>, we can visualize the process and the result. Since the result is random generated as we use <code>uniform_int_distribution</code> with random seed, the following results are randomly generated. Every run will produce different results.      
For <code>five.tsv</code>, the given file contains a path as shown below,

![five!](Solving_TSP_Problem/tsp_randomized_search/five.gif)

And after typing the following codes into the console as 

    /tsp five.tsv > speed_five.tsv
    gnuplot
    set term gif
    set out "speed_five.gif"
    plot "speed_five.tsv" w lp

We will get the following diagram to represent the process of finding the shortest path,

![five_speed!](/tsp/speed_five.gif)

And then, we can plot the shortest path using the <code>shortest.tsv</code> produced by <code>./tsp five.tsv</code> in <code>gnuplot</code> as, 

    set out "shortest_five.gif"
    plot "shortest.tsv" w lp

And it produces a diagram as shown below, 

![shortest_five!](/tsp/shortest_five.gif)

Similarly, we can find the shortest path for <code>challenge.tsv</code> as well.  
The original file looks like, 

![challenge!](tsp_randomized_search/challenge.gif)

And the process of finding the shortest path can be shown as following diagram,

![speed_challenge!](/tsp/speed_challenge.gif)

Then the optimal path with shortest distance can be shown as,

![shortest_challenge!](/tsp/shortest_challenge.gif)

### Memory check
I typed the following codes into the terminal to test if there is any memory leakage,

    g++ -std=c++2a -O3 cities.cc tsp.cc -o tsp
    valgrind --tool=memcheck --leak-check=yes --show-reachable=yes --num-callers=20 --track-fds=yes ./tsp five.tsv

And I got the following result,

 
    ==13472== Memcheck, a memory error detector
    ==13472== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
    ==13472== Using Valgrind-3.15.0 and LibVEX; rerun with -h for copyright info
    ==13472== Command: ./tsp five.tsv
    ==13472== 
    1       48.8699
    5       43.1834
    25       43.1834
    ==13472== 
    ==13472== FILE DESCRIPTORS: 3 open at exit.
    ==13472== Open file descriptor 2: /dev/pts/5
    ==13472==    <inherited from parent>
    ==13472== 
    ==13472== Open file descriptor 1: /dev/pts/5
    ==13472==    <inherited from parent>
    ==13472== 
    ==13472== Open file descriptor 0: /dev/pts/5
    ==13472==    <inherited from parent>
    ==13472== 
    ==13472== 
    ==13472== HEAP SUMMARY:
    ==13472==     in use at exit: 0 bytes in 0 blocks
    ==13472==   total heap usage: 4,000,018 allocs, 4,000,018 frees, 60,091,316 bytes allocated
    ==13472== 
    ==13472== All heap blocks were freed -- no leaks are possible
    ==13472== 
    ==13472== For lists of detected and suppressed errors, rerun with: -s
    ==13472== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
