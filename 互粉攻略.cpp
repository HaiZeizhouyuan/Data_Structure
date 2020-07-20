/*************************************************************************
	> File Name: 互粉攻略.cpp
	> Author: 
	> Mail: 
	> Created Time: Sun Jul 19 21:11:11 2020
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define max_n 1000
int ans[max_n + 5] = {0};
typedef struct Graph {
    int visit[max_n + 5][max_n + 5];
    int n;
} Graph;

Graph *getNewGraph (int n) {
    Graph *g = (Graph *)malloc(sizeof(Graph));
    g->n = n;
    memset(g->visit, 0, sizeof(g->visit));
    return g;
}

int insert (Graph *g, int x, int y) {
    if (x < 0 || x >= g->n || y < 0 || y >= g->n) return 0;
    int flag = g->visit[x][y];
    g->visit[x][y] = 1;
    return flag;
}

void output(int *ans, int n) {
    for(int i = 0; i < n; i++) {
        printf("%d\n", ans[i]);
    }
}

int main () {
    int n, m, x, y;
    scanf("%d%d", &n, &m);
    Graph *g = getNewGraph(n);
    for (int i = 0; i < m; i++) {
        scanf("%d%d", &x, &y);
        if (!insert(g, x, y)) {
            ans[x] -= 1;
            ans[y] += 1;
        }
    }
    output(ans, n);
    free(g);
    return 0;
}

