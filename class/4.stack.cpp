/*************************************************************************
	> File Name: 4.stack.cpp
	> Author: 
	> Mail: 
	> Created Time: Sun Jun 21 15:31:36 2020
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<time.h>

typedef struct stack {
    int *data;
    int size, top;
} Stack;

Stack *init(int);
void clear(Stack *);
int top(Stack *);
int empty(Stack *);
int push(Stack *, int);
int pop(Stack *);
void output(Stack *);

int main() {
    #define max_op 20
    srand(time(0));
    Stack *s = init(10);
    for (int i = 0; i < max_op; i++) {
        int val = rand() % 100;
        int op = rand() % 4;
        switch(op){
            case 0 :
            case 1 :
            case 2 : {
                printf("push %d to the stack is = %d\n", val, push(s, val));
            } break;
            case 3 : {
                int t = top(s);
                printf("pop %d from the Stack is = %d\n", t, pop(s));
            } break;
            
        }
        output(s);
    }
    #undef max_op
    clear(s);
    return 0;
}

Stack *init(int n) {
    Stack *s = (Stack *)malloc (sizeof(Stack));
    s->data = (int *)malloc(sizeof(int) * n);
    s->size = n;
    s->top = -1;
    return s;
}

int top(Stack *s) {
    return s->data[s->top];
}

int empty(Stack *s) {
    return s->top == -1;
}

int expend (Stack *s) {
    int extr_size = s->size;
    int *p;
    while(extr_size) {
        p = (int *)realloc(s->data,sizeof(int) * (s->size + extr_size));
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
        printf("\033[31mexpend Stack is success!, Stack's size is = %d\n\n\033[0m", s->size);
    }
    s->data[++(s->top)] = val;
    return 1;
}

int pop(Stack *s) {
    if (s == NULL) return 0;
    if (empty(s)) return 0;
    s->top -= 1;
    return 1;
}

void output (Stack *s) {
    printf("Stack(%d) = [", s->top + 1);
    for (int i = 0; i <= s->top; i++) {
        i && printf(", ");
        printf("%d", s->data[i]);
    }
    printf("];\n\n");
}

void clear (Stack *s) {
    if (s == NULL) return ;
    free(s->data);
    free(s);
    return ;
}

