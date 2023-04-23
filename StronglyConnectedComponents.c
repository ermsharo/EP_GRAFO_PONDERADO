
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "index.c"

void dfs_traversal_helper(Graph g, int source, bool* visited, int* stack, int* stack_idx, int* result) {
    visited[source] = true;
    link LINK = g->adj[source];
    printf("%i \n", source);
    
    while (LINK) {
        if (!visited[LINK->w]) {
            dfs_traversal_helper(g, LINK->w, visited, stack, stack_idx, result);
        }
        LINK = LINK->next;
    }
    stack[(*stack_idx)++] = source;
    result[(*stack_idx)-1] = source;
}

void dfs_traversal(Graph g, int source, int* result) {
    int num_of_vertices = g->V;
    int stack[num_of_vertices];
    int stack_idx = 0;
    bool visited[num_of_vertices];
    memset(visited, false, sizeof(visited));

    dfs_traversal_helper(g, source, visited, stack, &stack_idx, result);

    for (int i = 0; i < num_of_vertices; i++) {
        if (!visited[i]) {
            dfs_traversal_helper(g, i, visited, stack, &stack_idx, result);
        }
    }
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

    int result[g->V];
    memset(result, 0, sizeof(result));

    dfs_traversal(g, 0, result);

    printf("DFS Traversal: ");
    for (int i = 0; i < g->V; i++) {
        printf("%d ", result[i]);
    }
    printf("\n");

}
