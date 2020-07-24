/*************************************************************************
	> File Name: 1.Vector.protice.cpp
	> Author: 
	> Mail: 
	> Created Time: Mon Jun  8 20:30:18 2020
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>

typedef struct Vector{
    int *data;
    int size, length;
} Vector;

Vector *init(int n) {
    Vector *vec = (Vector *)malloc(sizeof(Vector));
    vec->data = (int *)malloc(sizeof(int) * n);
    vec->size = n;
    vec->length = 0;
    return vec;
}

int expend(Vector *vec) {
    int extr_size = vec->size;
    int *p;
    while (extr_size) {
        p = (int *)realloc(vec->data, sizeof(int) * (vec->size + extr_size));
        if (p) break;
        extr_size /= 2;
    }
    if (extr_size == 0) return 0;
    vec->data = p;
    vec->size += extr_size;
    return 1;
}

int inisert(Vector *vec, int loc, int val){
    if (vec == NULL) return 0;
    if (loc < 0 || loc > vec->length) return 0;
    if (vec->length == vec->size) {
        if (!expend(vec)) return 0;
        printf("success to expend ! the Vector size is %d\n", vec->size);
    }
    for (int i = vec->length; i > loc; i--) {
        vec->data[i] = vec->data[i - 1];
    }
    vec->data[loc] = val;
    vec->length += 1;
    return 1;
}

void clear(Vector *vec) {
    free(vec->data);
    free(vec);
    return ;
}



