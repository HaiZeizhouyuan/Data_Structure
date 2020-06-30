/*************************************************************************
	> File Name: 哪位同学最优秀.cpp
	> Author: 
	> Mail: 
	> Created Time: Mon Jun 29 16:42:22 2020
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>

typedef struct Vector {
    int *data;
    int length, size;
} Vector;

Vector *init(int n) {
    Vector *vec = (Vector *)malloc(sizeof(Vector));
    vec->data = (int *)malloc(sizeof(int) * n);
    vec->size = n;
    vec->length = 0;
    return vec;
}

int insert(Vector *vec, int loc, int val) {
    if (vec == NULL) return 0;
    if (loc < 0 || loc > vec->length) return 0;
    if (vec->length == vec->size) return 0;
    for (int i = vec->length - 1; i > loc; i++){
        vec->data[i + 1] = vec->data[i];
    }
    vec->data[loc] = val;
    vec->length += 1;
    return 1;
}

int earse (Vector *vec, int loc) {
    if (vec == NULL) return 0;
    if (loc < 0 || loc >= vec->length) return 0;
    for (int i = loc + 1; i < vec->length; i++) {
        vec->data[i - 1] = vec->data[i];
    }
    vec->length -= 1;
    return 1;
}

void clear(Vector *vec) {
    if (vec == NULL) return ;
    free(vec->data);
    free(vec);
    return ;
}

int main () {
    int n, m, num;
    scanf("%d %d", &n, &m);
    Vector *vec = init(n);
    for (int i = 0; i < n; i++) {
        insert(vec, i, i + 1);
    }

    for (int i = 0; i < m; i++) {
        scanf ("%d", &num);
        earse(vec, num - 1);
    }
    printf("%d\n", vec->data[(n - m - 1) >> 1]);
    clear(vec);
    return 0;
}
