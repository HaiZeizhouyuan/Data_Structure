/*************************************************************************
	> File Name: 4.stack.cpp
	> Author: 
	> Mail: 
	> Created Time: Sun Jun 21 15:31:36 2020
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include<time.h>

typedef struct stack {
    char **data;
    int size, top;
} Stack;

Stack *init(int);
void clear(Stack *);
char *top(Stack *);
int empty(Stack *);
int push(Stack *, char *);
int pop(Stack *);
void output(Stack *, Stack *, Stack *);

int main() {
    Stack *s0 = init(10);
    Stack *s1 = init(10);
    Stack *s2 = init(10);
    int k;
    char val[11];
    for (int i = 0; i < 10; i++) {
        memset(val, 0, sizeof(val));
        scanf("%d%s", &k, val);
        if (k == 0) push(s0, val);
        if (k == 1) push(s1, val);
        if (k == 2) push(s2, val);
    }
    output(s0, s1, s2);
    clear(s0);
    clear(s1);
    clear(s2);
    return 0;
}

Stack *init(int n) {
    Stack *s = (Stack *)malloc (sizeof(Stack));
    s->data = (char **)malloc(sizeof(char *) * n);
    s->size = n;
    s->top = -1;
    return s;
}

char *top(Stack *s) {
    return s->data[s->top];
}

int empty(Stack *s) {
    return s->top == -1;
}

int push(Stack *s, char *val) {
    if (s == NULL) return 0;
    if (s->top + 1 == s->size) return 0;
    //s->data[++(s->top)] = val;
    strcpy(s->data[++(s->top)], val);
    return 1;
}

void output (Stack *s0, Stack *s1, Stack *s2) {
    for (int i = 0; i < 10; i++) {
        if (i <= s0->top) printf("%s ", s0->data[i]);
        else printf("0 ");
        printf("\n");
        /*if (i <= s1->top) printf("%s ", s1->data[i]);
        else printf("0 ");
        if (i <= s2->top) printf("%s\n", s2->data[i]);
        else printf("0\n");*/
    }   
}

void clear (Stack *s) {
    if (s == NULL) return ;
    free(s->data);
    free(s);
    return ;
}

