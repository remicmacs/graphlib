//#include "c_utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <limits.h> // for type max and min
#define INFINITY INT_MAX
#define INIT INT_MIN

typedef enum bool_ {false, true} bool;


typedef struct graph_ {
    int verticenb;
    int * edges;

} graph;

typedef struct vertex_ {
    int vertexId;
    struct vertex_ * next;
} vertex;

typedef struct edge_ {
    int startId;
    int endId;
    int weight;
} edge;

typedef struct path_ {
    int cost;
    int endId;
    vertex * start;
} path;

int compareEdges(const void * ptr1, const void * ptr2);

edge * prim(graph myGraph, int startId);

edge * updateCosts(bool * processedV, graph myGraph, edge * previousStep, int currentVertex);

/**
 * Dijkstra algorithm to find shortest path between startId vertex and endId
 * vertex.
 *      Inputs : 
 *          {graph} myGraph - graph with an existing shortest path (simple
 *              and complete.
 *          {int} startId - ID of starting point.
 *          {int} endId - ID of end point.
 *      Output : 
 *          {path ** } list - [{path}]
 *              {path} : {
 *                  {int} Cost - cost of shortest path
 *                  {int} endId - ID of last vertex of path (goal)
 *                  {vertex *} start - linked list of vertices of shortest path
 *              }
 *          }
 */
path ** dijkstra(graph myGraph, int startId, int endId);

/**
 * Function to find next vertex to process
 */
int nextVertex(bool * processed, int * previousStep, int size);

/**
 * Function to process new cost of paths adding the new vertex newVertex
 */
int * updateStep(int * previousStep, int * newStep, int newVertex, graph myGraph);

/**
 * Function to return path from a full log of steps from Dijkstra's algorithm
 *      Inputs :
 *          {int **} log - the full log of steps
 *          {int} size - the size of the log
 *          {int} endId - the vertex goal of shortest path unique id
 *          {path *} shortest - a pointer to path to complete
 *      Output
 *          {path *} shortest - filled path pointer
 */
path * formatShortestPath(int ** log, int size, int endId, path * shortest);

/*
 * Fuction to allocate a graph which links the number of vertices and le edge
 * matrix
 *      Inputs : {int} verticenb, Number of vertices
 *      Output : {graph} newGraph {{int} verticenb ; {int} edges[verticenb]}
 */
graph initGraph(int verticenb);

/**
 * Helper function to parse a graph from stdin
 *      Graph data struct in stdin should be of format :
 *      {int} nb of vertices\n
 *      nb of vertices lines as such:
 *      ({int} value) * nb of vertices\n
 *
 *      INCORRECTLY FORMATTED GRAPHS NOT SUPPORTED
 *
 */
graph parseGraph();

/**
 * Helper function to diplay matrix
 */
void displayGraphMatrix(graph myGraph);

/**
 * Helper function to display list of vertices
 */
void displayList(vertex * start);

/**
 * Helper function to display unprocessed nodes from boolean list of vertices
 */
void displayUnprocessed(bool * processed, int size);

/**
 * Helper function to display a step of the log
 */
void displayStep(int * step, int size);

/**
 * Helper function to print log of steps
 */
void displaySteps(int ** log, int stepnb, int sizeofsteps);

/**
 * Helper function to display a valuated edge
 */
void displayEdge(edge anEdge);


/**
 * Helper function to display a list of edges
 */
void displayCosts(edge * list, int nb);

/**
 * UNUSED Function to initialize a list of vertices
 */
vertex * unprocessedVertices(graph myGraph);

/**
 * UNUSED function to return successors list of the given vertex
 */
int * successorList(graph myGraph, int vertexId);
/**
 * UNUSED function to return predecessors list of the given vertex
 */
int * predecessorList(graph myGraph, int vertexId);


