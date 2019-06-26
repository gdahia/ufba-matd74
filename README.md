# Spanning trees with few branchings
This repository contains code, a technical report, and a presentation (these last two in Brazilian Portuguese) for the term
project of the MSc course MATD74 - Algorithms & Graphs, taken at Federal University of Bahia (UFBA). The project was to propose a
new approach for a (preferrably NP-Hard) problem, for which I chose the Minimum Branching-vertices Spanning Tree, i.e. find the
spanning tree which have the least number of vertices with degree greater than 2.

# How to run
## Compilation
In order to run the local heuristics based on greedily optimizing the potential, first compile the executable:
```
cd implementation
mkdir build
make
```

## Single instance
If everything went well, this should have compiled a `run_instance.out` executable. To run it, use:
```
./run_instance.out path_to_instance
```

The output should be the list of edges in the found tree, followed by the number of branch vertices found.

## Multiple instances
To run for multiple instances at once, compile the path to the instances in a file `instance_list.txt`, a path per line, and then
run:
```
./run_instance_list.out instance_list.txt
```

The output should be the list of processed instances, expressed as the path to their file, and the number of branch vertices for
the tree in that instance, one instance per line.

# Instance format
We follow the format outlined by the instances of
[Carrabs et al.](http://www.dipmat2.unisa.it/people/carrabs/www/DataSet/MBV_Instances.zip),
so the instance files above should be formated likewise. The format is first a single line with three space separated integers:
the number of vertices, the number of edges, and a value to be ignored. The following lines, one per edge, have three space
separated integers: the two endpoints of an edge in 1-indexed values, and a value to be ignored.
