#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define vertex int

typedef struct graph *Graph;

typedef struct node *link;



struct adjacence
{

   struct adjacencia *next;
} adj;

struct node
{

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

void GRAPHinsertArcByIndex(Graph G, vertex v, vertex w)
{
   for (link a = G->adj[v]; a != NULL; a = a->next)
      if (a->w == w)
         return;
   G->adj[v] = NEWnode(w, G->adj[v]);
   G->A++;
}

int GRAPHgetIndexByLabel(Graph G, char *label)
{

   if (G == NULL || label == NULL)
      return -1;

   int index = -1;

   for (int i = 0; i < G->V; i++) {
      if (strcmp(G->index_to_label[i], label) == 0) {
         index = i;
      }
   }

   if (index == -1)
      fprintf(stderr, "Error: label %s not found in graph\n", label);
   return index;
}

char* GRAPHgetLabelByIndex(Graph G, int index)
{

    if (G == NULL || index < 0 || index >= G->V)
        return NULL;
    char *label = G->index_to_label[index];
    if (label == NULL)
        fprintf(stderr, "Error: index %d not found in graph\n", index);
    return label;
}

void GRAPHinsertArcByLabel(Graph G, char *v_label, char *w_label)
{

   // Find vertex indices for labels
   int v = GRAPHgetIndexByLabel(G,v_label); 
   int w = GRAPHgetIndexByLabel(G,w_label); 

   for (link a = G->adj[v]; a != NULL; a = a->next)
      if (a->w == w)
         return;
   G->adj[v] = NEWnode(w, G->adj[v]);
   G->A++;
}



void setLabels(Graph g, char **labels, int num_labels) {
    int i;
    g->index_to_label = malloc(num_labels * sizeof(char *));
    g->labels_to_index = malloc(num_labels * sizeof(int));
    for (i = 0; i < num_labels; i++) {
        g->index_to_label[i] = labels[i];
        g->labels_to_index[i] = i;
    }
}

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

void imprimeGrafo(Graph g)
{

   limpaArquivo("Grafo.dot");

   FILE *fp;
   fp = fopen("Grafo.dot", "a+");
   gerarTexto("Grafo.dot", "digraph{\n", fp);
   printf("Vertices: %d, Arestas: %d \n", g->V, g->A);

   int i;
   char resultado[256];
   for (i = 0; i < g->V; i++)
   {
      // Gerando os vertices
      printf("v( %s )", g->index_to_label[i]);
      link LINK = g->adj[i];
      while (LINK)
      {
         sprintf(resultado, "V%i -> V%i[label=%s]; \n ", i, LINK->w,g->index_to_label[LINK->w]);
         gerarTexto("Grafo.dot", resultado, fp);
         printf("->(%s)", g->index_to_label[LINK->w]);
         LINK = LINK->next;
      }
      printf("\n");
   }
   gerarTexto("Grafo.dot", " \n}", fp);
   fclose(fp);
}

// --- Remover funcoes daqui de baixo


int main()
{
   /*
   // Numero de vertices que o nosso grafo vai ter
   int n_vertex = 20;
   // Numero de arestas que o nosso grafo vai ter
   int n_links = 20;

   Graph g = GRAPHinit(n_vertex);
   Graph rg = GRAPHrand(n_vertex, n_links);

   printf(" \n EP 1 \n \n ");
   imprimeGrafo(rg);
   */
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

   /*
   // Test node_contains()
   printf("Test GRAPHnodeContains()\n");

   if (GRAPHnodeContains(g, "a", "d")) {
      printf("%s is connected to %s\n", "a", "d");
   } else {
      printf("%s is not connected to %s\n", "a", "d");
   }

   // Test the GRAPHgetIndexByLabel function
   int index_a = GRAPHgetIndexByLabel(G, "a");
   int index_f = GRAPHgetIndexByLabel(G, "f");
   int index_z = GRAPHgetIndexByLabel(G, "z");
   printf("Index of vertex 'a': %d\n", index_a); // should print 0
   printf("Index of vertex 'f': %d\n", index_f); // should print 5
   printf("Index of vertex 'z': %d\n", index_z); // should print an error message and -1

   // Test the GRAPHgetLabelByIndex function
   char *label_0 = GRAPHgetLabelByIndex(G, 0);
   char *label_5 = GRAPHgetLabelByIndex(G, 5);
   char *label_6 = GRAPHgetLabelByIndex(G, 6);
   printf("Label of vertex 0: %s\n", label_0); // should print "a"
   printf("Label of vertex 5: %s\n", label_5); // should print "f"
   printf("Label of vertex 6: %s\n", label_6); // should print an error message and NULL

   */
   
   return 0;
}