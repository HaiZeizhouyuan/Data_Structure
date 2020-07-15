/*************************************************************************
	> File Name: 蒜头君的魔法机.cpp
	> Author: 
	> Mail: 
	> Created Time: Mon Jul  6 16:17:46 2020
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>

typedef struct Stack {
    int *data;
    int size, top;
} Stack;

Stack *init_stack (int n) {
    Stack *s = (Stack *)malloc(sizeof(Stack));
    s->data = (int *)malloc(sizeof(int) * n);
    s->size = n;
    s->top = -1;
    return s;
}

int push(Stack *s, int val) {
    if (s ==NULL) return 0;
    if (s->top + 1 == s->size) return 0;
    s->data[++(s->top)] = val;
    return 1;
}

int top (Stack *s) {
    return s->data[s->top];
}

int empty (Stack *s) {
    return s->top == -1;
}

int pop(Stack *s) {
    if (s == NULL) return 0;
    if (empty(s)) return 0;
    s->top -= 1;
    return 1;
}

void clear (Stack *s) {
    if(s == NULL) return ;
    free(s->data);
    free(s);
    return ;
}

int main() {
    int n, ind = 0, m;
    scanf ("%d", &n);
    Stack *s = init_stack(n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &m);
        push(s, i);
    }
    return 0;
}
