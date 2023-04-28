#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#define MAX_LENGTH 1000
#define vertex int

typedef struct graph *Graph;

typedef struct node *link;

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

struct graph
{
   int V;
   int A;
   link *adj;
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
         sprintf(resultado, "V%i -> V%i[label=%s]; \n ", i, LINK->w, LINK->w);
         gerarTexto("Grafo.dot", resultado, fp);
         printf("->(%d)", LINK->w);
         LINK = LINK->next;
      }
      printf("\n");
   }
   gerarTexto("Grafo.dot", " \n}", fp);
   fclose(fp);
}

void readInputFile(const char *filename)
{

   char lines[1000][MAX_LENGTH];
   int line_count = read_file_lines(filename, lines);

   if (line_count == -1)
   {
      printf("Unable to open file.\n");
      return 1;
   }

   // // Iniciando o novo grafo
   // Graph g = GRAPHinit(line_count-2);

   // print out each line in the lines array
   int size = atoi(lines[0]);
   int option = atoi(lines[line_count]);

   printf("size %i \n ", size);
   printf("option %i \n ", option);
   for (int i = 1; i < line_count -1; i++)
   {

      if (i == 0)
      {
         printf("[ primeiro ] %s\n ", lines[i]);
         // Pega o primeiro item
      }

      else if (i == line_count - 1)
      {
         // Pega o utlimo item
         printf(" [ultimo] %s\n", lines[i]);
      }
      else
      {
         printf("%s\n", lines[i]);
      }
   }

   // imprimeGrafo(g);
}

int main()
{
   // Numero de vertices que o nosso grafo vai ter
   int n_vertex = 20;
   // Numero de arestas que o nosso grafo vai ter
   int n_links = 20;

   // Graph g = GRAPHinit(n_vertex);
   Graph rg = GRAPHrand(n_vertex, n_links);

   printf(" \n EP 1 \n \n ");
   imprimeGrafo(rg);
   // readInputFile("input.txt");
   return 0;
}