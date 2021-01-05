/*************************************************************************
	> File Name: 4.stack.protice5.cpp
	> Author: zhouyuan
	> Mail: 3294207721@qq.com 
	> Created Time: 2021年01月05日 星期二 19时03分45秒
 ************************************************************************/

#include<iostream>
#include<cstring>
#include<algorithm>
#include<cstdio>
#include<queue>
#include<vector>
using namespace std;
 
typedef struct Stack{
    int *data;
    int top, size;
}Stack;

Stack *getNewStack(int n) {
    Stack *s = (Stack *)malloc(sizeof(Stack));
    s->data = (int *)malloc(sizeof(int) * n);
    s->size = n;
    s->top = -1;
    return s;
}


int expend(Stack *s) {
    int extr_size = s->size;
    int *p;
    while(extr_size) {
        p = (int *)realloc(s->data, sizeof(int) * (extr_size + s->size));
        if (p) break;
        extr_size >>= 1;
    }
    if (p == NULL) return 0;
    s->data = p;
    s->size += s->size;
    return 1;
}


int push(Stack *s, int val) {
    if(s == NULL) return 0 ;
    if (s->top + 1 == s->size ) {
        if (!expend(s)) return 0;
    }
    s->data[++s->top] = val;
    return 1;
}


int empty(Stack *s) {
    return s->top == -1;
}

int top(Stack *s) {
    return s->data[s->top];
}

int pop(Stack *s) {
    if (s == NULL) return 0;
    if (!empty(s)) return 0;
    s->top -= 1;
    return 1;
}

void output(Stack *s) {
    for (int i = 0; i <= s->top; i++) {
        i && printf(",");
        printf("%d", s->data[i]);
    }
    printf("\n");
}

void clear(Stack *s) {
    if (s == NULL) return ;
    free(s->data);
    free(s);
    return ;
}

int main() {
    
 
    return 0;
}
