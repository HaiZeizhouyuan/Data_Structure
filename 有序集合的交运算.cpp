/*************************************************************************
	> File Name: 有序集合的交运算.cpp
	> Author: 
	> Mail: 
	> Created Time: Mon Jun 29 14:25:45 2020
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>


typedef struct Vector {
    int size, length;
    int *data;
} Vector;

Vector *init(int n) {
    Vector *vec = (Vector*)malloc(sizeof(Vector));
    vec->data = (int *)malloc(sizeof(int) * n);
    vec->length = 0;
    vec->size = n;
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

void buildVecC (Vector *veca, Vector *vecb, Vector *vecc) {
    for (int i = 0; i < veca->size; i++) {
        for (int j = 0; j < vecb->size; j++) {
            if (veca->data[i] == vecb->data[j]) insert(vecc, vecc->length, veca->data[i]);
        }
    }
    return ;
}

void output(Vector *vecc) {
    printf("%d\n", vecc->length);
    for (int i = 0; i < vecc->length; i++) {
        i && printf(" ");
        printf("%d", vecc->data[i]);
    }
    printf("\n");
    return ;
}
void clear(Vector *vec) {
    if (vec == NULL) return ;
    free(vec->data);
    free(vec);
    return ;
}

int main () {
    int n1, n2, n3, val;
    scanf("%d", &n1);
    Vector *veca = init(n1);
    for (int i = 0; i < n1; i++) {
        scanf("%d", &val);
        insert(veca, i, val);
    }

    scanf("%d", &n2);
    Vector *vecb = init(n2);
    for (int i = 0; i < n2; i++) {
        scanf("%d", &val);
        insert(vecb, i, val);
    }
    n3 = n1 < n2 ? n1 : n2;
    Vector *vecc = init(n3);
    buildVecC(veca, vecb, vecc);
    output(vecc);
    clear(veca);
    clear(vecb);
    clear(vecc);
    return 0;
}

