/*************************************************************************
	> File Name: 4.stack.protice3.c
	> Author: zhouyuan
	> Mail: 3294207721@qq.com 
	> Created Time: 2021年01月05日 星期二 18时00分15秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<time.h>
#include<unistd.h>

typedef struct stack{
    int *data;
    int size, top;
} Stack;

Stack *init(int n) {
    Stack *s = (Stack *)malloc(sizeof(Stack));
    s->data = (int *)malloc(sizeof(int) * n);
    s->size = n;
    s->top -= 1;
    return s;
}

int top(Stack *s){
    return s->data[s->top];
}

int empty(Stack *s){
    return s->top == -1;
}

int expend(Stack *s) {
    int extr_size = s->size;
    int *p;
    while(extr_size) {
        p = (int *)realloc(s->data, sizeof(int) * (s->size + extr_size));
        if (p) break;
        extr_size >>= 1;
    }
    if (p == NULL) return 0;
    s->size += extr_size;
    s->data = p;
    return 1;
}

int push(Stack *s, int val) {
    if (s == NULL) return 0;
    if (s->top + 1 == s->size) {
        expend(s);
    }
    s->data[++(s->top)] = val;
    return 1;
}

int pop(Stack *s){
    if (s == NULL) return 0;
    if (empty(s)) return 0;
    s->top -= 1;
    return 1;
}

void output(Stack *s) {
    for (int i = 0; i <= s->top; i++) {
        i && printf(", ");
        printf("%d", s->data[i]);
    }
    printf("\n");
}

int main() {
    
    return 0;
}
