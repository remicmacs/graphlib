# graphlib.c
C library to implement various graph theory algorithms

## Usage
Currently, there is a helper main function in the `graphlib.c` file. It can be
use as it is but needs inputs to fill the graph.
A test file `matrix3` is proposed to try the program. The test file represents a
graph and will be parsed by the program if it is in stdin.
To use it, build the program :
```
$ gcc graphlib.c -o prog
```

Then you can try Dijkstra and Prim algorithm with the given example graph :
```
$ ./prog < matrix3
```


## Purpose
This project is an exercice to implement basic algorithms of graph theory to try
to understand them better.

The purpose is to have various common algorithm to test result values obtained
when doing exercices in class.

## Formats
### Matrix representation
The representation of a valuated graph by a matrix is pretty straighforward.

Below is an example test file representing a matrix :
```
6
0 7 9 0 0 14
7 0 10 15 0 0
9 10 0 11 0 2
0 15 11 0 6 0
0 0 0 6 0 9
14 0 2 0 9 0
```

The first line is the number of vertices for the program to know how many values
to parse in total.
Then each line is the cost from the row number vertex to column number vertex.

Numerotation begins from 0 to simplify processing.

## Data structures
### graph
A graph is composed of :
* `verticesnb` - its number of vertices
* `edges` - an array of verticesnb * verticesnb integers representing the
      edge valuation. If it is 0, there is no path between the corresponding
      vertices.

For instance, given a graph `myGraph` : 
`*(myGraph.edge+(2*verticesnb)+3)` will be the cost to go from vertex 2 to
vertex 3.

### vertex
This type is meant to be linked to represent a path and is composed of :
* `vertexId` - the integer representing the unique id of the vertex
* `next` - a pointer to the next vertex in the path. If it is NULL, the current
  vertex is the last

### path
This type represent a path, with its succession of vertices, and its total cost
to go from its start to its end

### edge
This types is intended to represent a couple of vertices designated by their
IDs, hence an integer. This couple is associated to its valuation, called
weight.

## Algorithms

### Dijkstra
Finds the shortest path between a starting point and a end point

```
    path * shortest = dijkstra(myGraph, 0, 3);
    // Shortest now contains shortest path from vertex nb 0 to vertex nb 3
```

**UNTESTED** If there is no shortest path, returns { INFINITY, NULL }.

### Prim
Finds the minimum spanning tree. Needs a starting point as input.
Returns a lists of edges and their valuations to represent a partial graph.
For a graph with n vertices, returns an array of n-1 edges

```
    // Finds the minimum spanning tree
    edge * spanningTree = prim(myGraph, 0);

    // Displays the edges that are part of the spanning tree
    displayCosts(spanningTree, myGraph.nbvertices - 1);
```

## TODOs
* Implement secure parsing from file
* Implement errors management :
    * Matrix not correctly formated
    * Matrix not representing a complete graph
* Implement other lighter formats such as successors lists
* Prim :
    * Implement another format (new partial graph with only the selected edges)
* Bellman-Ford's algorithm
* Minimum/maximum spanning tree
* Makefile
* args parsing rather than changing stdin
* Migrating some helper functions to c_utils.c
