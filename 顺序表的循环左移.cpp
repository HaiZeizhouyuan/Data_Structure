/*************************************************************************
	> File Name: 顺序表的循环左移.cpp
	> Author: 
	> Mail: 
	> Created Time: Sun Jun 28 20:26:19 2020
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#define max_n 100

typedef struct Vector{
    int size, length;
    int *data;
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
    for (int i = vec->length; i > loc; i--) {
        vec->data[i] = vec->data[i - 1];
    }
    vec->data[loc] = val;
    vec->length += 1;
    return 1;
}

int earese (Vector *vec, int loc) {
    if (vec == NULL) return 0;
    if (loc < 0 || loc >= vec->length) return 0;
    for (int i = loc + 1; i < vec->length; i++) {
        vec->data[i - 1] = vec->data[i];
    }
    vec->length -= 1;
    return 1;
}

void forleft(Vector *vec, int m) {
    for (int i = 0; i < m; i++) {
        vec->length += 1;
        vec->data[vec->length - 1] = vec->data[0];
        //printf("%d\n", vec->data[i]);
        earese(vec, 0);
    }

    return ;

}

void outout (Vector *vec) {
    for (int i = 0; i < vec->length; i++) {
        i && printf(" ");
        printf("%d", vec->data[i]);
    }
    printf("\n");
}

void clear(Vector *vec) {
    free(vec->data);
    free(vec);
    return ;
}

int main () {
    int n, k, val;
    scanf ("%d %d", &n, &k);
    Vector *vec = init(n + 1);
    for (int i = 0; i < n; i++) {
        scanf("%d", &val);
        insert(vec, i, val);
    }

    forleft(vec, k);
    outout(vec);
    clear(vec);
    return 0;
}

