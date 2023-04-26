
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
    
    

    //imprimeGrafoIndexes(graphReversed);

    // > Primeira etapa : pegar tempos de termino

    int result[g->V];
    memset(result, -1, sizeof(result));

    int num_of_vertices = g->V;
    bool visited[num_of_vertices];
    memset(visited, false, sizeof(visited));

    int stack[num_of_vertices];
    
    dfs_traversal(g, 0, result, stack);

    printf("Stack: ");
    for (int i = 0; i < g->V; i++) {
        if ( result[i] == -1 )
            break;
        printf("%d ", stack[i]);
    }
    printf("\n");

    // > Segunda etapa : pegar tempos de termino

    Graph graphReversed = invertEdgesOfGraph(g,0);

    // > Quarta etapa : Clusterizar elementos 


    int **stronglyConnectedComponents = (int **)malloc(num_of_vertices * sizeof(int *));
    int *component_sizes = (int *)malloc(num_of_vertices * sizeof(int));
    int sc_components_count = 0;

    

    int top = num_of_vertices - 1;

    memset(result, -1, sizeof(result));

    //dfs_traversal_cluster(graphReversed,0,visited,result);

    // int *resultCluster = (int *)malloc(num_of_vertices * sizeof(int));
    // memset(resultCluster, -1, num_of_vertices * sizeof(int));

    // for (int i = 0; i < num_of_vertices; i++) {
        
    //     printf("%d", resultCluster[i]);
        
    // }



    while (top >= 0) {
        int source = stack[top];
        top--;

        printf("source : %i ", source);
        printf("\n");

         if (!visited[source]) {
            
               //int resultCluster[g->V];
               memset(result, -1, sizeof(result));

               dfs_traversal_cluster(graphReversed,source,visited,result);

                int valid_elements_count = 0;
                for (int i = 0; i < num_of_vertices; i++) {
                    if (result[i] != -1) {
                        valid_elements_count++;
                    }
                }

                printf("The valid elements to count are : %d \n", valid_elements_count);

                stronglyConnectedComponents[sc_components_count] = (int *)malloc(valid_elements_count * sizeof(int));
                component_sizes[sc_components_count] = valid_elements_count;
                int index = 0;
                for (int i = 0; i < num_of_vertices; i++) {
                    if (result[i] != -1) {
                        stronglyConnectedComponents[sc_components_count][index++] = result[i];
                    }
                }
                

                // printf("DFS Traversal CLUSTER: ");
                printf("Stored Clusterized DFS : ");
                for (int i = 0; i < g->V; i++) {
                    if ( result[i] != -1 )
                        printf("%d ", stronglyConnectedComponents[sc_components_count][i]);
                }
                printf("\n");

                sc_components_count++;

                // printf("DFS Traversal CLUSTER: ");
                printf("Clusterized DFS : ");
                for (int i = 0; i < g->V; i++) {
                    if ( result[i] != -1 )
                        printf("%d ", result[i]);
                }
                printf("\n");


            
            //free(result);
         }

    }

    struct ClusterResult cluster_result;
    cluster_result.stronglyConnectedComponents = stronglyConnectedComponents;
    cluster_result.component_sizes = component_sizes;
    cluster_result.count = sc_components_count;

    // printf("Result Cluster: [ \n");
    // int printed_elements = 0;
    // for (int i = 0; i < sc_components_count; i++) {
    //     printf("%d Component ", i);
    //     printf("\n");
        
    //     printf("size of component : %d", component_sizes[i]);

    //     printf("\n");
    // }

    printf("Strongly Connected Components:\n");
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

    //free(visited);

    // printf("DFS Traversal: ");
    // for (int i = 0; i < g->V; i++) {
    //     if ( result[i] == -1 )
    //         break;
    //     printf("%d ", result[i]);
    // }
    // printf("\n");



}
