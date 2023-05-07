#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#define MAX_LENGTH 1000
#define vertex int

typedef struct graph *Graph;

typedef struct node *link;

char** generate_numbers_array(int N);

struct adjacence
{
   char label[60];
   struct adjacencia *next;
} adj;

struct node
{
   char label[60];
   vertex w;
   link next;
};

vertex randV(Graph G);

struct graph
{

   int V;
   int A;
   link *adj;
   char **index_to_label;
   int *labels_to_index;
};

int read_file_lines(const char *filename, char lines[][MAX_LENGTH])
{
   FILE *file = fopen(filename, "r");
   if (!file)
   {
      return -1;
   }

   int line_count = 0;
   char buffer[MAX_LENGTH];

   while (fgets(buffer, MAX_LENGTH, file))
   {
      // remove newline character from buffer
      buffer[strcspn(buffer, "\n")] = '\0';

      // copy buffer to current line in lines array
      strcpy(lines[line_count], buffer);
      line_count++;

      // break out of loop if blank line is encountered
      if (buffer[0] == '\0')
      {
         break;
      }
   }

   fclose(file);

   return line_count;
}
int getNumberOfVertices(Graph G)
{
   return G->V;
}

link *getArrayOfVertices(Graph G)
{
   return G->adj;
}

void limpaArquivo(char nomeArquivo[])
{

   fclose(fopen(nomeArquivo, "w"));
}

void gerarTexto(char nomeArquivo[], char Conteudo[], FILE *fp)
{
   fputs(Conteudo, fp);
}

static link NEWnode(vertex w, link next)
{
   link a = malloc(sizeof(struct node));
   a->w = w;
   a->next = next;
   return a;
}

Graph GRAPHinit(int V)
{
   Graph G = malloc(sizeof *G);
   G->V = V;
   G->A = 0;
   G->adj = malloc(V * sizeof(link));
   for (vertex v = 0; v < V; ++v)
      G->adj[v] = NULL;
   return G;
}

// Getter usado para pegar um determinado label a partir de um index
int GRAPHgetIndexByLabel(Graph G, char *label)
{

   if (G == NULL || label == NULL)
      return -1;

   int index = -1;

   for (int i = 0; i < G->V; i++)
   {
      if (strcmp(G->index_to_label[i], label) == 0)
      {
         index = i;
      }
   }

   if (index == -1)
      fprintf(stderr, "Error: label %s not found in graph\n", label);
   return index;
}

// Pega uma conexão no grafo basada no index 
char *GRAPHgetLabelByIndex(Graph G, int index)
{

   if (G == NULL || index < 0 || index >= G->V)
      return NULL;
   char *label = G->index_to_label[index];
   if (label == NULL)
      fprintf(stderr, "Error: index %d not found in graph\n", index);
   return label;
}

// Pega uma conexão no grafo basada no index 
void GRAPHinsertArcByIndex(Graph G, vertex v, vertex w)
{
   for (link a = G->adj[v]; a != NULL; a = a->next)
      if (a->w == w)
         return;
   G->adj[v] = NEWnode(w, G->adj[v]);
   G->A++;
}

// Insere uma conexão no grafo basada no label 
void GRAPHinsertArcByLabel(Graph G, char *v_label, char *w_label)
{

   // Find vertex indices for labels
   int v = GRAPHgetIndexByLabel(G, v_label);
   int w = GRAPHgetIndexByLabel(G, w_label);

   for (link a = G->adj[v]; a != NULL; a = a->next)
      if (a->w == w)
         return;
   G->adj[v] = NEWnode(w, G->adj[v]);
   G->A++;
}

// Apartir do array de labels passado, seta na mesma ordem 
// estes aos arrays pertencentes ao grafo g, aos quais são 
// usados para mapear os labels ao indexes e vice e versa
void setLabels(Graph g, char **labels, int num_labels)
{
   int i;
   g->index_to_label = malloc(num_labels * sizeof(char *));
   g->labels_to_index = malloc(num_labels * sizeof(int));
   for (i = 0; i < num_labels; i++)
   {
      g->index_to_label[i] = labels[i];
      g->labels_to_index[i] = i;
   }
}

// Checa se uma adjacendia já não contem algum determinado label
// Fazendo a verifição nó a nó da source passada 
bool GRAPHnodeContains(Graph G, char *source, char *destination)
{
   int source_index = GRAPHgetIndexByLabel(G, source);
   int dest_index = GRAPHgetIndexByLabel(G, destination);

   link temp = G->adj[source_index];
   while (temp != NULL)
   {
      if (temp->w == dest_index)
      {
         return true;
      }
      temp = temp->next;
   }

   return false;
}

/* Esta função constrói um grafo aleatório com vértices 0..V-1 e exatamente A arcos. A função supõe que A <= V*(V-1). Se A for próximo de V*(V-1), a função pode consumir muito tempo. (Código inspirado no Programa 17.7 de Sedgewick.) */
Graph GRAPHrand(int V, int A)
{
   Graph G = GRAPHinit(V);

   char** labels = generate_numbers_array(V);

   setLabels(G, labels, V);

   while (G->A < A)
   {
      vertex v = randV(G);
      vertex w = randV(G);
      if (v != w)
         GRAPHinsertArcByIndex(G, v, w);
   }
   return G;
}

/* A função randV() devolve um vértice aleatório do grafo G. Vamos supor que G->V <= RAND_MAX. */
vertex randV(Graph G)
{
   double r;
   r = rand() / (RAND_MAX + 1.0);
   return r * G->V;
}

// Faz a impressão somente do labels de algum grafo g passado 
void imprimeGrafo(Graph g)
{

   limpaArquivo("Grafo.dot");

   FILE *fp;
   fp = fopen("Grafo.dot", "a+");
   gerarTexto("Grafo.dot", "digraph{\n", fp);

   int i;
   char resultado[256];
   for (i = 0; i < g->V; i++)
   {
      // Gerando os vertices
      printf("%s:", g->index_to_label[i]); // Removed the space before the colon
      link LINK = g->adj[i];
      while (LINK)
      {
         sprintf(resultado, "V%i V%i[label=%s]; \n ", i, LINK->w, g->index_to_label[LINK->w]);
         gerarTexto("Grafo.dot", resultado, fp);
         printf(" %s;", g->index_to_label[LINK->w]); // Added a space before the label and removed the space before the semicolon
         LINK = LINK->next;
      }
      printf("\n");
   }
   gerarTexto("Grafo.dot", " \n}", fp);
   fclose(fp);
}

// Faz a impressão somente do indexes de algum grafo g passado 
void imprimeGrafoIndexes(Graph g)
{
   int i;
   char resultado[256];
   printf("Vertices: %d, Arestas: %d \n", g->V, g->A);
   for (i = 0; i < g->V; i++)
   {
      // Gerando os vertices
      printf("v( %d )", i);
      link LINK = g->adj[i];
      while (LINK)
      {
         sprintf(resultado, "V%i -> V%i[label=%d]; \n ", i, LINK->w, LINK->w);
         printf("->(%d)", LINK->w);
         LINK = LINK->next;
      }
      printf("\n");
   }
}

void printBothArraysLabelsToIndexAndIndexToLabel(Graph G)
{
   printf("\nlabels_to_index:\n");
   for (int i = 0; i < G->V; i++)
   {
      printf("%s: %d\n", G->index_to_label[i], G->labels_to_index[i]);
   }
   printf("\nindex_to_label:\n");
   for (int i = 0; i < G->V; i++)
   {
      printf("%d: %s\n", i, G->index_to_label[i]);
   }
   printf("\n");
}

// Gera um array de chars até o numero N passado no paramentro
char** generate_numbers_array(int N) {
    int max_digits = snprintf(NULL, 0, "%d", N) + 1; // Get the maximum number of digits for N

    char** numbers_array = (char**)malloc((N + 1) * sizeof(char*));
    for (int i = 0; i <= N; i++) {
        numbers_array[i] = (char*)malloc(max_digits * sizeof(char));
        snprintf(numbers_array[i], max_digits, "%d", i);
    }

    return numbers_array;
}

// Da um free em todos os indices do array passado
void free_numbers_array(char** numbers_array, int N) {
    for (int i = 0; i <= N; i++) {
        free(numbers_array[i]);
    }
    free(numbers_array);
}

// int main()
// {
//    // Numero de vertices que o nosso grafo vai ter
//    int n_vertex = 20;
//    // Numero de arestas que o nosso grafo vai ter
//    int n_links = 20;

//    // Graph g = GRAPHinit(n_vertex);
//    Graph rg = GRAPHrand(n_vertex, n_links);

//    return 0;
// }