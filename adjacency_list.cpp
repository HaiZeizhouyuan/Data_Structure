/*************************************************************************
	> File Name: adjacency_list.cpp
	> Author: 
	> Mail: 
	> Created Time: Sun Jul 19 16:32:04 2020
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#define max_n 1000
typedef struct Graph {
    LinkedList edges[max_n];
    int n;
} Graph;

Graph *getNewGraph (int n) {
    Graph *g = (Graph *)malloc(sizeof(Graph));
    g->n = n;
    for (int i = 0; i < g->n; i++) g->edges[i] == NULL;
}

void clear(Graph *g) {
    for (int i = 0; i < g->n; i++) {
        Node *head = g->edges[i];
    }
}
