#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int * matrix;
    int sizemax;
} Graph;

Graph createGraph(int sizemax) {
    Graph newGraph;
    newGraph.matrix = (int*)malloc(sizemax * sizemax * sizeof(int));
    newGraph.sizemax = sizemax;
    int i;
    for (i = 0; i < sizemax * sizemax; i++) {
        newGraph.matrix[i] = 0;
    }
    return newGraph;
};

void addEdge(Graph graph, int v1, int v2) {
    graph.matrix[v1 * graph.sizemax + v2 ] = 1;
    graph.matrix[v2 * graph.sizemax + v1] = 1;
};

int adjacent(Graph graph, int v1, int v2) {
    return graph.matrix[v1 * graph.sizemax + v2];
};

int getAdjacentVertices(Graph graph, int vertex, int* output) {
    int count = 0;
    int i;
    for (i = 0; i < graph.sizemax; i++) {
        if (adjacent(graph, vertex, i) == 1) output[count++] = i;
    }
    return count;
}; 
void dropGraph(Graph graph){

};

int main() {
    int i, n, output[100];
    Graph g = createGraph(100);
    addEdge(g, 0, 1);
    addEdge(g, 0, 2);
    addEdge(g, 1, 2);
    addEdge(g, 1, 3);
    n = getAdjacentVertices(g, 2, output);
    if (n == 0)
        printf("No adjacent vertices of node 2\n");
    else {
        printf("Adjacent vertices of node 2:");
        for (i = 0; i < n; i++) printf("%5d", output[i]);
    }
    printf("\n");
    return 0;
}