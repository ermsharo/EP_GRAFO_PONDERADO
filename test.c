#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEN 50
#define MAX_CONNECTIONS 10
#define MAX_ITEMS 10

char **parse_adj(char input[][MAX_LEN], int num_items, int *adj_size) {
    char **adj = (char**)malloc(num_items * sizeof(char*));
    *adj_size = 0;

    for (int i = 0; i < num_items; i++) {
        char *tok = strtok(input[i], ":; ");
        if (tok != NULL) {
            adj[(*adj_size)++] = strdup(tok);
        }
    }

    return adj;
}

void parse_input(char input[][MAX_LEN], int num_lines, char output[][MAX_LEN], int *num_items) {
    int i, j;

    for (i = 0; i < num_lines; i++) {
        char *token = strtok(input[i], ":;");
        while (token != NULL) {
            if (strcmp(token, " ") != 0 && strcmp(token, "") != 0) {
                int found = 0;
                for (j = 0; j < MAX_ITEMS; j++) {
                    if (num_items[j] > 0 && strcmp(output[j][0], token) == 0) {
                        strcpy(output[j][num_items[j]], strtok(NULL, ":; "));
                        num_items[j]++;
                        found = 1;
                        break;
                    }
                }
                if (!found) {
                    strcpy(output[i][0], token);
                    strcpy(output[i][1], strtok(NULL, ":; "));
                    num_items[i] = 2;
                    break;
                }
            }
            token = strtok(NULL, ":;");
        }
    }
}


int main() {
    char input[][MAX_LEN] = { "undershorts: pants; shoes;",
                              "pants: belt; shoes;",
                              "belt: jacket;",
                              "shirt: belt; tie;" };
    int num_items = 4;
    int adj_size, conns_size;

    char **adj = parse_adj(input, num_items, &adj_size);
    char **conns = parse_connections(input, 5);

    printf("Adjacency list:\n");
    for (int i = 0; i < adj_size; i++) {
        printf("%s\n", adj[i]);
    }

  printf("Connections:\n");
for (int i = 0; i < conns_size; i++) {
    printf("%s", conns[i]);
  
}
    // free allocated memory
    for (int i = 0; i < adj_size; i++) {
        free(adj[i]);
    }
    for (int i = 0; i < conns_size; i++) {
        free(conns[i]);
    }
    free(adj);
    free(conns);

    return 0;
}
