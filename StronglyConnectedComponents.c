
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "index.c"

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
}
