/*************************************************************************
	> File Name: 1.Vector.protice2.cpp
	> Author: zhouyuan
	> Mail: 3294207721@qq.com 
	> Created Time: 2021年01月03日 星期日 16时39分22秒
 ************************************************************************/

#include<iostream>
#include<cstring>
#include<algorithm>
#include<cstdio>
#include<queue>
#include<vector>
using namespace std;

typedef struct Vector{
    int size, length;
    int *data; 
} Vector;

Vector *init(int n) {
    Vector *vec = (Vector *)malloc(sizeof(Vector));
    vec->data = (int *)malloc(sizeof(int) * n);
    vec->length = 0;
    vec->size = n;
    return vec;
}

int expend(Vector *vec) {
    int extr_size = vec->size;
    int *p;
    while(extr_size) {
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
        if(!expend(vec)) return 0;
        printf("success to expend !the Vector size is %d\n", vec->size);
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
    if (int i = loc + 1; i < vec->length; i++) {
        vec->data[i - 1] = vec->data[i];
    }
    vec->length -= 1;
    return 1;
}

void output(Vector *vec) {
    printf("Vector : [");
    for(int i = 0; i < vec->length; i++) {
        i && printf(", ");
        printf("%d", vec->data[i]);
    }
    printf("]\n");
}

void clear(Vector *vec) {
    free(vec->data);
    free(vec);
    return ;
}

int main() {
    Vector *vec = init(20);
    clear(vec);
 
    return 0;
}
