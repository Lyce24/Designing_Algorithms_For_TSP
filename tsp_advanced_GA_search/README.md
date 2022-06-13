<h2>
<p align="center"> 
TSP project - Part 3 (advanced GA operators)
</p> 
</h2>


<p align="center">
    Eriksen Liu, Ryan Tang, Ella Ngo 
</p>



### climb_chromosome.cc & climb_chromosome.hh
To make the chromosome to mutate with a new method. It will return an ordering with the highest fitness in the neighborhood, i.e by comparing switching back and forth of one particular city in the ordering to see if it has higher fitness than before.  
All codes are explained in the <code>chromosome.cc</code> file.


### tournament_deme.cc & tournament_deme.hh
To select the best parent using the tournament-like way. All code are explained in <code>tournament_deme.cc</code> file.


### How to implement & Result
In order to see the effect of "local hill climbing", we need to first use the regular deme class and compare the result with <code>baseline_ga.tsv</code>.  

In <code>tsp.cc</code> file, uncomment the line 156 and comment the line 157 and save it.

In the console, we can type the following command as,

    g++ -Wall -Wextra -pedantic -Werror -std=c++17 -O3  cities.cc chromosome.cc climb_chromosome.cc deme.cc tournament_deme.cc tsp.cc -o tsp
    ./tsp filename.tsv popsize mutrate > local.tsv

Or simply just use the Makefile as,

    make
    ./tsp filename.tsv popsize mutrate > local.tsv

And then a file named <code>shortest.tsv</code> will appear in your directory which contains ordered coordinates with shortest total distance. And another file named <code>local.tsv</code> will appear too showing the speed of finding the lowest total path distance.  

And then, we need to exam the effect of tournament_deme. In order to do that, simply uncomment line 157 in <code>tsp.cc</code> and comment the line 156 and save it.  

Then we can use Makefile to make a tournament tsp program, 

    make
    ./tsp filename.tsv popsize mutrate > tournament.tsv
    
If Makefile doesn't work, we can use regular command lines like,

    g++ -Wall -Wextra -pedantic -Werror -std=c++17 -O3  cities.cc chromosome.cc climb_chromosome.cc deme.cc tournament_deme.cc tsp.cc -o tsp
    ./tsp filename popsize mutrate > tournament.tsv

Similarly, two files will appear in your directory containing the optimal ordering of the cities and the speed for the program to do that.
### Result
With the implementation above, I used <code>popsize = 50</code> and <code>mutrate = 0.96</code> to optimize the <code>challenge.tsv</code>.  
Then, with the instruction in moodle, I got the following diagram containing <code>ga_baseline.tsv</code>, <code>local.tsv</code>, and <code>tournament.tsv</code>.  

![comp!](/comparison.gif)

### Memory check
I used Valgrind to check if there is any memory leakage. Therefore, I typed the following command in the console,  

    valgrind --tool=memcheck --leak-check=yes --show-reachable=yes --num-callers=20 --track-fds=yes ./tsp five.tsv 50 0.5

which gives me a result like this,

    ==5990== Memcheck, a memory error detector
    ==5990== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
    ==5990== Using Valgrind-3.15.0 and LibVEX; rerun with -h for copyright info
    ==5990== Command: ./tsp five.tsv 50 0.5
    ==5990== 
    50      51.1802
    100     43.1834
    ==5990== 
    ==5990== FILE DESCRIPTORS: 3 open at exit.
    ==5990== Open file descriptor 2: /dev/pts/5
    ==5990==    <inherited from parent>
    ==5990== 
    ==5990== Open file descriptor 1: /dev/pts/5
    ==5990==    <inherited from parent>
    ==5990== 
    ==5990== Open file descriptor 0: /dev/pts/5
    ==5990==    <inherited from parent>
    ==5990== 
    ==5990== 
    ==5990== HEAP SUMMARY:
    ==5990==     in use at exit: 0 bytes in 0 blocks
    ==5990==   total heap usage: 12,342,758 allocs, 12,342,758 frees, 517,074,936 bytes allocated
    ==5990== 
    ==5990== All heap blocks were freed -- no leaks are possible
    ==5990== 
    ==5990== For lists of detected and suppressed errors, rerun with: -s
    ==5990== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)