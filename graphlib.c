#include "graphlib.h"

int compareEdges(const void * ptr1, const void * ptr2) {
    edge * edge1 = (edge *) ptr1;
    edge * edge2 = (edge *) ptr2;

    if (edge1->weight < edge2->weight) return -1;
    else if (edge1->weight > edge2->weight) return 1;
    else return 0;
}

void displayEdge(edge anEdge) {
    printf("<%d,%d>", anEdge.startId, anEdge.endId );

    if (anEdge.weight == INFINITY) printf(": INF ;");
    else printf(": %d ;", anEdge.weight);
}

void displayCosts(edge * costs, int size) {
    printf("[");
    for (int i = 0 ; i < size ; i++) {
        edge currentEdge = *(costs+i);
        //printf("<%d,%d>", currentEdge.startId, currentEdge.endId );

        //if (currentEdge.weight == INFINITY) printf(" = INF ;");
        //else printf(" %d ;", currentEdge.weight);
        displayEdge(currentEdge);
    }
    printf("]\n");
}

edge * prim(graph myGraph, int startId) {
    /**
     * Initialization of unprocessed vertices list
     * A bool matrix initialized to false
     * if processedV[i] is true, vertex i has been processed
     */
    bool * processedV = (bool *) calloc(myGraph.verticenb, sizeof(bool));
    int currentVertex = startId;

    edge * costs = (edge *) malloc(sizeof(edge) * myGraph.verticenb);
    
    // Initializing costs to INIFINITY
    edge startingEdge = { currentVertex, currentVertex, INFINITY};
    for (int i = 0 ; i < myGraph.verticenb ; i++) {
        edge currentEdge;
        if (i != currentVertex) {
            currentEdge.weight = INFINITY;
            currentEdge.startId = currentVertex;
            currentEdge.endId = i;
        } else {
            currentEdge = startingEdge;
        }
        *(costs+i) = currentEdge;
    }
    processedV[startId] = true;

    // List of edges that will represent the minimum spanning tree
    edge * minimumSpanningTree = (edge *) malloc(sizeof(edge) * (myGraph.verticenb-1));

    // End of initialization
    
    for (int i = 1 ; i < myGraph.verticenb ; i++) {
        edge betterEdge;
        
        // Processing current costs to vertices
        costs = updateCosts(processedV, myGraph, costs, currentVertex);
        
        // Sorting the costs
        qsort(costs, myGraph.verticenb, sizeof(edge), &compareEdges);
        
        // Taking minimum cost among unprocessed vertices
        for (int j = 0 ; j < myGraph.verticenb ; j++) {
            if (!processedV[(costs+j)->endId]) {
                betterEdge = *(costs+j);
                break;
            }
        }

        *(minimumSpanningTree+i-1) = betterEdge;
        processedV[betterEdge.endId] = true;
        currentVertex = betterEdge.endId;
    }

    return minimumSpanningTree;
}

edge * updateCosts(bool * processedV, graph myGraph, edge * previousStep, int currentVertex) {
    for (int i = 0; i < myGraph.verticenb ; i++) {
        edge currentEdge = *(previousStep+i);

        if (!processedV[currentEdge.endId]){
            int newWeight = (*(myGraph.edges+(currentVertex*myGraph.verticenb)+currentEdge.endId) == 0) ? INFINITY : *(myGraph.edges+(currentVertex*myGraph.verticenb)+currentEdge.endId);

            if( currentEdge.weight > newWeight ) {
                currentEdge.startId = currentVertex;
                currentEdge.weight = newWeight;
                *(previousStep+i) = currentEdge;
            }
        }
    }
    return previousStep;

}

path ** dijkstra(graph myGraph, int startId, int endId) {
    // Init log of steps
    int ** steps = (int **) malloc(sizeof(int *) * myGraph.verticenb + 1);

    // First step : initialization
    int * currentStep = (int *) malloc(sizeof(int ) * myGraph.verticenb + 1);
    int stepIndex = 0;
    *currentStep = INIT;
    for (int i = 1 ; i <= myGraph.verticenb ; i++) {
        // All cost but starting vertex are initialized to INFINITY
        *(currentStep+i) = (i-1 == startId) ? 0 : INFINITY;
    }
    *steps = currentStep; // inserting current step into log
    stepIndex = 1; // Moving step index forward


    ////////////////////////////////////////////////////////////////////////////
    // DEBUG printf statements :
    // printf("Current step : [");
    // displayStep(currentStep, myGraph.verticenb + 1);
    // printf("]\n");
    ////////////////////////////////////////////////////////////////////////////
    
    /**
     * Initialization of unprocessed vertices list
     * A bool matrix initialized to false
     * if processedV[i] is true, vertex i has been processed
     */
    bool * processedV = (bool *) calloc(myGraph.verticenb, sizeof(bool));
// displayUnprocessed(processedV, myGraph.verticenb);

    
    // Finding next vertex to process
    int newVertex = nextVertex(processedV, currentStep, myGraph.verticenb);

    // while there is a new vertex to process, loop
    while (newVertex != INT_MIN) {
        // Step init
        currentStep = (int *) malloc(sizeof(int) * myGraph.verticenb+1);
        *(steps+stepIndex) = currentStep; // Attaching current step to log
        
        // currentStep[0] is index of vertex currently being processed
        *currentStep = newVertex;
        *(processedV+newVertex) = true; // Vertex has been processed
        
        // updating values of
        currentStep = updateStep(*(steps+stepIndex-1), currentStep, newVertex, myGraph);
        
        // Findin next vertex to process
        newVertex = nextVertex(processedV, currentStep, myGraph.verticenb);
        stepIndex++;
    }

    // Printing final log of steps
    // printf("\n\nFINAL STEPS\n");
    // displaySteps(steps, stepIndex, myGraph.verticenb+1);
    
    path ** list = (path ** ) malloc(sizeof(path *) * myGraph.verticenb);
    // Initialization of shortest path
    for (int i = 0 ; i < myGraph.verticenb ; i++) {
        path * shortest = (path *) malloc(sizeof(path));
        shortest->start = NULL;
        shortest->cost = INFINITY;
        shortest = formatShortestPath(steps, stepIndex-1, i, shortest);
        *(list+i) = shortest;
    }

    free(processedV);

    return list;
}

int nextVertex(bool * processed, int * previousStep, int size) {
    int min = INFINITY; // Minimum value found initialized to infinity
    int index;
    int minIndex = INT_MIN; // Minimum id of vertex is init to minimum
    
    for (index = 0 ; index < size; index++) {
        if (!*(processed+index)){
            // Finding shortest path in unprocessed vertices
            if (*(previousStep+index+1) < min) {
                min = *(previousStep+index+1);
                minIndex = index;
            }
        }
    }
    return minIndex;
}

int * updateStep(
        int * previousStep, 
        int * newStep, 
        int newVertex, 
        graph myGraph) {

    // newVertex is current starting vertex being added to log
    *(newStep) = newVertex; // newStep[0] = current vertex

    int edgeValue;

    // For each vertex
    for (int i = 1 ; i <= myGraph.verticenb ; i++) {
        // Recovering cost to go from current vertex to vertex i-1
        edgeValue = *(myGraph.edges+(myGraph.verticenb * newVertex)+(i-1));

        /* if vertex i-1 is current vertex, do not change value*/
        if (i-1 == newVertex) { 
            *(newStep+i) = *(previousStep+i);
        } else if (edgeValue == 0) { // if there is no edge, do not change value
            *(newStep+i) = *(previousStep+i);
        } else { // else value is updated
            // candidate value is cost from current vertex to vertex i-1
            // + cost from initial vertex to current vertex
            int candidateValue = edgeValue + *(previousStep+newVertex+1);

            // If candidate value is better (lower) than previous, update
            *(newStep+i) = (candidateValue < *(previousStep+i)) 
                ?
                candidateValue  : *(previousStep+i);
        }
    }
    return newStep;
}

path * formatShortestPath(int ** log, int logSize, int endId, path * shortest) {
    // Cost is recovered in last step of log
    shortest->cost = *(*(log+logSize)+endId+1);
    shortest->endId = endId;
    // Current vertex init
    vertex * current = (vertex *) malloc(sizeof(vertex));
    current->vertexId = endId;
    current->next = NULL;


    vertex * previous;

    int currCost, prevCost;
    int currVertex = endId;

    // Looping decrementing size of log used as index
    while(logSize > 0) {
        // Recovering cost
        currCost = *(*(log+logSize)+currVertex+1);
        prevCost = *(*(log+logSize-1)+currVertex+1);

        // Doing stg only if current cost != cost of previous step
        if (currCost != prevCost) {
            // Allocating new vertex link of list
            previous = (vertex *) malloc(sizeof(vertex));
            // First element of previous step is the previous vertex in path
            previous->vertexId = **(log+logSize);
            currVertex = previous->vertexId;

            // Linking to current vertex and shifting backwards in path
            previous->next = current;
            current = previous;
        }
        logSize--;
    }
    
    // Attaching list to path
    shortest->start = current;

    return shortest;
}

graph initGraph(int verticenb) {
    graph newGraph;
    newGraph.verticenb = verticenb;
    
    // Edges matrix allocation
    newGraph.edges = (int *) malloc(sizeof(int) * (verticenb*verticenb));

    return newGraph;
}

graph parseGraph() {
    graph parsedGraph;
    int x,y = 0;
    int verticenb;

    // Recovering number of vertices
    scanf("%d\n", &verticenb);
    
    // Graph initialization
    parsedGraph = initGraph(verticenb);
    
    // Scanning each edge value
    for (y = 0 ; y < verticenb ; y++) {
        for(x = 0 ; x < verticenb ; x++) {
            scanf("%d",(parsedGraph.edges+(y*verticenb)+x));
        }
    }
    return parsedGraph;
}

void displayGraphMatrix(graph myGraph) {
    printf("Matrix of graph :\n");
    int x,y;
    for (y = 0 ; y < myGraph.verticenb ; y++) {
        for (x = 0 ; x < myGraph.verticenb ; x++) {
            printf("%02d\t", *(myGraph.edges+(y*myGraph.verticenb)+x));
        }
        printf("\n");
    }
}

void displayList(vertex * list) {
    vertex * current = list;
    while(current != NULL) {
        printf("%d", current->vertexId);
        if (current->next != NULL) printf(" -> ");
        current = current->next;
    }
}

void displayUnprocessed(bool * list, int size) {
    printf("Unprocessed vertices : ");
    for (int i = 0 ; i < size ; i++) {
        if (*(list+i) == false){
            printf("%d\t", i);
        }
    }
    printf("\n");
}

void displayStep(int * step, int nb) {
    if (*(step) == INIT) {
        printf(" INIT : ");
    } else {
        printf("%5d : ", *(step));
    }
    
    for (int i = 1 ; i < nb ; i++) {
        if (*(step+i) == INFINITY) {
            printf("| +inf  ");
        } else {
            printf("|%5d  ", *(step+i));
        }
    }
}

void displaySteps(int ** steps, int maxStep, int nb) {
    // Display until step n° maxStep all nb value of step
    for (int i = 0; i < maxStep ; i++) {
        printf("[");
        displayStep(*(steps+i), nb);
        printf("]\n");
    }
}

/******************************************************************************/

vertex * unprocessedVertices(graph myGraph) {
    // Firt vertex init
    vertex * start = (vertex *) malloc(sizeof(vertex));
    start->vertexId = *(myGraph.edges);
    start->next = NULL;

    vertex * new;

    // Current vertex init
    vertex * current;
    current = start;
    for (int i = 1 ; i < myGraph.verticenb ; i++ ) {
        // new vertex allocation
        new = (vertex *) malloc(sizeof(vertex));
        new->vertexId = i;
        new->next = NULL;
        // New is attached
        current->next = new;

        // Shifting current
        current = current->next;
    }

    return start;
}

int * successorList(graph myGraph, int vertexId) {
    int * list = (int *) malloc(sizeof(int) * myGraph.verticenb);
    int nb = 0;
    for (int i = 0 ; i < myGraph.verticenb ; i++) {
        if (*(myGraph.edges+((vertexId * myGraph.verticenb)) + i) != 0) {
            *(list+nb) = i;
            nb++;
        }
    }
    printf("Vertex %d has sucessors : ", vertexId);
    for (int i = 0 ; i < nb ; i++) {
        printf("%d\t", *(list+i));
    }
    printf("\n");
    return list;
}

int * predecessorList(graph myGraph, int vertexId) {
    int * list = (int *) malloc(sizeof(int) * myGraph.verticenb);
    int nb = 0;

    for (int i = 0 ; i < myGraph.verticenb ; i++) {
        if (*(myGraph.edges+((vertexId * myGraph.verticenb)) + i) != 0) {
            *(list+nb) = i;
            nb++;
        }
    }
    printf("Vertex %d has predecessors : ", vertexId);
    for (int i = 0 ; i < nb ; i++) {
        printf("%d\t", *(list+i));
    }
    printf("\n");
    return list;
}

/******************************************************************************/

// Exemple main on how to use the library
int main(int argc, char ** argv) {
    graph myGraph = parseGraph();
    path ** list;

    displayGraphMatrix(myGraph);

    list = dijkstra(myGraph, 0, 4);
    for (int i = 0 ; i < myGraph.verticenb ; i++) {
        path * shortest = *(list+i);
        printf("Cost of shortest path between X%d to X%d = %d\n", 0, i, shortest->cost);
        printf("<");
        displayList(shortest->start);
        printf(">\n");
    }

    edge * spanningTree = prim(myGraph, 0);
    printf("Final spanning tree : \n");
    displayCosts(spanningTree, myGraph.verticenb-1);
}
