#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

#include "StronglyConnectedComponents.c"

typedef Graph (*test_function)();

Graph testA() {
    Graph g = GRAPHinit(6);

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

    //imprimeGrafo(g);

    return g;
}


Graph testB_letras() {
   Graph g = GRAPHinit(9);

    char *labels[] = { "a", "b", "c", "d", "e", "f", "g", "h", "i" };
    setLabels(g, labels, 9);

    GRAPHinsertArcByLabel(g, "a", "b");
    GRAPHinsertArcByLabel(g, "b", "c");
    GRAPHinsertArcByLabel(g, "c", "d");
    GRAPHinsertArcByLabel(g, "d", "a");
    GRAPHinsertArcByLabel(g, "c", "e");
    GRAPHinsertArcByLabel(g, "c", "d");
    GRAPHinsertArcByLabel(g, "e", "f");
    GRAPHinsertArcByLabel(g, "f", "g");
    GRAPHinsertArcByLabel(g, "g", "e");
    GRAPHinsertArcByLabel(g, "h", "g");
    GRAPHinsertArcByLabel(g, "h", "i");

    //imprimeGrafo(g);

    return g;
}

Graph testB() {
    Graph g = GRAPHinit(9);

    char *labels[] = { "0", "1", "2", "3", "4", "5", "6", "7", "8" };
    setLabels(g, labels, 9);

    GRAPHinsertArcByLabel(g, "0", "1");
    GRAPHinsertArcByLabel(g, "1", "2");
    GRAPHinsertArcByLabel(g, "2", "3");
    GRAPHinsertArcByLabel(g, "3", "0");
    GRAPHinsertArcByLabel(g, "2", "4");
    GRAPHinsertArcByLabel(g, "2", "3");
    GRAPHinsertArcByLabel(g, "4", "5");
    GRAPHinsertArcByLabel(g, "5", "6");
    GRAPHinsertArcByLabel(g, "6", "4");
    GRAPHinsertArcByLabel(g, "7", "6");
    GRAPHinsertArcByLabel(g, "7", "8");

    //imprimeGrafo(g);

    return g;
}

Graph testC() {
    Graph g = GRAPHinit(11);

    char *labels[] = { "0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "10" };
    setLabels(g, labels, 11);

    GRAPHinsertArcByLabel(g, "0", "1");
    GRAPHinsertArcByLabel(g, "1", "2");
    GRAPHinsertArcByLabel(g, "2", "0");
    GRAPHinsertArcByLabel(g, "1", "3");
    GRAPHinsertArcByLabel(g, "3", "4");
    GRAPHinsertArcByLabel(g, "4", "5");
    GRAPHinsertArcByLabel(g, "5", "3");
    GRAPHinsertArcByLabel(g, "6", "5");
    GRAPHinsertArcByLabel(g, "6", "7");
    GRAPHinsertArcByLabel(g, "7", "8");
    GRAPHinsertArcByLabel(g, "8", "9");
    GRAPHinsertArcByLabel(g, "9", "6");
    GRAPHinsertArcByLabel(g, "9", "10");

    //imprimeGrafo(g);

    return g;
}

Graph testC_letras() {
    Graph g = GRAPHinit(11);

    char *labels[] = { "a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k"};
    setLabels(g, labels, 11);

    GRAPHinsertArcByLabel(g, "a", "b");
    GRAPHinsertArcByLabel(g, "b", "c");
    GRAPHinsertArcByLabel(g, "c", "a");
    GRAPHinsertArcByLabel(g, "b", "d");
    GRAPHinsertArcByLabel(g, "d", "e");
    GRAPHinsertArcByLabel(g, "e", "f");
    GRAPHinsertArcByLabel(g, "f", "d");
    GRAPHinsertArcByLabel(g, "g", "f");
    GRAPHinsertArcByLabel(g, "g", "h");
    GRAPHinsertArcByLabel(g, "h", "i");
    GRAPHinsertArcByLabel(g, "i", "j");
    GRAPHinsertArcByLabel(g, "j", "g");
    GRAPHinsertArcByLabel(g, "j", "k");

    //imprimeGrafo(g);

    return g;
}

// GRAFO ENUCIADO EP ex - 1
Graph testD_exemplo1() {
    Graph g = GRAPHinit(8);

    char *labels[] = { "a", "b", "c", "d", "e", "f", "g", "h"};
    setLabels(g, labels, 8);

    GRAPHinsertArcByLabel(g, "a", "b");
    GRAPHinsertArcByLabel(g, "b", "e");
    GRAPHinsertArcByLabel(g, "b", "f");
    GRAPHinsertArcByLabel(g, "b", "c");
    GRAPHinsertArcByLabel(g, "c", "g");
    GRAPHinsertArcByLabel(g, "c", "d");
    GRAPHinsertArcByLabel(g, "d", "h");
    GRAPHinsertArcByLabel(g, "d", "c");
    GRAPHinsertArcByLabel(g, "e", "a");
    GRAPHinsertArcByLabel(g, "e", "f");
    GRAPHinsertArcByLabel(g, "f", "g");
    GRAPHinsertArcByLabel(g, "g", "f");
    GRAPHinsertArcByLabel(g, "g", "h");

    // imprimeGrafo(g);

    return g;
}

Graph testE() {
    Graph g = GRAPHinit(8);

    char *labels[] = { "apoli", "brexit", "cuba", "dina", "eritr", "finla", "guan", "hondur" };
    setLabels(g, labels, 8);

    GRAPHinsertArcByLabel(g, "apoli", "brexit");
    GRAPHinsertArcByLabel(g, "brexit", "eritr");
    GRAPHinsertArcByLabel(g, "brexit", "finla");
    GRAPHinsertArcByLabel(g, "brexit", "cuba");
    GRAPHinsertArcByLabel(g, "cuba", "guan");
    GRAPHinsertArcByLabel(g, "cuba", "dina");
    GRAPHinsertArcByLabel(g, "dina", "hondur");
    GRAPHinsertArcByLabel(g, "dina", "cuba");
    GRAPHinsertArcByLabel(g, "eritr", "apoli");
    GRAPHinsertArcByLabel(g, "eritr", "finla");
    GRAPHinsertArcByLabel(g, "finla", "guan");
    GRAPHinsertArcByLabel(g, "guan", "finla");
    GRAPHinsertArcByLabel(g, "guan", "hondur");

    //imprimeGrafo(g);

    return g;
}

Graph textF_exemplo2() {
    Graph g = GRAPHinit(9);

    char *labels[] = { "undershorts", "socks", "pants", "shoes", "belt", "shirt", "tie", "jacket", "watch" };
    setLabels(g, labels, 9);

    GRAPHinsertArcByLabel(g, "undershorts", "pants");
    GRAPHinsertArcByLabel(g, "undershorts", "shoes");
    GRAPHinsertArcByLabel(g, "pants", "belt");
    GRAPHinsertArcByLabel(g, "pants", "shoes");
    GRAPHinsertArcByLabel(g, "belt", "jacket");
    GRAPHinsertArcByLabel(g, "shirt", "belt");
    GRAPHinsertArcByLabel(g, "shirt", "tie");
    GRAPHinsertArcByLabel(g, "tie", "jacket");
    GRAPHinsertArcByLabel(g, "socks", "shoes");

    //imprimeGrafo(g);

    return g;
}

Graph textG() {
    Graph g = GRAPHinit(9);

    char *labels[] = { "a", "b", "c", "d", "e", "f", "g", "h", "i" };
    setLabels(g, labels, 9);

    GRAPHinsertArcByLabel(g, "a", "b");
    GRAPHinsertArcByLabel(g, "a", "h");
    GRAPHinsertArcByLabel(g, "b", "h");
    GRAPHinsertArcByLabel(g, "b", "c");
    GRAPHinsertArcByLabel(g, "c", "f");
    GRAPHinsertArcByLabel(g, "d", "e");
    GRAPHinsertArcByLabel(g, "d", "c");
    GRAPHinsertArcByLabel(g, "e", "f");
    GRAPHinsertArcByLabel(g, "g", "h");

    //imprimeGrafo(g);

    return g;
}

Graph textH_exemplo4() {
    Graph g = GRAPHinit(4);

    char *labels[] = { "a", "b", "c", "e" };
    setLabels(g, labels, 4);

    GRAPHinsertArcByLabel(g, "a", "b");
    GRAPHinsertArcByLabel(g, "a", "c");
    GRAPHinsertArcByLabel(g, "b", "e");
    GRAPHinsertArcByLabel(g, "c", "e");
    GRAPHinsertArcByLabel(g, "e", "a");

    //imprimeGrafo(g);

    return g;
}

Graph textJ() {
    Graph g = GRAPHinit(4);

    char *labels[] = { "a", "b", "c", "e" };
    setLabels(g, labels, 4);

    GRAPHinsertArcByLabel(g, "a", "b");
    GRAPHinsertArcByLabel(g, "a", "a");
    GRAPHinsertArcByLabel(g, "b", "e");
    GRAPHinsertArcByLabel(g, "c", "e");
    GRAPHinsertArcByLabel(g, "e", "a");

    //imprimeGrafo(g);

    return g;
}

Graph testC_selfloop() {
    Graph g = GRAPHinit(11);

    char *labels[] = { "a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k" };
    setLabels(g, labels, 11);

    GRAPHinsertArcByLabel(g, "a", "b");
    GRAPHinsertArcByLabel(g, "b", "c");
    GRAPHinsertArcByLabel(g, "c", "a");
    GRAPHinsertArcByLabel(g, "b", "d");
    GRAPHinsertArcByLabel(g, "d", "e");
    GRAPHinsertArcByLabel(g, "e", "f");
    GRAPHinsertArcByLabel(g, "f", "d");
    GRAPHinsertArcByLabel(g, "g", "f");
    GRAPHinsertArcByLabel(g, "g", "h");
    GRAPHinsertArcByLabel(g, "h", "i");
    GRAPHinsertArcByLabel(g, "i", "j");
    GRAPHinsertArcByLabel(g, "j", "g");
    GRAPHinsertArcByLabel(g, "j", "j");

    //imprimeGrafo(g);

    return g;
}

Graph testI() {
    Graph g = GRAPHinit(5);

    char *labels[] = { "0", "1", "2", "3", "4" };
    setLabels(g, labels, 5);

    GRAPHinsertArcByLabel(g, "0", "3");
    GRAPHinsertArcByLabel(g, "1", "2");
    GRAPHinsertArcByLabel(g, "2", "1");
    GRAPHinsertArcByLabel(g, "3", "4");
    GRAPHinsertArcByLabel(g, "3", "2");

    //imprimeGrafo(g);

    return g;
}

Graph testJ() {
    Graph g = GRAPHinit(10);

    char *labels[] = { "0", "1", "2", "3", "4", "5", "6", "7", "8", "9" };
    setLabels(g, labels, 10);

    GRAPHinsertArcByLabel(g, "0", "5");
    GRAPHinsertArcByLabel(g, "0", "6");
    GRAPHinsertArcByLabel(g, "0", "1");
    GRAPHinsertArcByLabel(g, "2", "9");
    GRAPHinsertArcByLabel(g, "2", "0");
    GRAPHinsertArcByLabel(g, "3", "0");
    GRAPHinsertArcByLabel(g, "3", "5");
    GRAPHinsertArcByLabel(g, "4", "7");
    GRAPHinsertArcByLabel(g, "4", "6");
    GRAPHinsertArcByLabel(g, "5", "9");
    GRAPHinsertArcByLabel(g, "5", "2");
    GRAPHinsertArcByLabel(g, "6", "7");
    GRAPHinsertArcByLabel(g, "6", "0");
    GRAPHinsertArcByLabel(g, "6", "9");
    GRAPHinsertArcByLabel(g, "7", "3");
    GRAPHinsertArcByLabel(g, "7", "4");
    GRAPHinsertArcByLabel(g, "8", "5");
    GRAPHinsertArcByLabel(g, "8", "0");
    GRAPHinsertArcByLabel(g, "9", "3");
    GRAPHinsertArcByLabel(g, "9", "7");

    //imprimeGrafo(g);

    return g;
}
Graph testK() {
    Graph g = GRAPHinit(4);

    char *labels[] = { "A", "B", "C", "D" };
    setLabels(g, labels, 4);

    GRAPHinsertArcByLabel(g, "A", "B");
    GRAPHinsertArcByLabel(g, "B", "C");
    GRAPHinsertArcByLabel(g, "C", "D");
    GRAPHinsertArcByLabel(g, "D", "A");

    return g;
}
Graph testL() {
    Graph g = GRAPHinit(6);

    char *labels[] = { "A", "B", "C", "D", "E", "F" };
    setLabels(g, labels, 6);

    GRAPHinsertArcByLabel(g, "A", "B");
    GRAPHinsertArcByLabel(g, "B", "C");
    GRAPHinsertArcByLabel(g, "C", "A");

    GRAPHinsertArcByLabel(g, "D", "E");
    GRAPHinsertArcByLabel(g, "E", "F");
    GRAPHinsertArcByLabel(g, "F", "D");

    return g;
}
Graph testM() {
    Graph g = GRAPHinit(8);

    char *labels[] = { "A", "B", "C", "D", "E", "F", "G", "H" };
    setLabels(g, labels, 8);

    GRAPHinsertArcByLabel(g, "A", "B");
    GRAPHinsertArcByLabel(g, "B", "C");
    GRAPHinsertArcByLabel(g, "C", "A");

    GRAPHinsertArcByLabel(g, "D", "E");
    GRAPHinsertArcByLabel(g, "E", "F");

    GRAPHinsertArcByLabel(g, "G", "H");
    GRAPHinsertArcByLabel(g, "H", "G");

    return g;
}

void redirect_stdout_to_file(const char *filename);
void run_tests();
void random_tests();

int main() {

    random_tests();
    run_tests();

    return 0;
}

void random_tests() {

    printf("Random tests \n");
    srand(time(NULL)); // Seed the random number generator with the current time

    int num_tests = 5;
    int max_vertices = 200;
    int max_edges = 200;

    for (int i = 0; i < num_tests; i++) {
        int n_vertex = rand() % (max_vertices + 1); // Random number of vertices between 0 and max_vertices
        int n_links = rand() % (max_edges + 1);    // Random number of edges between 0 and max_edges

        printf("Test %d: %d vertices, %d edges\n", i + 1, n_vertex, n_links);

        Graph rg = GRAPHrand(n_vertex, n_links);
        int approach = 1; 
        printf("Random running for approach 1 \n");
        executeKosarajuApproach(approach, rg);
        printf("\n \n");
        printf("Random running for approach 2 \n");
        approach = 2;
        executeKosarajuApproach(approach, rg);
        printf("\n \n");

    }
}

void run_tests() {
    test_function tests[] = {
        //testA,
        //testB_letras,
        //testB,
       // testC,
        //testC_letras,
        //testD_exemplo1,
        //testE,
       // textF_exemplo2,
        //textG,
        //textH_exemplo4,
       // testC_selfloop,
       // testI,
       // testJ,
        testK,
        testL,
        testM
    };

    printf("TESTS FOR APPROACH 1 \n");

    int num_tests = sizeof(tests) / sizeof(test_function);
    int approach = 1; // Change this value to choose the desired approach: 1 for Approach A, 2 for Approach B

    for (int i = 0; i < num_tests; i++) {
        printf("Running test %d:\n", i + 1);
        Graph rg = tests[i](); // Call the test function
        printf("\n");

        // Call the executeKosarajuApproach function for the current graph
        executeKosarajuApproach(approach, rg);
        printf("\n");
    }

    printf("TESTS FOR APPROACH 2 \n");

    approach = 2;

    for (int i = 0; i < num_tests; i++) {
        printf("Running test %d:\n", i + 1);
        Graph rg = tests[i](); // Call the test function
        printf("\n");

        // Call the executeKosarajuApproach function for the current graph
        executeKosarajuApproach(approach, rg);
        printf("\n");
    }
}

void redirect_stdout_to_file(const char *filename) {
    if (freopen(filename, "w", stdout) == NULL) {
        fprintf(stderr, "Error redirecting stdout to file: %s\n", filename);
        exit(1);
    }
}