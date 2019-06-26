# Spanning trees with few branchings
This repository contains code, a technical report, and a presentation (these last two in Brazilian Portuguese) for the term
project of the MSc course MATD74 - Algorithms & Graphs, taken at Federal University of Bahia (UFBA). The project was to propose a
new approach for a (preferrably NP-Hard) problem, for which I chose the Minimum Branching-vertices Spanning Tree, i.e. find the
spanning tree which have the least number of vertices with degree greater than 2.

# How to run
In order to run the local heuristics based on greedily optimizing the potential, first compile the executable:
```
mkdir build
make
```

If everything went well, this should have compiled a `run_instance.out` executable. To run it, use:
```
./run_instance.out path_to_instance
```

The output should be the list of edges in the found tree, followed by the number of branch vertices found.
