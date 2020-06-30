/*************************************************************************
	> File Name: 稀疏多项式.cpp
	> Author: 
	> Mail: 
	> Created Time: Mon Jun 29 13:41:59 2020
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<math.h>
typedef struct Node {
    int c, e;
} Node;

typedef struct Vector {
    int size, length;
    int *data;
} Vector;

Vector *init (int n) {
    Vector *vec = (Vector *)malloc(sizeof(Vector));
    vec->data = (int *)malloc (sizeof(int) * n);
    vec->size = n;
    vec->length = 0;
    return vec;
}

int insert (Vector *vec, int loc, int val) {
    if (vec == NULL) return 0;
    if (loc < 0 || loc > vec->length) return 0;
    if (vec->length == vec->size) return 0;
    for (int i = vec->length - 1; i > loc; i--) {
        vec->data[i + 1] = vec->data[i];
    }
    vec->data[loc] = val;
    vec->length += 1;
    return 1;
}

int erase (Vector *vec, int loc) {
    if (vec == NULL) return 0;
    if (loc < 0 || loc >= vec->length) return 0;
    for (int i = loc; i < vec->length; i++) {
        vec->data[i - 1] = vec->data[i];
    }
    vec->length -= 1;
    return 1;
}
void insertfuc(Vector *vec, Node *node, int x, int m) {
    for (int i = 0; i < m; i++) {
        int val = node[i].c * pow(x, node[i].e);
        insert(vec, i, val);
    }
    return ;
}

void output (Vector *vec) {
    int sum = 0;
    for (int i = 0; i < vec->length; i++) {
        sum += vec->data[i];
    }
    printf("%d\n", sum);
}

void clear (Vector *vec) {
    if (vec == NULL) return ;
    free (vec->data);
    free(vec);
}

Node node[20];
int main () {
    int m, x;
    scanf("%d", &m);
    Vector *vec = init(m);
    for (int i = 0; i < m; i++) {
        scanf("%d%d", &node[i].c, &node[i].e);
    }
    scanf("%d", &x);
    insertfuc(vec, node, x, m);
    output(vec);
    clear(vec);
    return 0;
}

