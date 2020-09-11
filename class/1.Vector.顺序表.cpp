/*************************************************************************
	> File Name: 1.Vector.cpp
	> Author: 
	> Mail: 
	> Created Time: Sun Jun  7 01:40:19 2020
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<time.h>

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

int expend (Vector *vec) {
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

int insert(Vector *vec, int loc, int val) {
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

int delete_node(Vector *vec, int loc) {
    if (vec == NULL) return 0;
    if (loc < 0 || loc >= vec->length) return 0;
    for (int i = loc + 1; i < vec->length; i++) {
        vec->data[i - 1] = vec->data[i];
    }
    vec->length -= 1;
    return 1;
}

void output(Vector *vec) {
    printf("Vector : [");
    for (int i = 0; i < vec->length; i++) {
        i && printf(", ");
        printf("%d", vec->data[i]);
    }
    printf("]\n");
    return ;
}

void clear(Vector *vec) {
    free(vec->data);
    free(vec);
    return ;
}
int main () {
    srand(time(0));
    #define max_op 20
    Vector *vec = init(max_op);
    for (int i = 0; i < max_op * 4; i++) {
        int op = rand() % 4;
        int loc = rand() % (vec->length + 3) - 1;
        int val = rand() % 100;
        switch (op) {
            case 0:
            case 1:
            case 2: {
                printf("insert %d at %d to Vector = %d\n", val, loc, insert(vec, loc, val));
            }break;
            case 3: {
                printf("delete a item at %d from Vector = %d\n", loc, delete_node(vec, loc));
            }break;
        }
        output(vec);
        printf("\n");
    }
    clear(vec);
    #undef max_op
    return 0;
}
