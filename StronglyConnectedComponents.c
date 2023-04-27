
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "index.c"

struct ClusterResult {
    int **stronglyConnectedComponents;
    int *component_sizes;
    int count;
};

Graph invertEdgesOfGraph(Graph g, vertex source);

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
    // printf("%i \n", source);

    while (LINK) {
        if (!visited[LINK->w]) {
            dfs_traversal_helper(g, LINK->w, visited, stack, stack_idx, result, result_idx);
            // printIntArray(result, *result_idx);
        
        }
        LINK = LINK->next;
    }
    // printf("iserting : %i \n ", source);
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


void dfs_traversal(Graph g, int source, int* result, int* stack) {
    
    int num_of_vertices = g->V;
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

void printClusterResult(struct ClusterResult cluster_result) {
    for (int i = 0; i < cluster_result.count; i++) {
        printf("Component %d: [", i);
        for (int j = 0; j < cluster_result.component_sizes[i]; j++) {
            printf("%d", cluster_result.stronglyConnectedComponents[i][j]);
            if (j < cluster_result.component_sizes[i] - 1) {
                printf(", ");
            }
        }
        printf("]\n");
    }
}

struct ClusterResult findStronglyConnectedComponents(Graph g, int num_of_vertices, int *stack) {
    bool visited[num_of_vertices];
    memset(visited, false, sizeof(visited));

    int **stronglyConnectedComponents = (int **)malloc(num_of_vertices * sizeof(int *));
    int *component_sizes = (int *)malloc(num_of_vertices * sizeof(int));
    int sc_components_count = 0;

    int top = num_of_vertices - 1;

    int result[num_of_vertices];
    memset(result, -1, sizeof(result));

    while (top >= 0) {
        int source = stack[top];
        top--;

        printf("source : %i\n", source);

        if (!visited[source]) {
            memset(result, -1, sizeof(result));
            dfs_traversal_cluster(g, source, visited, result);

            int valid_elements_count = 0;
            for (int i = 0; i < num_of_vertices; i++) {
                if (result[i] != -1) {
                    valid_elements_count++;
                }
            }

            printf("The valid elements to count are : %d\n", valid_elements_count);

            stronglyConnectedComponents[sc_components_count] = (int *)malloc(valid_elements_count * sizeof(int));
            component_sizes[sc_components_count] = valid_elements_count;
            int index = 0;
            for (int i = 0; i < num_of_vertices; i++) {
                if (result[i] != -1) {
                    stronglyConnectedComponents[sc_components_count][index++] = result[i];
                }
            }

            printf("Stored Clusterized DFS : ");
            for (int i = 0; i < num_of_vertices; i++) {
                if (result[i] != -1)
                    printf("%d ", stronglyConnectedComponents[sc_components_count][i]);
            }
            printf("\n");

            sc_components_count++;

            printf("Clusterized DFS : ");
            for (int i = 0; i < num_of_vertices; i++) {
                if (result[i] != -1)
                    printf("%d ", result[i]);
            }
            printf("\n");
        }
    }

    struct ClusterResult cluster_result;
    cluster_result.stronglyConnectedComponents = stronglyConnectedComponents;
    cluster_result.component_sizes = component_sizes;
    cluster_result.count = sc_components_count;

    return cluster_result;
}

void processGraph(Graph g) {
    // First step: get finish times
    int result[g->V];
    memset(result, -1, sizeof(result));

    int num_of_vertices = g->V;

    int stack[num_of_vertices];

    dfs_traversal(g, 0, result, stack);

    printf("Stack: ");
    for (int i = 0; i < g->V; i++) {
        if (result[i] == -1)
            break;
        printf("%d ", stack[i]);
    }
    printf("\n");

    // Second step: get finish times

    Graph graphReversed = invertEdgesOfGraph(g, 0);

    // Fourth step: Clusterize elements

    struct ClusterResult clusterResult = findStronglyConnectedComponents(graphReversed, g->V, stack);

    printClusterResult(clusterResult);
}
