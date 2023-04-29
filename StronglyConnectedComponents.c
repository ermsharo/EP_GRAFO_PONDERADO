
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "index.c"

void topological_search(Graph g);

// Guarda resultado dos nós que coompoem um grafo fortemente conexo
struct ClusterResult {
    int **stronglyConnectedComponents;
    int *component_sizes;
    int count;
    char ***labels;
};

// Cria uma especie de mapa usando struct dos nos exitentes no grafo 
typedef struct {
    char **keys;
    char **values;
    int size;
} LabelToComponentMap;

Graph invertEdgesOfGraph(Graph g, vertex source);

// Usado pra debugar e printar array de int
void printIntArray(int* arr, int size) {
    printf("[ ");
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("]\n");
}

// Metodo principal da Depth First Search que 
// percorre o mais profundo nos nós do grafo 
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

// Metodo para que chama a DFS helper é usado para fazer 
// uma busca em profundidade somente ate o ultimo nó alcançavel
void dfs_traversal_cluster(Graph g, int source, bool* visited, int* result){
    int num_of_vertices = g->V;
    int stack[num_of_vertices];
    int stack_idx = 0;
    int result_idx = 0;

    dfs_traversal_helper(g, source, visited, stack, &stack_idx, result, &result_idx);

}

// Metodo para que chama a DFS helper é usado para fazer 
// uma busca em profundidade em todo o grafo que foi passado. 
// O uso da stack é para termos os tempos de visitação que é 
// usado nos algoritimos 
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
    
    // Inverte resultado
    for (int i = 0; i < num_of_vertices / 2; i++) {
        int temp = result[i];
        result[i] = result[num_of_vertices - 1 - i];
        result[num_of_vertices - 1 - i] = temp;
    }
}

// Função que inverte as direções das arestas do grafo.
// Percorre por todas arestas do grafo representadas pelo array
// na sequencia visita todas adjacencias, faz um link invertido 
// adcionando em um novo grafo 
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

// Printa os componentes conexos encontrados no grafo em forma de index.
// Percorre o Array 2d que fica no objeto Cluster Result 
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

// Printa os componentes conexos encontrados no grafo em forma de label.
// Percorre o Array 2d que fica no objeto Cluster Result 
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


// Metodo de busca pelos componentes fortementes conexos usando 
// o sevindo o metodo principal do algoritimo de Kosarujo . 
// Basicamente recebendo um grafo g com as arestas ja invertidas 
// O algoritimo percorre todo o grafo seguindo a pilhas que tem a 
// ordem de finalização de visitas , fazendo buscas em profundidade
// usando o metodo dfs_traversal_cluster.
// Após isso a partir dos nós alcançaveis ele vai formando os componentes
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
void isGraphScc(Graph scc_graph);


// Metodo principal do algoritimo de Kosarujo 
// Etapa 1 : Pega os tempos de fim de visita, usando uma DFS 
// Etapa 2 : A partir do grafo original cria um mesmo grafo invertido 
// Etapa 3 : Agrupa elements fazendo uma DFS nos nós do grafo invertido
// seguindo a ordem dos tempos de visita
// Etapa 4 : Cria o grafo dos componentes fortemente conexos 
//  Na etapa 4 algumas conversoes e mapas são criados para facilitar a 
//  ligação dos vertices do grafo fortemente conexo

void getStronglyConnectedComponentsKosarujoAproach(Graph g) {
    // Etapa 1 : Pega os tempos de fim de visita, usando uma DFS 
    int result[g->V];
    memset(result, -1, sizeof(result));
    int num_of_vertices = g->V;
    int stack[num_of_vertices];
    dfs_traversal(g, 0, result, stack);

    // Etapa 2 : A partir do grafo original cria um mesmo grafo invertido 
    Graph graphReversed = invertEdgesOfGraph(g, 0);

    // Etapa 3 : Agrupa elements fazendo uma DFS nos nós do grafo invertido
    // seguindo a ordem dos tempos de visita
    struct ClusterResult clusterResult = findStronglyConnectedComponents(graphReversed, g->V, stack);

    
    // Etapa 4 : Cria o grafo dos componentes fortemente conexos
    
    // Converte lista de componentes gerados baseados nos indexes e cria a mesma lista com chars 
    struct ClusterResult clusterResultConv = convert_list_numbers_to_labels(g,clusterResult);

    // Cria uma string para ser usada como label de cada componente  
    char **stringified_components = stringify_components(clusterResultConv);

    // Seta cada label do grafo original para seu respectivo label do components a qual pertence
    LabelToComponentMap label_to_component_map = set_components_label_to_original_graph_nodes(g, stringified_components, clusterResult);
    
    // Cria grafo fortemente conexo
    Graph scc_graph = GRAPHinit(clusterResultConv.count);

    // Checa se grafo é fortemente conexo 
    isGraphScc(scc_graph);
    setLabels(scc_graph, stringified_components, clusterResultConv.count);

    // Liga os o grafo fortemente conexos usando o grafo original 
    Graph updated_scc_graph = add_vertices_on_scc_graph(g, scc_graph, clusterResultConv.labels, clusterResult.stronglyConnectedComponents, clusterResult, label_to_component_map);

}


// Converte array de componentes gerados baseados nos indexes 
// e cria a mesma lista com chars.
// Percorre pelo array 2d dos components encotrados mapeando 
// usando o metodo GRAPHgetLabelByIndex para fazer isso 
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

// Usado para printar os labels do agrupamento dos elementos fortemente conexos 
// itera sobre o array
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

// Cria uma String para cada sublista do objeto ClusterResult
// , para que possamos ter os labels para o grafo final 
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

// Usado para printar uma lista de char que contem os labels do grafo fortemente conexo
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

// Usado para a partir do nó originais do grafo 
// identificar a qual componentes este faz parte 
// Apos percorrer todos os nó quando algum for igual ao no do componente
// seguindo a condição  if (cluster_result.stronglyConnectedComponents[j][k] == i)
// podemos mapear o componente 
// map.values[i] = stringified_components[j];
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

// Usado para printar o Objeto LabelToComponentMap 
// mostrado os itens aos quais estao mapeados 
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

// Getter usado para o valor do index que 
// representa o componente atravez do indice do nó 
char *get_value_by_key(LabelToComponentMap map, const char *key) {
    for (int i = 0; i < map.size; i++) {
        if (strcmp(map.keys[i], key) == 0) {
            return map.values[i];
        }
    }
    return NULL;
}
// A partir do mapas que identificam os componentes, do grafo original, 
// da lista de componentes fortementes conexos faz a ligação dos labels dos componentes conexos 
// com suas respectivas conexões baseando-se no grafo original 
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
    topological_search(scc_graph);
    imprimeGrafo(scc_graph);
    return scc_graph;
}

// Verifica se o grafo é fortemente conexo 
void isGraphScc(Graph scc_graph){
    
    if (scc_graph->V == 1){
        printf("Sim \n");
    }else{
        printf("Não \n");
    }

    printf("%i \n", scc_graph->V);
}
// Faz a ordenação topologica usando a DFS ja exitente 
void topological_search(Graph g) {
    int num_vertices = g->V;
    int* result = malloc(num_vertices * sizeof(int));
    int* stack = malloc(num_vertices * sizeof(int));

    dfs_traversal(g, 0, result, stack);

    for (int i = 0; i < g->V; i++) {
        printf("%s ", GRAPHgetLabelByIndex(g, result[i]));
    }
    printf("\n");

    free(stack);
}




