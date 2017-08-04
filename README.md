# UPGMA

CPSC 221 2017S1 Project: 
UPGMA (Unweighted Pair Group Method with Arithmetic Mean) is a simple bottom-up hier- archical clustering method used to construct a phylogenetic tree (a tree of life) from the pairwise (evolutionary) distances between species invented by Sokal and Michener in 1958. The method works by clustering the species, at each stage joining two clusters together that have the smallest distance.

Compile the program using: ```make```

Run the program using: ```./upgma species.txt```


### List of Files:
1. README.md: this file
2. Makefile: compiler instruction
3. dynmatrix.cc - implementation of the Dynamic Matrix and helper functions to print and update
4. dynmatrix.h - header file with structs for ClusterNode and DistanceNode, as well as function declarations
5. main.cc - UPGMA program that reads input from the specified text file and performs clustering until only one cluster remains
6. species.txt - sample input to the UPGMA program
7. proj1-instructions.pdf - instructions to project

