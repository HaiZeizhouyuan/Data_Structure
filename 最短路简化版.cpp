/*************************************************************************
	> File Name: 最短路简化版.cpp
	> Author: 
	> Mail: 
	> Created Time: Mon Jul 20 15:42:47 2020
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define max_n 1000

typedef struct Node {
    int v;
    struct Node *next;
} Node, *LinkedList;

typedef struct Graph {
    int n;
    ListedList e[max_n];
    int vis[max_n];
} Graph;

Graph *init(int n) {
    Graph *g = (Graph *)malloc(sizeof(Graph));
    g->n = n;
    memset(g->path, 0, sizeof(g->path));
    return g;
}

int insert(Graph *g, int x, int y) {
    if (x < 0 || x > g->n || y < 0 || y > g->n) return 0;
    
}

int main () {
    int n, m, c, x, y;
    scanf("%d%d%d", &n, &m, &c);
    for (int i = 0; i < m; i++) {
        scanf("%d%d", &x, &y);
    }
    return 0;
}
