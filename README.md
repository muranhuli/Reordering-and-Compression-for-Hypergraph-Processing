# Reordering and Compression for Hypergraph Analysis

## Introduction
This repository contains the source code for the Reordering and Compression for Hypergraph Analysis project.

Below is a detailed description of the function of each directory and file.

## Experimental Dataset
The experimental datasets are obtained from http://www.cs.cornell.edu/~arb/data/

## Directory Structure

### genDataStorage
This directory contains files to generate various hypergraph storage formats.

- compressUnordering.cpp: Generates the hypergraph storage format for a one-dimensional compressed array, without vertex or hyperedge reordering.
- reorderingHyperedges.cpp: Generates the hypergraph storage format for one-dimensional compressed arrays, with hyperedge reordering and vertex non-reordering.
- reorderingVertices.cpp: Generates a compressed one-dimensional array hypergraph storage format, with vertex reordering and without hyperedge reordering.
- reorderingVerticesHyperedges.cpp: Generates the hypergraph storage format for compressed one-dimensional array, with both vertices and hyperedges reordering.

### includes
This directory contains program dependencies files.

- adjacencyList.h: Hypergraph adjacency list storage format. Algorithms for executing the adjacency list storage format.
- oneDimensionalArray.h: Hypergraph one-dimensional array storage format. Algorithm used for executing the one-dimensional array storage format.

### applications
This directory contains the application of the hypergraph algorithm. There are several algorithms available, including: BFS, DFS, SCC, NQ, PR, kcore, SSSP, and MIS.

- XXXAdjList.cpp: Algorithm for adjacency list storage format.
- XXXOneDimArray.cpp: Algorithm for One-Dimensional Array Storage Format.

### measureMemory
This directory contains a file for measuring algorithm compression efficiency.

- measureMemory.cpp: Measure algorithm compression efficiency.

## Generating various hypergraph storage formats
1. Set the file path for the files inside the `genDataStorage` folder.
2. Change to the `genDataStorage` directory using `cd genDataStorage`.
3. Run `make`.
4. Execute the corresponding executable file.

## Running the algorithm
1. Set the file path for the files inside the `includes` folder.
2. Execute the makefile for the main program.
3. Execute the corresponding program to measure its execution time.
