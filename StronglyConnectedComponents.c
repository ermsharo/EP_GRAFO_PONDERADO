
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "index.c"

Graph test(int size);

// Guarda resultado dos nos que coompoem um grafo fortemente conexo
struct ClusterResult {
    int **stronglyConnectedComponents;
    int *component_sizes;
    int count;
    char ***labels;
};

// Cria uma especie de mapa dos nos exitentes no grafo 
typedef struct {
    char **keys;
    char **values;
    int size;
} LabelToComponentMap;

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
    printf("printing the strongly connected components : \n");
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

void printLabelsClusterResult(struct ClusterResult cluster_result) {
    printf("Printing the strongly connected components:\n");
    for (int i = 0; i < cluster_result.count; i++) {
        printf("Component %d: [", i);
        for (int j = 0; j < cluster_result.component_sizes[i]; j++) {
            printf("%s", cluster_result.labels[i][j]);
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


        if (!visited[source]) {
            memset(result, -1, sizeof(result));
            dfs_traversal_cluster(g, source, visited, result);

            int valid_elements_count = 0;
            for (int i = 0; i < num_of_vertices; i++) {
                if (result[i] != -1) {
                    valid_elements_count++;
                }
            }

            stronglyConnectedComponents[sc_components_count] = (int *)malloc(valid_elements_count * sizeof(int));
            component_sizes[sc_components_count] = valid_elements_count;
            int index = 0;
            for (int i = 0; i < num_of_vertices; i++) {
                if (result[i] != -1) {
                    stronglyConnectedComponents[sc_components_count][index++] = result[i];
                }
            }


            sc_components_count++;

        }
    }

    struct ClusterResult cluster_result;
    cluster_result.stronglyConnectedComponents = stronglyConnectedComponents;
    cluster_result.component_sizes = component_sizes;
    cluster_result.count = sc_components_count;

    return cluster_result;
}
struct ClusterResult convert_list_numbers_to_labels(Graph G, struct ClusterResult cluster_result);
void printLabelClusterResult(struct ClusterResult cluster_result);
char **stringify_components(struct ClusterResult cluster_result);
void print_stringified_components(char **stringified_components, int count);
LabelToComponentMap set_components_label_to_original_graph_nodes(Graph g, char **stringified_components, struct ClusterResult cluster_result);
void print_label_to_component_map(LabelToComponentMap map);
char *get_value_by_key(LabelToComponentMap map, const char *key);
Graph add_vertices_on_scc_graph(Graph g, Graph scc_graph, char ***scc_list_label, int **scc_list_index, struct ClusterResult cluster_result, LabelToComponentMap map);

void getStronglyConnectedComponentsKosarujoAproach(Graph g) {
    // First step: get finish times
    int result[g->V];
    memset(result, -1, sizeof(result));

    int num_of_vertices = g->V;

    int stack[num_of_vertices];

    dfs_traversal(g, 0, result, stack);

    // Second step: get finish times

    Graph graphReversed = invertEdgesOfGraph(g, 0);

    //imprimeGrafoIndexes(graphReversed);

    // Fourth step: Clusterize elements
    
    struct ClusterResult clusterResult = findStronglyConnectedComponents(graphReversed, g->V, stack);

    //printClusterResult(clusterResult);

    
    // Graph Generation
    
    // TODO : VERIFICAR SE FUNCIONA SOMENTE COM INDEXES
    struct ClusterResult clusterResultConv = convert_list_numbers_to_labels(g,clusterResult);
    
    //printLabelClusterResult(clusterResultConv);
    
    // TODO : VERIFICAR SE FUNCIONA SOMENTE COM INDEXES
    char **stringified_components = stringify_components(clusterResultConv);
    
   
    // TODO : VERIFICAR SE FUNCIONA SOMENTE COM INDEXES
    LabelToComponentMap label_to_component_map = set_components_label_to_original_graph_nodes(g, stringified_components, clusterResult);
    
    
    // TODO : VERIFICAR SE FUNCIONA SOMENTE COM INDEXES
    Graph scc_graph = GRAPHinit(clusterResultConv.count);
    
    // TODO : VERIFICAR SE FUNCIONA SOMENTE COM INDEXES
    setLabels(scc_graph, stringified_components, clusterResultConv.count);
    
    // TODO : VERIFICAR SE FUNCIONA SOMENTE COM INDEXES
    Graph updated_scc_graph = add_vertices_on_scc_graph(g, scc_graph, clusterResultConv.labels, clusterResult.stronglyConnectedComponents, clusterResult, label_to_component_map);
    /**/
}

struct ClusterResult convert_list_numbers_to_labels(Graph G, struct ClusterResult cluster_result) {
    struct ClusterResult new_cluster_result;
    new_cluster_result.count = cluster_result.count;
    new_cluster_result.component_sizes = cluster_result.component_sizes;
    new_cluster_result.stronglyConnectedComponents = cluster_result.stronglyConnectedComponents;

    new_cluster_result.labels = (char ***)malloc(cluster_result.count * sizeof(char **));
    for (int i = 0; i < cluster_result.count; i++) {
        new_cluster_result.labels[i] = (char **)malloc(cluster_result.component_sizes[i] * sizeof(char *));
        for (int j = 0; j < cluster_result.component_sizes[i]; j++) {
            int index = cluster_result.stronglyConnectedComponents[i][j];
            new_cluster_result.labels[i][j] = GRAPHgetLabelByIndex(G, index);
        }
    }

    return new_cluster_result;
}

void printLabelClusterResult(struct ClusterResult cluster_result) {
    printf("Printing the strongly connected components:\n");
    for (int i = 0; i < cluster_result.count; i++) {
        printf("Component %d: [", i);
        for (int j = 0; j < cluster_result.component_sizes[i]; j++) {
            printf("%s", cluster_result.labels[i][j]);
            if (j < cluster_result.component_sizes[i] - 1) {
                printf(", ");
            }
        }
        printf("]\n");
    }
}

char **stringify_components(struct ClusterResult cluster_result) {
    char **stringified_components = (char **)malloc(cluster_result.count * sizeof(char *));
    for (int i = 0; i < cluster_result.count; i++) {
        int component_size = 0;
        for (int j = 0; j < cluster_result.component_sizes[i]; j++) {
            component_size += strlen(cluster_result.labels[i][j]);
        }
        stringified_components[i] = (char *)malloc((component_size + 1) * sizeof(char));
        stringified_components[i][0] = '\0';
        for (int j = 0; j < cluster_result.component_sizes[i]; j++) {
            strcat(stringified_components[i], cluster_result.labels[i][j]);
        }
    }
    return stringified_components;
}

void print_stringified_components(char **stringified_components, int count) {
    printf("Stringified components: [");
    for (int i = 0; i < count; i++) {
        printf("'%s'", stringified_components[i]);
        if (i < count - 1) {
            printf(", ");
        }
    }
    printf("]\n");
}

LabelToComponentMap set_components_label_to_original_graph_nodes(Graph g, char **stringified_components, struct ClusterResult cluster_result) {
    LabelToComponentMap map;
    map.keys = (char **)malloc(g->V * sizeof(char *));
    map.values = (char **)malloc(g->V * sizeof(char *));
    map.size = g->V;

    for (int i = 0; i < g->V; i++) {
        char *label = GRAPHgetLabelByIndex(g, i);
        map.keys[i] = label;
        bool found = false;
        for (int j = 0; j < cluster_result.count && !found; j++) {
            for (int k = 0; k < cluster_result.component_sizes[j]; k++) {
                if (cluster_result.stronglyConnectedComponents[j][k] == i) {
                    map.values[i] = stringified_components[j];
                    found = true;
                    break;
                }
            }
        }
    }
    return map;
}

void print_label_to_component_map(LabelToComponentMap map) {
    printf("{");
    for (int i = 0; i < map.size; i++) {
        printf("'%s': '%s'", map.keys[i], map.values[i]);
        if (i < map.size - 1) {
            printf(", ");
        }
    }
    printf("}\n");
}

char *get_value_by_key(LabelToComponentMap map, const char *key) {
    for (int i = 0; i < map.size; i++) {
        if (strcmp(map.keys[i], key) == 0) {
            return map.values[i];
        }
    }
    return NULL;
}

Graph add_vertices_on_scc_graph(Graph g, Graph scc_graph, char ***scc_list_label, int **scc_list_index, struct ClusterResult cluster_result, LabelToComponentMap map) {
    for (int i = 0; i < cluster_result.count; i++) {
        int *component_orig = scc_list_index[i];
        for (int j = 0; j < cluster_result.component_sizes[i]; j++) {
            int node_orig = component_orig[j];
            char *node_orig_label = GRAPHgetLabelByIndex(g, node_orig);
            int node_orig_index = GRAPHgetIndexByLabel(g, node_orig_label);
            link node_dest = g->adj[node_orig_index];

            while (node_dest != NULL) {
                int dest_index = node_dest->w;

                char *label_orig_comp = get_value_by_key(map, node_orig_label);
                char *label_dest_comp = get_value_by_key(map, GRAPHgetLabelByIndex(g, dest_index));


                if (strcmp(label_orig_comp, label_dest_comp) != 0) {
                    GRAPHinsertArcByLabel(scc_graph, label_orig_comp, label_dest_comp);
                }
                node_dest = node_dest->next;
            }
        }
    }
    imprimeGrafo(scc_graph);
    return scc_graph;
}




