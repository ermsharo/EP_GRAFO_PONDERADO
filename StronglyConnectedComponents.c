
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "index.c"

Graph invertEdgesOfGraph(Graph g, vertex source);

void findSCCs(Graph g);

void printIntArray(int* arr, int size) {
    printf("[ ");
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("]\n");
}

void dfs_traversal_helper(Graph g, int source, bool* visited, int* stack, int* stack_idx, int* result, int* result_idx) {
    visited[source] = true;
    link LINK = g->adj[source];
    printf("%i \n", source);

    while (LINK) {
        if (!visited[LINK->w]) {
            dfs_traversal_helper(g, LINK->w, visited, stack, stack_idx, result, result_idx);
            printIntArray(result, *result_idx);
        
        }
        LINK = LINK->next;
    }
    printf("iserting : %i \n ", source);
    stack[(*stack_idx)++] = source;
    result[(*result_idx)++] = source;
}

void dfs_traversal_cluster(Graph g, int source, bool* visited, int* result){
    int num_of_vertices = g->V;
    int stack[num_of_vertices];
    int stack_idx = 0;
    int result_idx = 0;

    dfs_traversal_helper(g, source, visited, stack, &stack_idx, result, &result_idx);

}


void dfs_traversal(Graph g, int source, int* result) {
    int num_of_vertices = g->V;
    int stack[num_of_vertices];
    int stack_idx = 0;
    bool visited[num_of_vertices];
    memset(visited, false, sizeof(visited));
    int result_idx = 0;

    dfs_traversal_helper(g, source, visited, stack, &stack_idx, result, &result_idx);

    for (int i = 0; i < num_of_vertices; i++) {
        if (!visited[i]) {
            dfs_traversal_helper(g, i, visited, stack, &stack_idx, result, &result_idx);
        }
    }
    
    // Reverse the order of the result array to get the correct order
    for (int i = 0; i < num_of_vertices / 2; i++) {
        int temp = result[i];
        result[i] = result[num_of_vertices - 1 - i];
        result[num_of_vertices - 1 - i] = temp;
    }
}

// // Function to invert the edges of a given graph


Graph invertEdgesOfGraph(Graph g, vertex source)
{
    Graph graphReversed = GRAPHinit(g->V);
    vertex current;

    for (current = 0; current < g->V; current++)
    {
        link temp = g->adj[current];

        while (temp != NULL)
        {
            if (current != temp->w)
            {
                GRAPHinsertArcByIndex(graphReversed, temp->w, current);
            }
            temp = temp->next;
        }
    }

    return graphReversed;
}


void findSCCs(Graph g)
{
    int num_of_vertices = g->V;
    int *ordering = (int *)malloc(num_of_vertices * sizeof(int));
    dfs_traversal(g, 0, ordering);

    Graph invertedGraph = invertEdgesOfGraph(g, 0);
    bool visited[num_of_vertices];
    memset(visited, false, sizeof(visited));

    int scc = 1;
    for (int i = 0; i < num_of_vertices; i++)
    {
        int v = ordering[i];
        if (!visited[v])
        {
            printf("SCC %d:\n", scc);
            dfs_traversal_cluster(invertedGraph, v, visited, NULL);
            scc++;
            printf("\n");
        }
    }

    free(ordering);
}

int main() {
    int n_vertex = 6;
    Graph g = GRAPHinit(n_vertex);

    char *labels[] = { "a", "b", "c", "d", "e", "f" };
    setLabels(g, labels, 6);

    GRAPHinsertArcByLabel(g, "a", "b");
    GRAPHinsertArcByLabel(g, "a", "c");
    GRAPHinsertArcByLabel(g, "b", "c");
    GRAPHinsertArcByLabel(g, "b", "e");
    GRAPHinsertArcByLabel(g, "c", "b");
    GRAPHinsertArcByLabel(g, "e", "f");
    GRAPHinsertArcByLabel(g, "e", "d");
    GRAPHinsertArcByLabel(g, "d", "e");
 
    imprimeGrafo(g);
    //imprimeGrafoIndexes(g);
    
    //Graph graphReversed = invertEdgesOfGraph(g,0);

    //imprimeGrafoIndexes(graphReversed);

    findSCCs(g);



    // int result[g->V];
    // memset(result, -1, sizeof(result));

    // int num_of_vertices = g->V;
    // bool visited[num_of_vertices];
    // memset(visited, false, sizeof(visited));

    // dfs_traversal_cluster(g,1,visited,result);
    // //dfs_traversal(g, 0, result);

    // printf("DFS Traversal: ");
    // for (int i = 0; i < g->V; i++) {
    //     if ( result[i] == -1 )
    //         break;
    //     printf("%d ", result[i]);
    // }
    // printf("\n");

}
