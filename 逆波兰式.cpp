/*************************************************************************
	> File Name: 逆波兰式.cpp
	> Author: 
	> Mail: 
	> Created Time: Mon Jul  6 17:19:25 2020
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Stack {
    int *data;
    int size, top;
} Stack;

Stack *init_stack(int n) {
    Stack *s = (Stack *)malloc(sizeof(Stack));
    s->data = (int *)malloc(sizeof(int) * n);
    s->size = n;
    s->top = -1;
    return s;
}

int push(Stack *s, int val) {
    if (s == NULL) return 0;
    if (s->top + 1 == s->size) return 0;
    s->data[++(s->top)] = val;
    return 1;
}

int top(Stack *s) {
    return s->data[s->top];
}

int empty(Stack *s) {
    return s->top == -1;
}

int pop(Stack *s) {
    if (s == NULL) return 0;
    if (empty(s)) return 0;
    s->top -= 1;
    return 1;
}

void clear (Stack *s) {
    if (s == NULL) return ;
    free(s->data);
    free(s);
    return ;
}

int preed(char a, char b) {
    int class_a, class_b;
    if (a == '+' || a == '-') class_a = 1;
    else class_a = 2;
    if (b == '+' || b == '-') class_b = 1;
    else class_b = 2;
    return class_a > class_b;
}

int oprate(char op, int a, int b) {
    switch(op) {
        case '+' : return a + b; break;
        case '-' : return b - a; break;
        case '*' : return a * b; break;
        case '/' : return b / a; break;
    }
}

void calc(Stack *num, Stack *sym) {
    int a = top(num);
    pop(num);
    int b = top(num);
    pop(num);
    int val = oprate(top(sym), a, b);
    pop(sym);
    push(num, val);
    return ;
}

int is_digit (char str) {
    if (str >= 48 && str <= 57) return 1;
    else return 0;
}

int main () {
    char str[20];
    scanf("%s", str);
    Stack *num = init_stack(20);
    Stack *sym = init_stack(20);
    int i = 0;
    while(i < strlen(str)){
        if (is_digit(str[i])) {
            push(num,str[i] - '0');
            i += 1;
        }
        else {
            if (empty(sym) || preed(str[i], top(sym))) {
                push(sym, str[i]);
                i += 1;
            } else {
                calc(num, sym);
            }
        }
    }

    while (!empty(sym)) {
        calc(num, sym);
    }
    printf("%d\n", top(num));
    clear(num);
    clear(sym);
    return 0;
}
