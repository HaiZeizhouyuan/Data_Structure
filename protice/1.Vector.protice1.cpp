/*************************************************************************
	> File Name: 1.Vector.protice1.cpp
	> Author: 
	> Mail: 
	> Created Time: Tue Jul 21 09:43:07 2020
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct Vec {
    int *data;
    int size, length;
} Vec;

Vec *getNewVec (int n) {
    Vec *v = (Vec *) malloc(sizeof(Vec));
    v->data = (int *)malloc(sizeof(int) * n);
    v->size = n;
    v->length = 0;
    return v;
}

int expend(Vec *v) {
    int extr_size = v->size;
    int *p;
    while (extr_size) {
        p = (int *)realloc(v->data, sizeof(int) * (v->size + extr_size));
        if (p) break;
        extr_size >>= 1;
    }
    if (extr_size == 0) return 0;
    v->data = p;
    v->size += extr_size;
    return 1;
}

int insert(Vec *v, int loc, int val) {
    if (v == NULL) return 0;
    if (loc < 0 || loc > v->length) return 0;
    if (v->size == v->length) {
        if (!expend(v)) return 0;
        printf("\033[32mexpend vec is success, and it's new size is %d\n\033[0m", v->size);
    }
    for (int i = v->length; i > loc; i--) v->data[i] = v->data[i - 1];
    v->data[loc] = val;
    v->length += 1;
    return 1;
}

int delete_node (Vec *v, int loc) {
    if (v == NULL) return 0;
    if (loc < 0 || loc >= v->length) return 0;
    for (int i = loc; i < v->length - 1; i++) v->data[i] = v->data[i + 1];
    v->length -= 1;
    return 1;
}

void output(Vec *v){
    printf("Vector[");
    for (int i = 0; i < v->length; i++) {
        i && printf(",");
        printf("%d", v->data[i]);
    }
    printf("]\n");
    printf("\n");
}

void clearVec (Vec *v) {
    if (v == NULL) return ;
    free(v->data);
    free(v);
    return ;
}

int main () {
    srand(time(0));
    #define max_op 20
    Vec *v = getNewVec(max_op);
    for (int i = 0; i < 4 * max_op; i++) {
        int val = rand() % 100;
        int loc = rand() % (v->length + 3) - 1;
        int op = rand() % 5;
        switch(op) {
            case 0:
            case 1:
            case 2:
            case 3:
                printf("insert %d in %d to vec is %s\n", val, loc, insert(v, loc, val) ? "success" : "failed");
                break;
            case 4:
            case 5:
                printf("delete val in %d is %s\n", loc, delete_node(v, loc) ? "success" : "failed");
                break;
        }
        output(v);
    }
    clearVec(v);
    #undef max_op
    return 0;
}

