#include <stdio.h>
#include <stdlib.h>

// Structure to represent an edge in the graph
struct Edge {
    int src, dest, weight;
};

// Structure to represent a subset for the disjoint-set data structure
struct Subset {
    int parent;
    int rank;
};

// Function to find the set of an element 'i'
int find(struct Subset subsets[], int i) {
    if (subsets[i].parent != i)
        subsets[i].parent = find(subsets, subsets[i].parent);
    return subsets[i].parent;
}

// Function to perform union of two sets
void unionSets(struct Subset subsets[], int x, int y) {
    int rootX = find(subsets, x);
    int rootY = find(subsets, y);

    if (subsets[rootX].rank < subsets[rootY].rank)
        subsets[rootX].parent = rootY;
    else if (subsets[rootX].rank > subsets[rootY].rank)
        subsets[rootY].parent = rootX;
    else {
        subsets[rootY].parent = rootX;
        subsets[rootX].rank++;
    }
}

// Compare function for sorting edges by weight
int compareEdges(const void* a, const void* b) {
    return ((struct Edge*)a)->weight - ((struct Edge*)b)->weight;
}

// Function to find the Minimum Spanning Tree using Kruskal's Algorithm
void kruskalMST(struct Edge edges[], int V, int E) {
    struct Edge resultMST[V]; // Stores the MST edges
    int e = 0; // Index variable for resultMST[]
    int i = 0; // Index variable for sorted edges array

    qsort(edges, E, sizeof(edges[0]), compareEdges);

    struct Subset* subsets = (struct Subset*)malloc(V * sizeof(struct Subset));

    for (int v = 0; v < V; v++) {
        subsets[v].parent = v;
        subsets[v].rank = 0;
    }

    while (e < V - 1 && i < E) {
        struct Edge nextEdge = edges[i++];

        int x = find(subsets, nextEdge.src);
        int y = find(subsets, nextEdge.dest);

        if (x != y) {
            resultMST[e++] = nextEdge;
            unionSets(subsets, x, y);
        }
    }

    printf("Edges in the Minimum Spanning Tree:\n");
    for (i = 0; i < e; i++) {
        printf("%d - %d  Weight: %d\n", resultMST[i].src, resultMST[i].dest, resultMST[i].weight);
    }

    free(subsets);
}

int main() {
    int V = 4; // Number of vertices
    int E = 5; // Number of edges
    struct Edge edges[] = {
        {0, 1, 10},
        {0, 2, 6},
        {0, 3, 5},
        {1, 3, 15},
        {2, 3, 4}
    };

    kruskalMST(edges, V, E);

    return 0;
}
