/*************************************************************************
	> File Name: 回文判断.cpp
	> Author: 
	> Mail: 
	> Created Time: Mon Jul  6 18:44:22 2020
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Stack {
    char *data;
    int size, top;
} Stack;

Stack *init(int n) {
    Stack *s = (Stack *)malloc (sizeof(Stack));
    s->data = (char *)malloc(sizeof(char) * n);
    s->size = n;
    s->top = -1;
    return s;
}
char top(Stack *s) {
    return s->data[s->top];
}

char topp(Stack *s) {
    return s->data[s->top - 1];
}

int empty(Stack *s) {
    return s->top == -1;
}

int emepty1(Stack *s) {
    return s->top < 1;
}

int push(Stack *s, char val) {
    if (s == NULL) return 0;
    if (s->top + 1 == s->size) return 0;
    s->data[++(s->top)] = val;
    return 1;
}

int pop(Stack *s) {
    if (s == NULL) return 0;
    if (empty(s)) return 0;
    s->top -= 1;
    return 1;
}

void clear(Stack *s) {
    if(s == NULL) return ;
    free(s->data);
    free(s);
    return ;
}

int main(){
    char str[20];
    scanf("%s", str);
    Stack *s = init(20);
    for (int i = 0; i < strlen(str) - 1; i++) {
        if (!empty(s) && str[i] == top(s)) {
            pop(s);
        } else if (!emepty1(s) && str[i] == topp(s)) {
            pop(s);
            pop(s);
        } else {
            push(s, str[i]); 
        } 
    }
    if (strlen(str) == 2) printf("%s\n", "true");
    else printf("%s\n", empty(s) ? "true" : "false");
    clear(s);
    return 0;
}
