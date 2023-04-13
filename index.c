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

struct graph
{
   int V;
   int A;
   link *adj;
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

void GRAPHinsertArc(Graph G, vertex v, vertex w)
{
   for (link a = G->adj[v]; a != NULL; a = a->next)
      if (a->w == w)
         return;
   G->adj[v] = NEWnode(w, G->adj[v]);
   G->A++;
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
         GRAPHinsertArc(G, v, w);
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
      printf("v( %d )", i);
      link LINK = g->adj[i];
      while (LINK)
      {
         sprintf(resultado, "V%i -> V%i[label=%i]; \n ", i, LINK->w, LINK->w);
         gerarTexto("Grafo.dot", resultado, fp);
         printf("->(%d)", LINK->w);
         LINK = LINK->next;
      }
      printf("\n");
   }
   gerarTexto("Grafo.dot", " \n}", fp);
   fclose(fp);
}

int main()
{
   // Numero de vertices que o nosso grafo vai ter
   int n_vertex = 20;
   // Numero de arestas que o nosso grafo vai ter
   int n_links = 20;

   Graph g = GRAPHinit(n_vertex);
   Graph rg = GRAPHrand(n_vertex, n_links);

   printf(" \n EP 1 \n \n ");
   imprimeGrafo(rg);

   return 0;
}